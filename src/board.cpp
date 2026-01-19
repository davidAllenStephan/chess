#ifndef BOARD_CPP
#define BOARD_CPP
#include "../include/board.hpp"
#include "../include/uuid.hpp"
#include "state_manager.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <cstdio>
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

void board::handle_mouse(int button, int state, int x, int y, int window_width, int window_height) {
        if (state == GLUT_DOWN) {
                int pos_x = x / (window_height / 8);
                int pos_y = 7 - (y / (window_height / 8));
                if (this->placement[pos_y][pos_x] != "") {
                        printf("%s, %i, %i\n", this->pieces.at(this->placement[pos_y][pos_x])->id.c_str(), pos_y, pos_x);
                        state_manager::instance().selected = this->pieces.at(this->placement[pos_y][pos_x]);
                } else if (this->placement[pos_y][pos_x] == "") {
                        piece *p = state_manager::instance().selected;
                        this->placement[p->rank][p->file] = "";
                        p->rank = pos_y;
                        p->file = pos_x;
                        state_manager::instance().selected = NULL;
                }
        }
}

void board::insert_piece_map(piece *p) {
        this->pieces.insert({p->id, p});
}

void board::insert_placement(piece *p) {
        this->placement[p->rank][p->file] = p->id;
}

#endif
