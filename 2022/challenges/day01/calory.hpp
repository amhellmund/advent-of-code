#include <fstream>
#include <vector>

struct RawData final
{
    struct Index final
    {
        int start{-1};
        int end{-1};
    };

    std::vector<int> raw_calory_values;
    std::vector<Index> elves_indices;
};

RawData readElvesCaloryDataFromFile(std::ifstream &file_stream);
std::vector<int> aggregateCaloriesPerElf(const RawData &raw_data);