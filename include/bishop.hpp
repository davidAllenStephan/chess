#ifndef BISHOP
#define BISHOP

#include "movement_mask.hpp"
#include "piece.hpp"

class bishop : public piece {
      public:
        bishop(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 3;
                this->color = color;
                this->fen = color == WHITE ? "B" : "b";
                this->movement_mask = movement_mask::bishop;
		this->capture_mask = this->movement_mask;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_BISHOP) : texture_manager::getOrLoad(BLACK_BISHOP);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_BISHOP) : texture_manager::getOrLoad(BLACK_BISHOP);
        }
};

#endif
