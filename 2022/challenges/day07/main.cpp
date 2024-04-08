#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include <ranges>
#include <numeric>

struct CommandExecution {
    std::string commandline;
    std::vector<std::string> command_output;
};

using CommandExecutions = std::vector<CommandExecution>;

CommandExecutions loadCommandExecutionsFromFile (std::ifstream& stream) {
    CommandExecutions executions{};
    std::string line;
    while (std::getline(stream, line)) {
        if (line.starts_with("$")) {
            executions.push_back({
                .commandline = line.substr(2),
            });
        }
        else {
            executions.back().command_output.push_back(line);
        }
    }
    return executions;
}

struct Directory {
    std::string name;
    int index;
    std::unordered_map<std::string, int> files;
    std::unordered_map<std::string, int> subdirectory_indices;
};

using Directories = std::vector<Directory>;

Directories getDirectoryTree (const CommandExecutions& executions) {
    Directories dir_tree {{.name = "/", .index = 0}};
    std::stack<int> current_directory;
    
    for (const auto& [cmdline, cmd_output] : executions) {
        if (cmdline.starts_with("cd")) {
            const auto& subdir = cmdline.substr(3);
            if (subdir == "/") {
                current_directory.push(0);
            }
            else if (subdir == "..") {
                current_directory.pop();
            }
            else {
                current_directory.push(dir_tree[current_directory.top()].subdirectory_indices.at(subdir));
            }
        }
        else if (cmdline.starts_with("ls")) {
            for (const auto& output : cmd_output) {
                if (output.starts_with("dir")) {
                    const auto& subdir = output.substr(4);
                    dir_tree.push_back({.name = subdir, .index = static_cast<int>(dir_tree.size())});
                    dir_tree[current_directory.top()].subdirectory_indices[subdir] = static_cast<int>(dir_tree.size() - 1);
                }
                else {
                    auto seperator_pos = output.find(" ");
                    const auto& filename = output.substr(seperator_pos + 1);
                    const auto filesize = std::stoi(output.substr(0, seperator_pos));
                    dir_tree[current_directory.top()].files[filename] = filesize;
                }
            }
        }
    }
    return dir_tree;
}

std::vector<int> computeDirectorySizes (const Directories& dirs) {
    std::vector<int> dir_sizes;
    dir_sizes.resize(dirs.size());
    std::ranges::for_each(dirs | std::views::reverse, [&dir_sizes](const Directory& dir) {
        // dir_sizes[dir.index] += dir.files | std::views::values | std::views::reduce;
        auto files_range = dir.files | std::views::transform([](const auto& element) {
            return element.second;
        });
        dir_sizes[dir.index] += std::reduce(files_range.begin(), files_range.end());
        // dir_sizes[dir.index] += dir.subdirectory_indices | std::views::values | std::views::transform([dir_sizes](int index) {
        //   return dir_sizes[index];   
        //})
        auto subdir_sizes_range = dir.subdirectory_indices | std::views::transform([](const auto& element) {
            return element.second;
        }) | std::views::transform([dir_sizes](int index) {
            return dir_sizes[index];
        });
        dir_sizes[dir.index] += std::reduce(subdir_sizes_range.begin(), subdir_sizes_range.end());
    });
    return dir_sizes;
}


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

    const auto& executions = loadCommandExecutionsFromFile(file_stream);
    std::cout << std::format("Number of executions: {}\n", executions.size());

    const auto& dir_tree = getDirectoryTree(executions);
    const auto& dir_sizes = computeDirectorySizes(dir_tree);
    std::cout << std::format("Number of directories: {} ({})\n", dir_tree.size(), dir_sizes.size());

    // accumulate all the directories below 100000
    auto dir_size_below_threshold_range = dir_sizes | std::views::filter([](int value) {
        return value < 100'000;
    });
    auto accumulated_dir_size_below_threshold = std::reduce(dir_size_below_threshold_range.begin(), dir_size_below_threshold_range.end());

    std::cout << std::format("Accumulated size below threshold of 100,000: {}\n", accumulated_dir_size_below_threshold);

    int space_to_be_freed = dir_sizes[0] - 40'000'000;
    std::cout << std::format("Space to be freed: {}\n", space_to_be_freed);

    auto dir_to_be_deleted_range = dir_sizes | std::views::filter([space_to_be_freed](int value) { 
        return value > space_to_be_freed;
    });
    int dir_with_min_size = *std::ranges::min_element(dir_to_be_deleted_range);
    std::cout << std::format("Directory with minimal size to fulfil space requirements: {}\n", dir_with_min_size);
}