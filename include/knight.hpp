#ifndef KNIGHT
#define KNIGHT

#include "movement_mask.hpp"
#include "piece.hpp"
class knight : public piece {
      public:
        knight(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 3;
                this->color = color;
                this->fen = color == WHITE ? "N" : "n";
                this->movement_mask= movement_mask::knight;
		this->capture_mask = this->movement_mask;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KNIGHT) : texture_manager::getOrLoad(BLACK_KNIGHT);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KNIGHT) : texture_manager::getOrLoad(BLACK_KNIGHT);
        }

};

#endif
