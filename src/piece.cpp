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
        this->move_mask = {};
        this->texture_id = 0;
}

void piece::update_color(COLOR color) {
        this->color = color;
}

#endif
