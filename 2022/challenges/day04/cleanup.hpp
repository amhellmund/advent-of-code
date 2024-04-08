#include <istream>
#include <vector>

struct SectionAssignment {
    std::vector<int> first;
    std::vector<int> second;
};

using SectionAssignments = std::vector<SectionAssignment>;

int countSectionAssignmentsWithContainment (const SectionAssignments& assignments);
int countOverlappingAssigments (const SectionAssignments& assignments);
SectionAssignments loadSectionAssignments (std::istream& stream);