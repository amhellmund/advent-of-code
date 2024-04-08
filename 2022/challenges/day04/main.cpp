#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include <numeric>

#include "cleanup.hpp"

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

    const auto& assignments = loadSectionAssignments(file_stream);
    std::cout << std::format("Number of assignments: {}\n", assignments.size());

    const auto assignment_containment_count = countSectionAssignmentsWithContainment (assignments);
    std::cout << std::format("Number of contained assignments: {}\n", assignment_containment_count);

    const auto overlap_assignment_count = countOverlappingAssigments(assignments);
    std::cout << std::format("Number of overlapping assignments: {}\n", overlap_assignment_count);
}