#include "Display.h"
#include "BoardState.h"
#include "Piece.h"
#include "PositionMap.h"
#include "TextureManager.h"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <climits>
#include <cstdlib>
#include <utility>
#include <vector>

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
                        drawSquare(i, j, cell_scale, cell_scale, window_width, window_height);
                        std::string id = PositionMap::get({i, j});
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
