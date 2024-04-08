#include <vector>
#include <map>
#include <string>
#include <istream>

enum class HandShape {
    Rock = 0,
    Paper = 1,
    Scissor = 2,
};

enum class Winner {
    Player = 0,
    Opponent = 1,
    Draw = 2,
};

struct Game {
    HandShape hand_of_player;
    HandShape hand_of_opponent;
};

struct GameOpponentWinner {
    HandShape hand_of_opponent;
    Winner winner;
};

using Tournament = std::vector<Game>;
using TournamentOpponentWinner = std::vector<GameOpponentWinner>;
 
using HandShapeMapping = std::map<std::string, HandShape>;
using WinnerMapping = std::map<std::string, Winner>;

inline const HandShapeMapping DEFAULT_MAPPING_OPPONENT {
    {"A", HandShape::Rock},
    {"B", HandShape::Paper},
    {"C", HandShape::Scissor},
};

inline const HandShapeMapping DEFAULT_MAPPING_PLAYER {
    {"X", HandShape::Rock},
    {"Y", HandShape::Paper},
    {"Z", HandShape::Scissor},
};

inline const WinnerMapping DEFAULT_MAPPING_WINNER {
    {"X", Winner::Opponent},
    {"Y", Winner::Draw},
    {"Z", Winner::Player},
};

Winner getWinner (const Game& game);
int getPlayerPoints (const Game& game);
int getPlayerPoints (const std::vector<Game>& tournament);

Tournament readTournamentFromFile (std::istream& file_stream, const HandShapeMapping& opponent_mapping = DEFAULT_MAPPING_OPPONENT, const HandShapeMapping& player_mapping = DEFAULT_MAPPING_PLAYER);
TournamentOpponentWinner readTournamentOpponentWinnerFromFile (std::istream& file_stream, const HandShapeMapping& opponent_mapping = DEFAULT_MAPPING_OPPONENT, const WinnerMapping& winner_mapping = DEFAULT_MAPPING_WINNER);
Tournament convert (const TournamentOpponentWinner& tournament);