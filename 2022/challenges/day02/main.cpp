#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include <numeric>

#include "rock_paper_scissor.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << std::format("Usage: {} <input-file> [advanced]", argv[0]);
        std::exit(EXIT_FAILURE);
    }
    bool base_version = true;
    if (argc >= 3 and std::string{argv[2]} == "advanced" ) {
        base_version = false;
    }
    std::filesystem::path input_file = argv[1];

    std::ifstream file_stream{input_file, std::ifstream::in};
    if (not file_stream.is_open())
    {
        std::cerr << std::format("Unable to open input file {}", input_file.string());
        std::exit(EXIT_FAILURE);
    }

    Tournament tournament{};

    if (base_version) {
        std::cout << "Base-Version\n";
        tournament = readTournamentFromFile(file_stream);
    }
    else {
        std::cout << "Advanced-Version\n";
        const auto& tournament_opponent_winner = readTournamentOpponentWinnerFromFile(file_stream);
        tournament = convert(tournament_opponent_winner);
    }

    std::cout << std::format("Number of Games in Tournament: {}\n", tournament.size());
    const auto& player_points = getPlayerPoints(tournament);
    std::cout << std::format("Total points for Player: {}\n", player_points);
}