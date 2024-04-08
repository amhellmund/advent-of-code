#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include <ranges>
#include <unordered_map>
#include <set>
#include <numeric>

#include <vector>
#include <array>

enum class OpCode {
    Noop = 0,
    Add,
};

struct Instruction {
    OpCode opcode;
    int operand{-1};
};

using Instructions = std::vector<Instruction>;

Instructions loadInstructionsFromFile (std::ifstream& file_stream) { 
    Instructions instructions {};
    std::string line;
    while (std::getline(file_stream, line)) {
        if (line.starts_with("noop")) {
            instructions.push_back({
                .opcode = OpCode::Noop,
            });
        }
        else if (line.starts_with("addx")) {
            instructions.push_back({
                .opcode = OpCode::Add,
                .operand = std::stoi(line.substr(5)),
            });
        }
    }
    return instructions;
}

class CPUSimulation {
public:
    struct CycleRegisterState {
        int value_at_start;
        int value_at_end;
    };

    CPUSimulation() {
        cycles_.push_back({
            .value_at_start = 1,
            .value_at_end = 1,
        });
    }

    int getPassedCycles () const {
        return cycles_.size() - 1;
    }

    CycleRegisterState getStateForCycle (int cycle) const {
        if (cycle <= 0) {
            throw std::runtime_error("Cycle must be positive");
        }
        return cycles_[cycle];
    }

    void printCycles () {
        for (int i = 0; i < cycles_.size(); ++i) {
            std::cout << std::format("Cycle[{}]: while = {}, end = {}\n", i, cycles_[i].value_at_start, cycles_[i].value_at_end);
        }
    }

    void runInstruction(const Instruction& instruction) {
        auto last_state_end_value = cycles_.back().value_at_end;
        switch (instruction.opcode) {
            case OpCode::Noop:
                cycles_.push_back({
                    .value_at_start = last_state_end_value,
                    .value_at_end = last_state_end_value,
                });
                break;
            case OpCode::Add:
                cycles_.push_back({
                    .value_at_start = last_state_end_value,
                    .value_at_end = last_state_end_value,
                });
                cycles_.push_back({
                    .value_at_start = last_state_end_value,
                    .value_at_end = last_state_end_value + instruction.operand,
                });
                break;
        }
    }

private:
    std::vector<CycleRegisterState> cycles_;
};


std::vector<std::string> obtainScreenContent (const CPUSimulation& simulation) {
    std::vector<std::string> screen_content;
    for (int row = 0; row < 6; ++row) {
        std::string screen_row{};
        for (int col = 0; col < 40; ++col) {
            int cycle = row * 40 + col + 1; // cycles start at 1
            auto [start, _] = simulation.getStateForCycle(cycle);
            if (std::abs(start - col) <= 1) {
                screen_row += "#";
            }
            else {
                screen_row += ".";
            }
        }
        screen_content.push_back(screen_row);
    }
    return screen_content;
}

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

    auto instructions = loadInstructionsFromFile(file_stream);
    std::cout << std::format("Number of instructions: {}\n", instructions.size());

    CPUSimulation simulation{};
    std::ranges::for_each(instructions, [&simulation](const auto& instruction) {
        simulation.runInstruction(instruction);
    });
    std::cout << std::format("Passed CPU cycles: {}\n", simulation.getPassedCycles());

    std::vector<int> cycles_to_consider {20, 60, 100, 140, 180, 220};
    auto range = cycles_to_consider | std::views::transform([simulation](int cycle) {
        const auto [start_value, _] = simulation.getStateForCycle(cycle);
        return start_value * cycle;
    });
    auto total_signal_strength = std::reduce(range.begin(), range.end());
    std::cout << std::format("Total signal strength: {}\n", total_signal_strength);

    const auto& screen_content = obtainScreenContent(simulation);
    for (const auto& screen_row : screen_content) {
        std::cout << screen_row << "\n";
    }
}