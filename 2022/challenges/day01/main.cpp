#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>

#include "calory.hpp"

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

    const auto &raw_data = readElvesCaloryDataFromFile(file_stream);
    std::cout << std::format("Number of Elves: {}\n", raw_data.elves_indices.size());

    auto calories_per_elf = aggregateCaloriesPerElf(raw_data);

    if (calories_per_elf.size() >= 1)
    {
        std::cout
            << std::format("Top calory count: {}\n", calories_per_elf[0]);
    }
    if (calories_per_elf.size() >= 3)
    {
        std::cout << std::format("Top 3 calory count: {}\n", calories_per_elf[0] + calories_per_elf[1] + calories_per_elf[2]);
    }
}