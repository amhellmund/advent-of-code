#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include <numeric>

#include "rucksack.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << std::format("Usage: {} <input-file> [advanced]", argv[0]);
        std::exit(EXIT_FAILURE);
    }
    std::filesystem::path input_file = argv[1];

    std::ifstream file_stream{input_file, std::ifstream::in};
    if (not file_stream.is_open())
    {
        std::cerr << std::format("Unable to open input file {}", input_file.string());
        std::exit(EXIT_FAILURE);
    }

    const auto& rucksacks = loadRucksackPartsFromFile(file_stream);
    std::cout << std::format("Number of rucksacks: {}\n", rucksacks.size());

    auto priorities = computePriorities(rucksacks);
    std::cout << std::format("Total priority in rucksacks: {}\n", priorities);

    auto prioritities_by_3_elves = computePrioritiesBy3Elves(rucksacks);
    std::cout << std::format("Total priority in rucksacks by 3 elves: {}\n", prioritities_by_3_elves);
}