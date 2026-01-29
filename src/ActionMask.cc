#include "../include/ActionMask.h"
#include "BoardState.h"
#include "PositionMap.h"

const std::set<std::pair<int, int>> ActionMask::white_pawn = {{0, 1}, {0, 2}};
const std::set<std::pair<int, int>> ActionMask::black_pawn = {{0, -1}, {0, -2}};
const std::set<std::pair<int, int>> ActionMask::white_passant_pawn = {{0, 1}, {0, -1}, {0, 2}, {0, -2}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
const std::set<std::pair<int, int>> ActionMask::black_passant_pawn = {{0, 1}, {0, -1}, {0, 2}, {0, -2}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
const std::set<std::pair<int, int>> ActionMask::knight = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
const std::set<std::pair<int, int>> ActionMask::bishop = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
const std::set<std::pair<int, int>> ActionMask::rook = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
const std::set<std::pair<int, int>> ActionMask::queen = {{0, 1}, {1, 0}, {1, 1}, {0, -1}, {-1, 0}, {-1, -1}, {1, -1}, {-1, 1}};
const std::set<std::pair<int, int>> ActionMask::king = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
const std::unordered_map<Label, std::set<std::pair<int, int>>> ActionMask::mask = {{Label::KNIGHT, knight}, {Label::BISHOP, bishop}, {Label::ROOK, rook}, {Label::QUEEN, queen}, {Label::KING, king}};

std::set<std::pair<int, int>> ActionMask::get(Piece *p) {
        if (p->label == Label::PAWN) {
                return p->color == Color::WHITE ? white_pawn : black_pawn;
        }
        return mask.at(p->label);
}

std::set<std::pair<int, int>> ActionMask::findMinMax(Piece *p) {
        std::set<std::pair<int, int>> minMax;
        std::set<std::pair<int, int>> peers = collectPeers(p);
        std::set<std::pair<int, int>> mask = get(p);
        for (std::pair<int, int> peer : peers) {
                if (mask.count(peer) == 0) {
                        continue;
                }
        }
        return minMax;
}

std::set<std::pair<int, int>> ActionMask::collectPeers(Piece *p) {
        std::set<std::pair<int, int>> mask = get(p);
        int file = PositionMap::getId(p->id).first;
        int rank = PositionMap::getId(p->id).second;
        for (std::pair<int, int> pos : mask) {
                if (BoardState::get(PositionMap::get(pos))->id == "") {
                        continue;
                }
                mask.insert({file, rank});
        }
        return mask;
}
