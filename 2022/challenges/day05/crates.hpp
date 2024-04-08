#include <istream>
#include <vector>
#include <stack>

using CratesStructure = std::vector<std::string>;

struct CratesMovement {
    int amount;
    int from;
    int to;
};

using CratesMovements = std::vector<CratesMovement>;

struct TaskExcercise {
    CratesStructure crates;
    CratesMovements movements;
};

TaskExcercise loadTaskExcerciseFromFile (std::istream& stream);

std::string computeStackEndConfiguration (const TaskExcercise& task);