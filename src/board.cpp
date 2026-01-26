#ifndef BOARD_CPP
#define BOARD_CPP

#include "../include/board.hpp"
#include "../include/uuid.hpp"
#include "state_manager.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <cstdlib>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

void draw_square(double pos_x, double pos_y, double width, double height, double window_width, double window_height) {
        pos_x = pos_x * width;
        pos_y = pos_y * width;
        pos_x -= window_width;
        pos_y -= window_height;
        vector<array<double, 2>> vertices = {
            {pos_x, pos_y},
            {pos_x, pos_y + height},
            {pos_x + width, pos_y + height},
            {pos_x + width, pos_y}};
        glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i++) {
                glVertex2d(vertices[i][0] / window_width, vertices[i][1] / window_height);
        }
        glEnd();
}

void draw_overlay(double pos_x, double pos_y, double width, double height, double window_width, double window_height) {
        pos_x = pos_x * width;
        pos_y = pos_y * width;
        pos_x -= window_width;
        pos_y -= window_height;
        vector<array<double, 2>> vertices = {
            {pos_x, pos_y},
            {pos_x, pos_y + height},
            {pos_x + width, pos_y + height},
            {pos_x + width, pos_y}};
        glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i++) {
                glVertex2d(vertices[i][0] / window_width, vertices[i][1] / window_height);
        }
        glEnd();
}

void board::draw_board(int window_width, int window_height) {
        double board_width = window_width * 1.5;
        double cell_scale = board_width / 8;
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (i % 2 == 0) {
                                if (j % 2 == 0) {
                                        glColor3f(50.0 / 255, 100.0 / 255, 72.0 / 255);
                                } else {
                                        glColor3f(238.0 / 255, 238.0 / 255, 234.0 / 255);
                                }
                        } else {
                                if (j % 2 == 0) {
                                        glColor3f(238.0 / 255, 238.0 / 255, 234.0 / 255);
                                } else {
                                        glColor3f(50.0 / 255, 100.0 / 255, 72.0 / 255);
                                }
                        }
                        draw_square(i, j, cell_scale, cell_scale, window_width, window_height);
                }
        }

        string select_piece_id;
        if ((select_piece_id = state_manager::instance().selected) != "") {
                int select_piece_rank = this->pieces.at(select_piece_id)->rank;
                int select_piece_file = this->pieces.at(select_piece_id)->file;
                glColor3f(1, 0, 0);
                draw_square(select_piece_file, select_piece_rank, cell_scale, cell_scale, window_width, window_height);
        }
        for (const auto &piece : this->pieces) {
                draw_texture(piece.second->texture_id, piece.second->file, piece.second->rank, window_width, window_height);
        }
        glFlush();
}

void board::draw_texture(int texture_id, double pos_x, double pos_y, int window_width, int window_height) {
        glColor3f(1, 1, 1);

        double board_width = window_width * 1.5;
        double cell_scale = board_width / 8;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glBegin(GL_QUADS);

        pos_x = pos_x * cell_scale;
        pos_y = pos_y * cell_scale;
        pos_x -= window_width;
        pos_y -= window_height;

        vector<array<float, 2>> texture_vertices = {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f}};

        vector<array<double, 2>> vertices = {
            {pos_x, pos_y},
            {pos_x, pos_y + cell_scale},
            {pos_x + cell_scale, pos_y + cell_scale},
            {pos_x + cell_scale, pos_y}};

        for (int i = 0; i < vertices.size(); i++) {
                glTexCoord2f(texture_vertices[i][0], texture_vertices[i][1]);
                glVertex2f(vertices[i][0] / window_width, vertices[i][1] / window_height);
        }

        glEnd();
        glDisable(GL_TEXTURE_2D);
}

void draw_places(piece *p) {
}

void board::replace_piece(string select_piece_id, string target_piece_id) {
        int select_piece_rank = this->pieces.at(select_piece_id)->rank;
        int select_piece_file = this->pieces.at(select_piece_id)->file;
        int target_piece_rank = this->pieces.at(target_piece_id)->rank;
        int target_piece_file = this->pieces.at(target_piece_id)->file;
        this->placement[select_piece_rank][select_piece_file] = "";
        this->placement[target_piece_rank][target_piece_file] = select_piece_id;
        this->pieces.at(select_piece_id)->rank = target_piece_rank;
        this->pieces.at(select_piece_id)->file = target_piece_file;
}

void board::update_piece(string select_piece_id, int rank, int file) {
        int select_piece_rank = this->pieces.at(select_piece_id)->rank;
        int select_piece_file = this->pieces.at(select_piece_id)->file;
        this->placement[select_piece_rank][select_piece_file] = "";
        this->placement[rank][file] = select_piece_id;
        this->pieces.at(select_piece_id)->rank = rank;
        this->pieces.at(select_piece_id)->file = file;
}

void board::handle_take_piece(string select_piece_id, string target_piece_id) {
        string select_piece_fen = this->pieces.at(select_piece_id)->fen;
        int target_piece_rank = this->pieces.at(target_piece_id)->rank;
        int target_piece_file = this->pieces.at(target_piece_id)->file;
        pair<int, int> valid_move;
        if ((valid_move = this->pieces.at(select_piece_id)->valid_capture(target_piece_rank, target_piece_file)) == (pair<int, int>){0, 0}) {
                return;
        }
        if (this->pieces.at(select_piece_id)->fen != "N" && this->pieces.at(select_piece_id)->fen != "n") {
                if (!block_piece(select_piece_id, valid_move)) {
                        return;
                }
        }
        replace_piece(select_piece_id, target_piece_id);
        this->pieces.erase(target_piece_id);
        state_manager::instance().selected = "";
        this->pieces.at(select_piece_id)->moved++;
}

void board::handle_special_take_piece(string select_piece_id, string target_piece_id) {
        string select_piece_fen = this->pieces.at(select_piece_id)->fen;
        int target_piece_rank = this->pieces.at(target_piece_id)->rank;
        int target_piece_file = this->pieces.at(target_piece_id)->file;
        pair<int, int> valid_move;
        if ((valid_move = this->pieces.at(select_piece_id)->valid_special_capture(target_piece_rank, target_piece_file)) == (pair<int, int>){0, 0}) {
                return;
        }
        if (this->pieces.at(select_piece_id)->fen != "N" && this->pieces.at(select_piece_id)->fen != "n") {
                if (!block_piece(select_piece_id, valid_move)) {
                        return;
                }
        }
        replace_piece(select_piece_id, target_piece_id);
        this->pieces.erase(target_piece_id);
        state_manager::instance().selected = "";
        this->pieces.at(select_piece_id)->moved++;
}

void board::handle_select_piece(string target_piece_id) {
        state_manager::instance().selected = target_piece_id;
}

bool board::block_piece(string select_piece_id, pair<int, int> valid_move) {
        int select_rank = this->pieces.at(select_piece_id)->rank;
        int select_file = this->pieces.at(select_piece_id)->file;
        vector<pair<int, int>> paths;
        for (int i = 1; i < (abs(valid_move.first) >= abs(valid_move.second) ? abs(valid_move.first) : abs(valid_move.second)); i++) {
                paths.push_back({valid_move.first == 0 ? 0 : valid_move.first < 0 ? (-1 * (i % valid_move.first))
                                                                                  : i % valid_move.first,
                                 valid_move.second == 0 ? 0 : valid_move.second < 0 ? (-1 * (i % valid_move.second))
                                                                                    : i % valid_move.second});
        }
        int j = 0;
        for (pair<int, int> path : paths) {
                j++;
        }
        for (pair<int, int> path : paths) {
                if (this->placement[select_rank + path.first][select_file + path.second] != "") {
                        return false;
                }
        }
        return true;
}

void board::handle_move_piece(string select_piece_id, int rank, int file) {
        string piece_fen = this->pieces.at(select_piece_id)->fen;
        int piece_moved = this->pieces.at(select_piece_id)->moved;

        pair<int, int> valid_move;
        if ((valid_move = this->pieces.at(select_piece_id)->valid_move(rank, file)) == (pair<int, int>){0, 0}) {
                return;
        }
        if (piece_fen != "N" && piece_fen != "n") {
                if (!block_piece(select_piece_id, valid_move)) {
                        return;
                }
        }
        update_piece(select_piece_id, rank, file);
        state_manager::instance().selected = "";
        this->pieces.at(select_piece_id)->moved++;
}

void board::handle_special_move_piece(string select_piece_id, int rank, int file) {
        string piece_fen = this->pieces.at(select_piece_id)->fen;
        int piece_moved = this->pieces.at(select_piece_id)->moved;

        pair<int, int> valid_move;
        if ((valid_move = this->pieces.at(select_piece_id)->valid_move(rank, file)) == (pair<int, int>){0, 0}) {
                return;
        }
        if (piece_fen != "N" && piece_fen != "n") {
                if (!block_piece(select_piece_id, valid_move)) {
                        return;
                }
        }
        update_piece(select_piece_id, rank, file);
        state_manager::instance().selected = "";
        this->pieces.at(select_piece_id)->moved++;
}

void board::handle_mouse(int button, int state, int x, int y, int window_width, int window_height) {
        if (state != GLUT_DOWN) {
                return;
        }

        int file = x / (window_height / 8);
        int rank = 7 - (y / (window_height / 8));

        bool isEmpty = this->placement[rank][file] == "" ? true : false;
        bool isSelected = state_manager::instance().selected == "" ? false : true;
        bool isSameColor = false;

        string select_piece_id = state_manager::instance().selected;
        string target_piece_id = this->placement[rank][file];
        string select_piece_fen = "";
        string target_piece_fen = "";

        if (select_piece_id != "") {
                select_piece_fen = this->pieces.at(select_piece_id)->fen;
        }

        if (target_piece_id != "") {
                target_piece_fen = this->pieces.at(target_piece_id)->fen;
        }

        // IF selected AND target spot is not empty THEN set same color
        if (isSelected && !isEmpty) {
                isSameColor = this->pieces.at(this->placement[rank][file])->color == this->pieces.at(state_manager::instance().selected)->color ? true : false;
        }

        // IF not selected AND target spot is empty THEN ignore
        if (!isSelected && isEmpty) {
                return;
        }

        // IF not selected and target spot is not empty THEN select target PIECE
        if (!isSelected && !isEmpty) {
                handle_select_piece(target_piece_id);
                return;
        }

        // IF selected AND target spot is the same color as selected THEN select target piece
        if (isSelected && isSameColor) {
                handle_select_piece(target_piece_id);
                return;
        }

        // Passant
        if (isSelected && isEmpty && ((select_piece_fen == "P" && rank == 5) || select_piece_fen == "p" && rank == 2)) {
                if (select_piece_fen == "P") {
                        target_piece_id = this->placement[rank - 1][file];
                } else if (select_piece_fen == "p") {
                        target_piece_id = this->placement[rank + 1][file];
                }
                if (target_piece_id == "") {
                        return;
                }
                if (!this->pieces.at(target_piece_id)->two_square && this->pieces.at(target_piece_id)->moved == 1) {
                        return;
                }
                handle_special_take_piece(select_piece_id, target_piece_id);
        }

        // TODO
        // * Castle
        // * Check clear space
        // * Check if checked
        // * Check if any space is line of sight
        if (isSelected && !isEmpty && ((select_piece_fen == "K" && target_piece_fen == "R") || (select_piece_fen == "k" && target_piece_fen == "r"))) {
                return;
        }

        // IF selected AND not same color AND not empty THEN capture target piece
        if (isSelected && !isSameColor && !isEmpty) {
                handle_take_piece(select_piece_id, target_piece_id);
                return;
        }

        // IF selected and target spot is empty THEN move selected piece
        if (isSelected && isEmpty) {
                handle_move_piece(select_piece_id, rank, file);
                return;
        }
}

void board::insert_piece(unique_ptr<piece> p) {
        this->placement[p->rank][p->file] = p->id;
        string id = p->id;
        pieces.emplace(id, std::move(p));
}

#endif
