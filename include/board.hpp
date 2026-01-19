#ifndef BOARD_HPP
#define BOARD_HPP

#include "piece.hpp"
#include <cstdio>
#include <unordered_map>

using namespace std;

class board {
      public:
        string placement[8][8];
        unordered_map<string, piece *> pieces;
        void print_board() {
                for (const auto &piece : pieces) {
                        printf("%s, %i, %i\n", piece.second->fen.c_str(), piece.second->rank, piece.second->file);
                }
        }
        void draw_board(int window_width, int window_height);
        void draw_cell(int pos_x, int pos_y, int width, int height, int window_width, int window_height);
        void draw_texture(int texture_id, double pos_x, double pos_y, int window_width, int window_height);
        void handle_mouse(int button, int state, int x, int y, int window_width, int window_height);
        void insert_piece_map(piece *p);
        void insert_placement(piece *p);
};

#endif
