#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include <ranges>
#include <unordered_map>
#include <set>

#include <vector>
#include <array>

enum class Direction {
    Left = 0,
    Right,
    Up,
    Down,
};

Direction convert (std::string_view str) {
    std::unordered_map<std::string_view, Direction> mapping {
        {"R", Direction::Right},
        {"L", Direction::Left},
        {"U", Direction::Up},
        {"D", Direction::Down},
    };
    return mapping.at(str);
}

struct Move {
    Direction direction;
    int steps;
};

using Moves = std::vector<Move>;

Moves loadMovesFromFile (std::ifstream& file_stream) { 
    Moves moves {};
    std::string direction;
    int steps;
    while (file_stream.good()) {
        file_stream >> direction >> steps;
        moves.push_back({
            .direction = convert(direction),
            .steps = steps,
        });
    }
    return moves;
}

struct Position {
    int x{0};
    int y{0};

    int max_absolute () const {
        return std::max(std::abs(x), std::abs(y));
    }
};

Position operator+ (const Position& lhs, const Position& rhs) {
    return {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
    };
}

Position operator- (const Position& lhs, const Position& rhs) {
    return {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
    };
}

bool operator< (const Position& lhs, const Position& rhs) {
    return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}

Position moveByDirection (Direction direction) {
    std::unordered_map<Direction, Position> mapping {
        {Direction::Left, {-1, 0}},
        {Direction::Right, {1, 0}},
        {Direction::Down, {0, -1}},
        {Direction::Up, {0, 1}},
    };
    return mapping.at(direction);
}

Position getFollowerPosition (const Position& head, const Position& follower) {
    auto diff = head - follower;
    if (diff.max_absolute() <= 1) {
        return follower;
    }
    else {
        return follower + Position{
            .x = ((diff.x == 0) ? 0 : ((diff.x > 0) ? 1 : -1)),
            .y = ((diff.y == 0) ? 0 : ((diff.y > 0) ? 1 : -1)),
        };
    }
}

class TailKnotsTracker {
public:
    TailKnotsTracker (int number_of_knots) : positions_{static_cast<std::size_t>(number_of_knots)} {
    }

    Position moveHead(Direction direction) {
        // move head
        positions_[0] = positions_[0] + moveByDirection(direction);
        // move other knots
        for (int i = 1; i < positions_.size(); ++i) {
            positions_[i] = getFollowerPosition(positions_[i-1], positions_[i]);
        }
        return positions_.back();
    }

private:
    std::vector<Position> positions_;
};

int simulateHeadMove (int number_of_knots, const Moves& moves) {
    TailKnotsTracker tracker {number_of_knots};
    std::set<Position> tail_positions;
    for (const auto& move : moves) {
        for (int i = 0; i < move.steps; ++i) {
            tail_positions.insert(tracker.moveHead(move.direction));
        }
    }
    return tail_positions.size();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << std::format("Usage: {} <input-file>", argv[0]);
        std::exit(EXIT_FAILURE);
    }
    std::filesystem::path input_file = argv[1];

    std::ifstream file_stream{input_file, std::ifstream::in};
    if (not file_stream.is_open())
    {
        std::cerr << std::format("Unable to open input file {}", input_file.string());
        std::exit(EXIT_FAILURE);
    }

    auto moves = loadMovesFromFile(file_stream);
    std::cout << std::format("Number of moves: {}\n", moves.size());

    auto visited_positions = simulateHeadMove(10, moves);
    std::cout << "Number of covered positions: " << visited_positions << "\n";
}