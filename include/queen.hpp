#ifndef QUEEN
#define QUEEN

#include "movement_mask.hpp"
#include "piece.hpp"
class queen : public piece {
      public:
        queen(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 9;
                this->color = color;
                this->fen = color == WHITE ? "Q" : "q";
                this->movement_mask = movement_mask::queen;
		this->capture_mask = this->movement_mask;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_QUEEN) : texture_manager::getOrLoad(BLACK_QUEEN);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_QUEEN) : texture_manager::getOrLoad(BLACK_QUEEN);
        }
};

#endif
