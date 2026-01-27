#ifndef ACTION_MASK_H
#define ACTION_MASK_H

#include "Piece.h"
#include <unordered_map>
#include <utility>
#include <vector>

class ActionMask {
        static const std::vector<std::pair<int, int>> pawn;
        static const std::vector<std::pair<int, int>> knight;
        static const std::vector<std::pair<int, int>> bishop;
        static const std::vector<std::pair<int, int>> rook;
        static const std::vector<std::pair<int, int>> queen;
        static const std::vector<std::pair<int, int>> king;
        static const std::unordered_map<Label, std::vector<std::pair<int, int>>> mask;

      public:
        static std::vector<std::pair<int, int>> get(Label);
};

#endif
