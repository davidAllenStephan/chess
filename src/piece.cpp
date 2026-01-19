#ifndef PIECE_CPP
#define PIECE_CPP

#include "../include/piece.hpp"

piece::piece() {
        this->id = "";
        this->rank = 0;
        this->file = 0;
        this->value = 0;
        this->color = EMPTY;
        this->fen = "";
        this->move_mask = NULL;
        this->texture_id = 0;
}

piece::~piece() = default;

void piece::update_color(COLOR color) {
        this->color = color;
}

#endif
