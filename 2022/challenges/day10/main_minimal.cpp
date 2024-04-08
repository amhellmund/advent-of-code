// The minimal solution tried to mimic Python as presented by:
// https://github.com/hyper-neutrino/advent-of-code/blob/main/2022/day10p1.py

#include <fstream>
#include <iostream>
#include <ranges>
#include <numeric>
#include <vector>

#include <number_crunching/ranges/stream.hpp>
#include <number_crunching/ranges/sequence.hpp>
#include <number_crunching/string/split.hpp>

int main(int argc, char *argv[])
{
    std::ifstream file_stream{argv[1], std::ifstream::in};
 
    auto range = nc::views::stream_linewise(file_stream) | std::views::transform([](std::string_view str) {
        return nc::split<std::string, int>(str, " ");
    });

    std::vector<int> cpu_cycles;
    int initial_value {1};
    std::ranges::for_each(range, [&cpu_cycles, &initial_value](const auto& data) {
        const auto& [op, operand] = data;
        if (op.starts_with("noop")) {
            cpu_cycles.push_back(initial_value);
        }
        else if (op.starts_with("addx")) {
            cpu_cycles.push_back(initial_value);
            cpu_cycles.push_back(initial_value);
            initial_value += operand;
        }
    });

    auto range_reduce = nc::views::sequence(19, cpu_cycles.size(), 40)
    | std::views::transform([cpu_cycles](int cycle) { 
        return cpu_cycles[cycle] * (cycle + 1);
    }) | std::views::common;
    std::cout << "Total signal strength: " << (int)std::reduce(range_reduce.begin(), range_reduce.end()) << "\n";
}