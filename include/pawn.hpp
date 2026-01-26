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
                this->two_square = false;
                this->moved = 0;
                if (color == WHITE) {
                        this->movement_mask = {{1, 0}};
                        this->special_movement_mask = {{1, 0}, {2, 0}};
                        this->capture_mask = {{1, 1}, {1, -1}};
                        this->special_capture_mask = {{0, 1}, {0, -1}};
                } else if (color == BLACK) {
                        this->movement_mask = {{-1, 0}};
                        this->special_movement_mask = {{-1, 0}, {-2, 0}};
                        this->capture_mask = {{-1, 1}, {-1, -1}};
                        this->special_capture_mask = {{0, 1}, {0, -1}};
                } else {
                        this->movement_mask = {{}};
                        this->capture_mask = {{}};
                        this->special_capture_mask = {{}};
                        this->special_movement_mask = {{}};
                }
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_PAWN) : texture_manager::getOrLoad(BLACK_PAWN);
        }

        void update_color(COLOR color) override {
                this->color = color;
                this->texture_id = color == WHITE ? texture_manager::getOrLoad(WHITE_PAWN) : texture_manager::getOrLoad(BLACK_PAWN);
        }

        pair<int, int> valid_move(int rank, int file) override {
                for (auto p : moved == 0 ? this->special_movement_mask : this->movement_mask) {
                        if ((p.first + this->rank) == rank && (p.second + this->file) == file) {
                                if (abs(p.first) == 2) {
                                        this->two_square = true;
                                }
                                return {p.first, p.second};
                        }
                }
                return {0, 0};
        }
};

#endif
