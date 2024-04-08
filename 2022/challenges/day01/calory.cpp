#include <cstdlib>
#include <ranges>
#include <numeric>
#include <algorithm>

#include "calory.hpp"

RawData readElvesCaloryDataFromFile(std::ifstream &file_stream)
{
    RawData raw_data{};
    RawData::Index current_index{.start = 0, .end = 0};

    auto addIndexPotentially = [&raw_data](RawData::Index &index)
    {
        if (index.end > index.start)
        {
            raw_data.elves_indices.push_back(index);
            index = {.start = index.end,
                     .end = index.end};
        }
    };

    std::string input_line;
    while (std::getline(file_stream, input_line))
    {
        if (input_line.empty()) [[unlikely]]
        {
            addIndexPotentially(current_index);
        }
        else
        {
            raw_data.raw_calory_values.push_back(std::stoi(input_line));
            current_index.end++;
        }
    }
    addIndexPotentially(current_index);
    return raw_data;
}

std::vector<int> aggregateCaloriesPerElf(const RawData &raw_data)
{
    auto transformed_range = raw_data.elves_indices | std::ranges::views::transform([raw_data](const RawData::Index &elf_index)
                                                                                    { return std::accumulate(raw_data.raw_calory_values.cbegin() + elf_index.start, raw_data.raw_calory_values.cbegin() + elf_index.end, 0); });
    
    std::vector<int> result {transformed_range.begin(), transformed_range.end()};
    std::ranges::sort(result, [](int a, int b) { return a > b; });
    return result;
}