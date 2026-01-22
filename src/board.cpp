#ifndef BOARD_CPP
#define BOARD_CPP

#include "../include/board.hpp"
#include "../include/uuid.hpp"
#include "state_manager.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>
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
        int target_piece_rank = this->pieces.at(target_piece_id)->rank;
        int target_piece_file = this->pieces.at(target_piece_id)->file;
        if (!this->pieces.at(select_piece_id)->valid_move(target_piece_rank, target_piece_file)) {
                return;
        }
        replace_piece(select_piece_id, target_piece_id);
        this->pieces.erase(target_piece_id);
        state_manager::instance().selected = "";
}

void board::handle_select_piece(string target_piece_id) {
        state_manager::instance().selected = target_piece_id;
}

void board::handle_move_piece(string select_piece_id, int rank, int file) {
        if (!this->pieces.at(select_piece_id)->valid_move(rank, file)) {
                return;
        }
        update_piece(select_piece_id, rank, file);
        state_manager::instance().selected = "";
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

        if (isSelected && !isEmpty) {
                isSameColor = this->pieces.at(this->placement[rank][file])->color == this->pieces.at(state_manager::instance().selected)->color ? true : false;
        }

        if (!isSelected && isEmpty) {
                return;
        }

        if (isSelected && !isSameColor && !isEmpty) {
                handle_take_piece(select_piece_id, target_piece_id);
                return;
        }

        if (isSelected && isEmpty) {
                handle_move_piece(select_piece_id, rank, file);
                return;
        }

        if (!isSelected) {
                handle_select_piece(target_piece_id);
                return;
        }
}

void board::insert_piece(unique_ptr<piece> p) {
        // std::cout << "Loading piece id=" << p->id << " at rank=" << p->rank << " file=" << p->file << std::endl;
        this->placement[p->rank][p->file] = p->id;
        string id = p->id;
        pieces.emplace(id, std::move(p));
}

#endif
