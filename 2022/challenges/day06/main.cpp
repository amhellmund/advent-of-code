#include <format>
#include <iostream>
#include <set>
#include <string_view>

int computeLengthToEndOfStartOfPacketMarker (std::string_view input, int sync_length);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << std::format("Usage: {} <sync-length> <input-string>", argv[0]);
        std::exit(EXIT_FAILURE);
    }
    int synchronization_length = std::stoi(argv[1]);
    if (synchronization_length < 0) {
        std::cerr << std::format("Error: synchronization length must be positive (> 0), given: {}\n", synchronization_length);
        std::exit(EXIT_FAILURE);
    }
    std::string input_string = argv[2];
    if (input_string.size() < synchronization_length) {
        std::cerr << std::format("Error: minimal length of input string must be {}!", synchronization_length);
        std::exit(EXIT_FAILURE);
    }

    std::cout << std::format("Length of input string: {}\n", input_string.size());
    const auto length_to_end_of_packet = computeLengthToEndOfStartOfPacketMarker(input_string, synchronization_length);

    std::cout << std::format("Length to end of Start-of-Packet Marker: {}\n", length_to_end_of_packet);
}

bool areCharactersUnique (std::string_view str) {
    std::set<int> chars{str.cbegin(), str.cend()};
    return chars.size() == str.length();
}

int computeLengthToEndOfStartOfPacketMarker (std::string_view input, int sync_length) {
    for (int i = 0; i <= input.length() - sync_length; ++i) {
        auto substr = input.substr(i, sync_length);
        if (areCharactersUnique(substr)) {
            return i + sync_length;
        }
    }
    return -1;
}