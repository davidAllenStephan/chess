#ifndef KING_HPP
#define KING_HPP

#include "movement_mask.hpp"
#include "piece.hpp"
#include <cstdlib>
#include <uuid/uuid.h>

class king : public piece {
      public:
        king(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 0;
                this->color = color;
                this->fen = color == WHITE ? "K" : "k";
                this->movement_mask = movement_mask::king;
                this->capture_mask = this->movement_mask;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KING) : texture_manager::getOrLoad(BLACK_KING);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KING) : texture_manager::getOrLoad(BLACK_KING);
        }

};

#endif
