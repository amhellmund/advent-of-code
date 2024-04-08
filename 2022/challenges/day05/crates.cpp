#include "crates.hpp"

#include <ranges>
#include <string_view>
#include <iostream>
#include <format>
#include <cassert>
#include <regex>

CratesStructure loadCratesStructure (std::istream& stream) {
    std::string line;
    std::vector<std::string> crates_buffer;
    while (std::getline(stream, line) && not line.empty()) {
        crates_buffer.push_back(line);
    }
    // get number of stacks (last line in the buffer)
    std::string_view stack_numbers {crates_buffer.back()};
    int number_of_stacks = std::stoi(stack_numbers.substr(stack_numbers.find_last_not_of(" "), 1).data());
    
    auto position_range = std::views::iota(0, number_of_stacks) | std::views::transform([](int value) {
        return 1 + value * 4; // the first character starts in column 2 --> index 1
    });

    CratesStructure result{static_cast<std::size_t>(number_of_stacks)};

    // iterate from the second last line in creates_buffer to the beginning
    for (int i = static_cast<int>(crates_buffer.size()) - 2; i >= 0; --i) {
        std::string_view content {crates_buffer[i]};
        for (const auto [index, pos] : std::views::zip(std::views::iota(0), position_range)) {
            if (content[pos] >= 'A' and content[pos] <= 'Z') {
                result[index].push_back(content[pos]);
            }
        }
    }
    return result;
}

CratesMovements loadMovements (std::istream& stream) {
    CratesMovements movements;
    std::string line;
    std::regex regexp {R"(move (\d+) from (\d+) to (\d+))"};
    while (std::getline(stream, line) && not line.empty()) {
        std::smatch matches;
        auto match_successful = std::regex_search(line, matches, regexp);
        assert(match_successful);
        movements.push_back({
            .amount = std::stoi(matches[1]),
            .from = std::stoi(matches[2]) - 1,
            .to = std::stoi(matches[3]) - 1,
        });
    }
    return movements;
}

TaskExcercise loadTaskExcerciseFromFile (std::istream& stream) {
    return {
        .crates = loadCratesStructure(stream),
        .movements = loadMovements(stream),
    };
}

std::string computeStackEndConfiguration (const TaskExcercise& task) {
    auto crates = task.crates;
    for (const auto [amount, from, to] : task.movements) {
        std::ranges::for_each(crates[from].substr(crates[from].size() - amount), [&to_str=crates[to]](char ch) {
            to_str.push_back(ch);
        });
        std::ranges::for_each(std::views::iota(0, amount), [&from_str=crates[from]](auto _) {
            from_str.pop_back();
        });
    }
    auto end_configuration_range = crates | std::views::transform([](const auto& stack) {
        return stack.back();
    });
    return {end_configuration_range.begin(), end_configuration_range.end()};
}