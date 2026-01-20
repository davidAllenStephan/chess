#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"
#include <uuid/uuid.h>
class king : public piece {
      public:
        king(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 0;
                this->color = color;
                this->fen = color == WHITE ? "K" : "k";
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KING) : texture_manager::getOrLoad(BLACK_KING);
                this->move_mask = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KING) : texture_manager::getOrLoad(BLACK_KING);
        }
};

#endif
