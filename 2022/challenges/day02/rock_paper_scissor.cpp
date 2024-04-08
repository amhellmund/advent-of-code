#include <cstdlib>
#include <ranges>
#include <numeric>

#include "rock_paper_scissor.hpp"

Winner getWinner (const Game& game) {
    const std::map<std::pair<HandShape, HandShape>, Winner> PLAYER_OPPONENT_WINNER_MAPPING {
        // std::pair(hand_of_player, hand_of_opponent) -> winner
        {{HandShape::Rock, HandShape::Rock}, Winner::Draw},
        {{HandShape::Rock, HandShape::Paper}, Winner::Opponent},
        {{HandShape::Rock, HandShape::Scissor}, Winner::Player},
        ///
        {{HandShape::Paper, HandShape::Rock}, Winner::Player},
        {{HandShape::Paper, HandShape::Paper}, Winner::Draw},
        {{HandShape::Paper, HandShape::Scissor}, Winner::Opponent},
        ///
        {{HandShape::Scissor, HandShape::Rock}, Winner::Opponent},
        {{HandShape::Scissor, HandShape::Paper}, Winner::Player},
        {{HandShape::Scissor, HandShape::Scissor}, Winner::Draw},
    };
    return PLAYER_OPPONENT_WINNER_MAPPING.at({game.hand_of_player, game.hand_of_opponent});
}

HandShape getPlayerHand (const GameOpponentWinner& game) {
    const std::map<std::pair<HandShape, Winner>, HandShape> OPPONENT_WINNER_PLAYER_MAPPING {
        // std::pair(hand_of_player, hand_of_opponent) -> winner
        {{HandShape::Rock, Winner::Player}, HandShape::Paper},
        {{HandShape::Rock, Winner::Draw}, HandShape::Rock},
        {{HandShape::Rock, Winner::Opponent}, HandShape::Scissor},
        ///
        {{HandShape::Paper, Winner::Player}, HandShape::Scissor},
        {{HandShape::Paper, Winner::Draw}, HandShape::Paper},
        {{HandShape::Paper, Winner::Opponent}, HandShape::Rock},
        ///
        {{HandShape::Scissor, Winner::Player}, HandShape::Rock},
        {{HandShape::Scissor, Winner::Draw}, HandShape::Scissor},
        {{HandShape::Scissor, Winner::Opponent}, HandShape::Paper},
    };
    return OPPONENT_WINNER_PLAYER_MAPPING.at({game.hand_of_opponent, game.winner});
}

int getPointsForHandPlayer (const HandShape& shape) {
    switch (shape) {
        case HandShape::Rock:
            return 1;
        case HandShape::Paper:
            return 2;
        case HandShape::Scissor:
            return 3;
    }
}

int getPointsForWinner (const Winner& winner) {
    switch (winner) {
        case Winner::Player:
            return 6;
        case Winner::Draw:
            return 3;
        case Winner::Opponent:
            return 0;
    }
}

int getPlayerPoints (const Game& game) {
    return getPointsForHandPlayer(game.hand_of_player) + getPointsForWinner(getWinner(game));
}

int getPlayerPoints (const std::vector<Game>& tournament) {
    return std::accumulate(tournament.cbegin(), tournament.cend(), 0, [](const int value, const Game& game) {
        return value + getPlayerPoints(game);
    });
}

Tournament readTournamentFromFile (std::istream& file_stream, const HandShapeMapping& opponent_mapping, const HandShapeMapping& player_mapping) {
    Tournament tournament {};
    while (file_stream.good()) {
        std::string opponent, player;
        file_stream >> opponent >> player;
        if (not opponent.empty() and not player.empty()) {
            tournament.push_back(
                {
                    .hand_of_player = player_mapping.at(player),
                    .hand_of_opponent = opponent_mapping.at(opponent),
                }
            );
        }
    }
    return tournament;
}

TournamentOpponentWinner readTournamentOpponentWinnerFromFile (std::istream& file_stream, const HandShapeMapping& opponent_mapping, const WinnerMapping& winner_mapping) {
    TournamentOpponentWinner tournament{};
    while (file_stream.good()) {
        std::string opponent, winner;
        file_stream >> opponent >> winner;
        if (not opponent.empty() and not winner.empty()) {
            tournament.push_back(
                {
                    .hand_of_opponent = opponent_mapping.at(opponent),
                    .winner = winner_mapping.at(winner),
                }
            );
        }
    }
    return tournament;
}

Tournament convert (const TournamentOpponentWinner& tournament) {
    auto range = tournament | std::views::transform([](const GameOpponentWinner& game) -> Game {
        return {
            .hand_of_player = getPlayerHand(game),
            .hand_of_opponent = game.hand_of_opponent,
        };
    });
    return {range.begin(), range.end()};
}