#include <string>
#include <vector>
#include <istream>

using Rucksack = std::string;
using Rucksacks = std::vector<Rucksack>;

int computePriorities (const Rucksacks& rucksacks);
int computePrioritiesBy3Elves (const Rucksacks& rucksacks);
Rucksacks loadRucksackPartsFromFile (std::istream& stream);