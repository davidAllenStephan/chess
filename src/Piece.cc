#include "../include/Piece.h"
#include "../include/ActionMask.h"
#include "../include/BoardState.h"
#include "../include/PositionMap.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

Piece::Piece(Label label, Color color, std::string id) {
        this->label = label;
        this->color = color;
        this->id = id;
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
        for (const std::pair<std::string, Piece *> &p : this->action_table) {
                out += p.first;
                out += ": ";
                out += p.second->toString();
                out += "\n";
        }
        std::cout << out << std::endl;
}

void Piece::updateActionTable() {
        this->action_table.clear();
        std::set<std::pair<int, int>> mask = ActionMask::get(this);
        std::pair<int, int> position = PositionMap::getId(this->id);
        for (std::pair<int, int> direction : mask) {
                int i_file = position.first + direction.first;
                int i_rank = position.second + direction.second;
                while (i_file < 8 && i_rank < 8 && i_file >= 0 && i_rank >= 0) {
                        std::string target_id = PositionMap::get({i_file, i_rank});
                        Piece *p = BoardState::get(target_id);
                        if (p->label != Label::EMPTY) {
                                break;
                        }
                        this->action_table.insert({target_id, p});
                        if ((this->label == Label::PAWN) || (this->label == Label::KING) || (this->label == Label::KNIGHT)) {
                                break;
                        }
                        i_file += direction.first;
                        i_rank += direction.second;
                }
        }
}

bool Piece::actionTableContains(std::string id) {
        return this->action_table.count(id) == 0 ? false : true;
}

Piece *Piece::get(std::string id) {
        return this->action_table.at(id);
}
