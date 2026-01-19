#ifndef KNIGHT
#define KNIGHT

#include "piece.hpp"
class knight : public piece {
      public:
        knight(int rank, int file, COLOR color) {
                this->rank = rank;
                this->file = file;
                this->value = 3;
                this->color = color;
                this->fen = color == WHITE ? "N" : "n";
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KNIGHT) : texture_manager::getOrLoad(BLACK_KNIGHT);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_KNIGHT) : texture_manager::getOrLoad(BLACK_KNIGHT);
        }
};

#endif
