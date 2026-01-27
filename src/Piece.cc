#include "../include/Piece.h"
#include "../include/ActionMask.h"
#include "../include/BoardState.h"
#include "../include/PositionMap.h"
#include <iostream>
#include <utility>
#include <vector>

Piece::Piece(Label label, Color color, int file, int rank) {
        this->label = label;
        this->color = color;
        this->pos.first = file;
        this->pos.second = rank;
}

Piece::~Piece() = default;

std::string Piece::toString() {
        if (color == Color::EMPTY) {
                return "-";
        }
        char c = label_fen.at(label);
        if (color == Color::WHITE) {
                c = static_cast<char>(std::toupper(c));
        }
        return std::string(1, c);
}

void Piece::printActionTable() {
        std::string out;
        out += this->toString();
        out += "\n";
        for (std::pair<std::string, Piece *> p : this->action_table) {
                out += p.first;
                out += ": ";
                out += p.second->toString();
                out += "\n";
        }
        std::cout << out << std::endl;
}

void Piece::updateActionTable() {
        this->action_table.clear();
        std::vector<std::pair<int, int>> mask = ActionMask::get(this->label);
        for (std::pair<int, int> action : mask) {
                int file = getFile() + action.first;
                int rank = getRank() + action.second;
                if ((rank < 0 || rank >= 8) || (file < 0 || file >= 8)) {
                        continue;
                }
                std::string id = PositionMap::get({file, rank});
                Piece *p = BoardState::get(id);
                this->action_table.insert({id, p});
        }
}

int Piece::getFile() {
        return this->pos.first;
}

int Piece::getRank() {
        return this->pos.second;
}

std::pair<int, int> Piece::getPos() {
        return this->pos;
}

void Piece::setFile(int file) {
        this->pos.first = file;
}

void Piece::setRank(int rank) {
        this->pos.second = rank;
}

void Piece::setPos(std::pair<int, int> p) {
        this->pos = p;
}

Piece *Piece::get(std::string position) {
        return this->action_table.at(position);
}

void Piece::play(std::string position) {
        if (this->action_table.count(position) != 0) {
                BoardState::replace(position, PositionMap::get(this->getPos()));
        }
}
