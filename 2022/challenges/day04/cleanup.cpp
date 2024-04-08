#include <string_view>
#include <regex>
#include <iostream>
#include <cassert>
#include <ranges>
#include <numeric>

#include "cleanup.hpp"

std::vector<int> getAssignment(int low, int high) {
    auto range = std::views::iota(low) | std::views::take(high-low+1) | std::views::common;
    return {range.begin(), range.end()};
}

SectionAssignment computeSectionAssignment (const std::string& assignment) {
    std::regex regexp {R"((\d+)-(\d+),(\d+)-(\d+))"};
    std::smatch matches;
    auto match_successful = std::regex_search(assignment, matches, regexp);
    assert(match_successful);
    return {
        .first = getAssignment(std::stoi(matches[1]), std::stoi(matches[2])),
        .second = getAssignment(std::stoi(matches[3]), std::stoi(matches[4])),
    };
}

SectionAssignments loadSectionAssignments(std::istream& stream) {
    SectionAssignments assignments{};
    std::string line;
    while (std::getline(stream, line)) {
        assignments.push_back(computeSectionAssignment(line));
    }
    return assignments;
}

int countSectionAssignmentsWithContainment (const SectionAssignments& assignments) {
    return std::ranges::count_if(assignments, [](const SectionAssignment& assignment) {
        return std::ranges::includes(assignment.first, assignment.second) or std::ranges::includes(assignment.second, assignment.first);
    });
}

int countOverlappingAssigments (const SectionAssignments& assignments) {
    return std::ranges::count_if(assignments, [](const SectionAssignment& assignment) {
        std::vector<int> intersection;
        std::ranges::set_intersection(assignment.first, assignment.second, std::back_inserter(intersection));
        return intersection.size() > 0;
    });
}