#ifndef ACTION_MASK_H
#define ACTION_MASK_H

#include "Piece.h"
#include <set>
#include <unordered_map>
#include <utility>

class ActionMask {
        static const std::set<std::pair<int, int>> white_pawn;
        static const std::set<std::pair<int, int>> black_pawn;
        static const std::set<std::pair<int, int>> white_passant_pawn;
        static const std::set<std::pair<int, int>> black_passant_pawn;
        static const std::set<std::pair<int, int>> knight;
        static const std::set<std::pair<int, int>> bishop;
        static const std::set<std::pair<int, int>> rook;
        static const std::set<std::pair<int, int>> queen;
        static const std::set<std::pair<int, int>> king;
        static const std::unordered_map<Label, std::set<std::pair<int, int>>> mask;

      public:
        static std::set<std::pair<int, int>> get(Piece *p);
        static std::set<std::pair<int, int>> findMinMax(Piece *p);
        static std::set<std::pair<int, int>> collectPeers(Piece *p);
};

#endif
