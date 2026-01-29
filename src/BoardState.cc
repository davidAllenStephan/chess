#include "../include/BoardState.h"
#include "../include/PositionMap.h"
#include "Piece.h"
#include <unordered_map>
#include <utility>

std::unordered_map<std::string, Piece *> init() {
        std::unordered_map<std::string, Piece *> data;
        for (int file = 0; file < 8; ++file) {
                for (int rank = 0; rank < 8; ++rank) {
                        std::string id = PositionMap::get({file, rank});
                        data.emplace(id, EMPTY_PIECE);
                }
        }
        return data;
}

BoardState::BoardState() {
        this->data = init();
};

void BoardState::load(std::unordered_map<std::pair<int, int>, Piece *, PairHash> map) {
        for (std::pair<std::pair<int, int>, Piece *> p : map) {
                BoardState::instance().data.insert_or_assign(PositionMap::get(p.first), p.second);
        }
        BoardState::updateAllPieces();
}

BoardState &BoardState::instance() {
        static BoardState instance;
        return instance;
}

Piece *BoardState::get(std::string id) {
        return BoardState::instance().data.at(id);
}

void BoardState::replace(std::string from, std::string to) {
        Piece *piece = BoardState::instance().data.at(from);
        if (!piece->actionTableContains(to)) {
                return;
        }
        BoardState::instance().data.at(from) = EMPTY_PIECE;
        piece->id = to;
        BoardState::instance().data.at(to) = piece;
}

void BoardState::updateAllPieces() {
        for (std::pair<std::string, Piece *> p : BoardState::instance().data) {
                if (p.second->label != Label::EMPTY) {
                        p.second->updateActionTable();
                }
        }
}

std::string BoardState::toString() {
        std::string out;
        for (int rank = 7; rank >= 0; --rank) {
                for (int file = 0; file < 8; ++file) {
                        std::string pos{
                            static_cast<char>('a' + file),
                            static_cast<char>('1' + rank)};
                        auto it = BoardState::instance().data.find(pos);
                        out += it->second->toString();
                        out += ' ';
                }
                out += '\n';
        }
        return out;
}
