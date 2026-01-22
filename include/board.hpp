#ifndef BOARD_HPP
#define BOARD_HPP

#include "piece.hpp"
#include <cstdio>
#include <memory>
#include <unordered_map>

using namespace std;

class board {
      public:
        string placement[8][8];
        unordered_map<string, unique_ptr<piece>> pieces;

        void print_board() {
                for (const auto &piece : pieces) {
                        printf("%s, %i, %i\n", piece.second->fen.c_str(), piece.second->rank, piece.second->file);
                }
        }
        void draw_board(int window_width, int window_height);
        void draw_cell(int pos_x, int pos_y, int width, int height, int window_width, int window_height);
        void draw_texture(int texture_id, double pos_x, double pos_y, int window_width, int window_height);

        void handle_mouse(int button, int state, int x, int y, int window_width, int window_height);
        void handle_take_piece(string select_piece_id, string target_piece_id);
        void handle_select_piece(string target_piece_id);
        void handle_move_piece(string select_piece_id, int rank, int file);

        void replace_piece(string select_piece_id, string target_piece_id);
        void update_piece(string select_piece_id, int rank, int file);

        void insert_piece(unique_ptr<piece> p);
};

#endif
