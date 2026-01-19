#include "piece.hpp"

#ifndef ROOK
#define ROOK

class rook : public piece {
      public:
        rook(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 5;
                this->color = color;
                this->fen = color == WHITE ? "R" : "r";
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_ROOK) : texture_manager::getOrLoad(BLACK_ROOK);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_ROOK) : texture_manager::getOrLoad(BLACK_ROOK);
        }
};

#endif
