#include "rucksack.hpp"
#include <cassert>
#include <algorithm>
#include <numeric>
#include <set>
#include <iostream>
#include <format>
#include <ranges>

struct RucksackParts {
    std::string left;
    std::string right;
};

RucksackParts splitRucksack(const Rucksack& rucksack) {
    assert(rucksack.size() % 2 == 0);
    return {
        .left = rucksack.substr(0, rucksack.size() / 2),
        .right = rucksack.substr(rucksack.size() / 2),
    };
}

int computePriority (char ch) {
    if (ch >= 'a' and ch <= 'z') {
        return ch - 'a' + 1;
    }
    else if (ch >= 'A' and ch <= 'Z') {
        return ch - 'A' + 27;
    }
    else {
        return 0;
    }
}

Rucksack intersect (const Rucksack& left, const Rucksack& right) {
    std::set<char> left_set {left.cbegin(), left.cend()};
    std::set<char> right_set {right.cbegin(), right.cend()};
    std::set<char> intersection;
    std::ranges::set_intersection(left_set, right_set, std::inserter(intersection, intersection.begin()));
    return {intersection.cbegin(), intersection.cend()};
}

char findSharedItemTypeInParts (const Rucksack& rucksack) {
    const auto& [left, right] = splitRucksack(rucksack);
    const auto& intersection = intersect(left, right);
    assert(intersection.size() == 1);
    return intersection[0];
}

char findSharedItemType (const Rucksack& r1, const Rucksack& r2, const Rucksack& r3) {
    const auto& intersection = intersect(r1, intersect(r2, r3));
    assert(intersection.size() == 1);
    return *intersection.cbegin();
}

int computePriorities (const Rucksacks& rucksacks) {
    return std::accumulate(rucksacks.cbegin(), rucksacks.cend(), 0, [](int value, const Rucksack& rucksack) {
        return value + computePriority(findSharedItemTypeInParts(rucksack)); 
    });
}

int computePrioritiesBy3Elves (const Rucksacks& rucksacks) {
    // could be simplified as
    // rucksacks | std::views::chunk(3) | std::ranges::accumulate | ...
    int priority {0};
    for (auto i = 0LU; i < rucksacks.size(); i += 3) {
        priority += computePriority(findSharedItemType(rucksacks[i], rucksacks[i+1], rucksacks[i+2]));
    }
    return priority;
}

Rucksacks loadRucksackPartsFromFile(std::istream& stream) {
    Rucksacks rucksacks{};
    std::string line;
    while (std::getline(stream, line)) {
        rucksacks.push_back(line);
    }
    return rucksacks;
}