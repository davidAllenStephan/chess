#ifndef PAWN
#define PAWN
#include "piece.hpp"

class pawn : public piece {
      public:
        pawn(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 1;
                this->color = color;
                this->fen = color == WHITE ? "P" : "p";
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_PAWN) : texture_manager::getOrLoad(BLACK_PAWN);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_PAWN) : texture_manager::getOrLoad(BLACK_PAWN);
        }
};

#endif
