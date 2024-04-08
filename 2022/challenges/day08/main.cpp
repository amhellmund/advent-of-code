#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include <ranges>

#include <vector>

auto range = [](int begin, int end_exclusive) {
    if (end_exclusive < begin) {
        return std::views::iota(0, 0);
    }
    return std::views::iota(begin, end_exclusive);
};

auto revrange = [](int begin, int end_exclusive) {
    if (end_exclusive > begin) {
        return std::views::iota(0,0) | std::views::reverse;
    }
    return range(end_exclusive + 1, begin + 1) | std::views::reverse;
};

auto is_smaller = [](int ref_value) {
    return [ref_value](int value) {
        return value < ref_value;
    };
};

auto is_true = [](bool value) {
    return value == true;
};

class TreePlant {
public:
    static TreePlant loadFromFile (std::istream& stream) {
        std::vector<int> heights;
        int rows {0};
        std::string line;
        while (std::getline(stream, line)) {
            auto int_range = line | std::views::transform([](char c) {
                return c - '0';
            });
            heights.insert(heights.end(), int_range.begin(), int_range.end()); 
            rows++;
        }
        int columns {static_cast<int>(heights.size()) / rows};
        return TreePlant(std::move(heights), rows, columns);
    }

    int getRows() const {
        return rows_;
    }

    int getColumns() const {
        return columns_;
    }

    bool isVisible (int row, int column) const {
        auto height_for_fixed_row = std::views::transform([this,row](int column) {
            return this->getHeight(row, column);
        });
        
        auto height_for_fixed_column = std::views::transform([this,column](int row) {
            return this->getHeight(row, column);
        });

        auto current_height = getHeight(row, column);

        std::array<bool, 4> adj_trees_are_smaller = {
            std::ranges::all_of(range(0, row) | height_for_fixed_column, is_smaller(current_height)), // up
            std::ranges::all_of(range(row+1, rows_) | height_for_fixed_column, is_smaller(current_height)), // down
            std::ranges::all_of(range(0,column) | height_for_fixed_row, is_smaller(current_height)), // left
            std::ranges::all_of(range(column+1, columns_) | height_for_fixed_row, is_smaller(current_height)), // right
        };

        return std::ranges::any_of(adj_trees_are_smaller, is_true);
    }

    int computeScenicScore (int row, int column) const {
        auto current_height = getHeight(row, column);

        auto height_for_fixed_row = std::views::transform([this,row](int column) {
            return this->getHeight(row, column);
        });
        
        auto height_for_fixed_column = std::views::transform([this,column](int row) {
            return this->getHeight(row, column);
        });

        auto count_until_as_high = [this,current_height](auto range) {
            int count{0};
            for (const auto& value : range) {
                count++;
                if (value >= current_height) {
                    break;
                }
            }
            return count;
        };

        return (
            count_until_as_high(revrange(row-1, -1) | height_for_fixed_column) *
            count_until_as_high(range(row+1, rows_) | height_for_fixed_column) *
            count_until_as_high(revrange(column-1, -1) | height_for_fixed_row) *
            count_until_as_high(range(column+1, columns_) | height_for_fixed_row)
        );
    }

private:
    TreePlant (std::vector<int> tree_heights, int rows, int columns) : tree_heights_{std::move(tree_heights)}, rows_{rows}, columns_{columns} {
    }

    int getIndex(int row, int column) const {
        return row * columns_ + column;
    }

    int getHeight(int row, int column) const {
        return tree_heights_[getIndex(row, column)];
    }

    std::vector<int> tree_heights_;
    int rows_;
    int columns_;
};

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

    auto tree_plant = TreePlant::loadFromFile(file_stream);
    std::cout << std::format("Tree plant with dimensions: [{},{}]\n", tree_plant.getRows(), tree_plant.getColumns());

    int visible_trees {0};
    for (int i = 0; i < tree_plant.getRows(); ++i) {
        for (int j = 0; j < tree_plant.getColumns(); ++j) {
            if (tree_plant.isVisible(i, j)) {
                visible_trees++;
            }
        }
    }
    std::cout << std::format("Visible trees: {}\n", visible_trees);

    int max_scenic_score {0};
    for (int i = 0; i < tree_plant.getRows(); ++i) {
        for (int j = 0; j < tree_plant.getColumns(); ++j) {
            max_scenic_score = std::max(max_scenic_score, tree_plant.computeScenicScore(i, j));
        }
    }
    std::cout << std::format("Max scenic score: {}\n", max_scenic_score);
}