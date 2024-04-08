#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>

#include "crates.hpp"

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

    const auto& task_excercise = loadTaskExcerciseFromFile(file_stream);
    std::cout << std::format("Number of stacks: {}\n", task_excercise.crates.size());
    std::cout << std::format("Number of movements: {}\n", task_excercise.movements.size());

    const auto& end_configuration = computeStackEndConfiguration(task_excercise);
    std::cout << std::format("End Configuration: {}\n", end_configuration);
}