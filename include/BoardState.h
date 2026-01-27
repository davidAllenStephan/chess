#ifndef BOARD_STATE_H
#define BOARD_STATE_H

#include "PairHash.h"
#include "Piece.h"
#include <string>
#include <unordered_map>
#include <utility>

class BoardState {
      public:
        static BoardState &instance();
        static Piece *get(std::string);
        static void updateAllPieces();
        static void replace(std::string, std::string);
        static void load(std::unordered_map<std::pair<int, int>, Piece *, PairHash>);
        static std::string toString();

      private:
        std::unordered_map<std::string, Piece *> data;
        BoardState();
        BoardState(std::unordered_map<std::pair<int, int>, Piece *, PairHash>);
        BoardState(const BoardState &) = delete;
        BoardState &operator=(const BoardState &) = delete;
};

#endif
