#ifndef PIECE_CPP
#define PIECE_CPP

#include "../include/piece.hpp"
#include "../include/uuid.hpp"

piece::piece() {
        this->id = get_uuid();
        this->rank = 0;
        this->file = 0;
        this->value = 0;
        this->color = EMPTY;
        this->fen = "";
        this->moved = 0;
        this->two_square = false;
        this->movement_mask = {};
        this->special_movement_mask = {};
        this->capture_mask = {};
        this->special_capture_mask = {};
        this->texture_id = 0;
}

void piece::update_color(COLOR color) {
        this->color = color;
}

pair<int, int> piece::valid_move(int rank, int file) {
        for (auto p : this->movement_mask) {
                if ((p.first + this->rank) == rank && (p.second + this->file) == file) {
                        return {p.first, p.second};
                }
        }
        return {0, 0};
}

pair<int, int> piece::valid_special_move(int rank, int file) {
        for (auto p : this->special_movement_mask) {
                if ((p.first + this->rank) == rank && (p.second + this->file) == file) {
                        return {p.first, p.second};
                }
        }
        return {0, 0};
}

pair<int, int> piece::valid_capture(int rank, int file) {
        for (auto p : this->capture_mask) {
                if ((p.first + this->rank) == rank && (p.second + this->file) == file) {
                        return {p.first, p.second};
                }
        }
        return {0, 0};
}

pair<int, int> piece::valid_special_capture(int rank, int file) {
        for (auto p : this->special_capture_mask) {
                if ((p.first + this->rank) == rank && (p.second + this->file) == file) {
                        return {p.first, p.second};
                }
        }
        return {0, 0};
}

#endif
