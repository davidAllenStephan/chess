#include "Display.h"
#include "BoardState.h"
#include "Piece.h"
#include "PositionMap.h"
#include "SelectionState.h"
#include "TextureManager.h"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <climits>
#include <cstdlib>
#include <utility>
#include <vector>

float primary_board_color[3] = {53.0 / 255.0, 129.0 / 255.0, 216.0 / 255.0};
float secondary_board_color[3] = {99.0 / 255.0, 202.0 / 255.0, 216.0 / 255.0};
float selected_color[3] = {216.0 / 255.0, 46.0 / 255.0, 63.0 / 255.0};
float action_color[3] = {40.0 / 255.0, 204.0 / 255.0, 45.0 / 255.0};

void drawSquare(double pos_x, double pos_y, double width, double height, double window_width, double window_height) {
        pos_x = pos_x * width;
        pos_y = pos_y * width;
        pos_x -= window_width;
        pos_y -= window_height;
        std::vector<std::array<double, 2>> vertices = {
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

void drawTexture(int texture_id, double pos_x, double pos_y, int window_width, int window_height) {
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
        std::vector<std::array<float, 2>> texture_vertices = {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f}};
        std::vector<std::array<double, 2>> vertices = {
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

void Display::displayBoard(int window_width, int window_height) {
        double board_width = window_width * 1.5;
        double cell_scale = board_width / 8;
        std::string selected = SelectionState::instance().selected;
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        std::string id = PositionMap::get({i, j});
                        if (id == selected) {
                                glColor3f(selected_color[0], selected_color[1], selected_color[2]);
                        } else if (selected != "" && BoardState::get(selected)->actionTableContains(id)) {
                                glColor3f(action_color[0], action_color[1], action_color[2]);
                        } else if (i % 2 == 0) {
                                if (j % 2 == 0) {
                                        glColor3f(primary_board_color[0], primary_board_color[1], primary_board_color[2]);
                                } else {
                                        glColor3f(secondary_board_color[0], secondary_board_color[1], secondary_board_color[2]);
                                }
                        } else {
                                if (j % 2 == 0) {
                                        glColor3f(secondary_board_color[0], secondary_board_color[1], secondary_board_color[2]);
                                } else {
                                        glColor3f(primary_board_color[0], primary_board_color[1], primary_board_color[2]);
                                }
                        }
                        drawSquare(i, j, cell_scale, cell_scale, window_width, window_height);
                        Label l = BoardState::get(id)->label;
                        Color c = BoardState::get(id)->color;
                        if (l == Label::EMPTY) {
                                continue;
                        }
                        GLuint texture_id = TextureManager::get(l, c);
                        drawTexture(texture_id, i, j, window_width, window_height);
                }
        }
        glFlush();
}
