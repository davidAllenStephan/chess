#include "menu.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <array>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

/**
 * TODO:
 * clock is not working correctly.
 * when reaching 1 minute displays 01:60.
 * instead of 01:00.
 * might need to minus the multiplication of the min to seconds.
 * or derive a more comprehensive mathimatical operations to fix.
 */
void display_timer(int window_width, int window_height, int time) {
        float pos_x = 400;
        float pos_y = 400;
        pos_x /= window_width;
        pos_y /= window_height;
        int ten_min = (time / 60) / 10;
        int single_min = (time / 60) % 10;
        int ten_sec = time / 10;
        int single_sec = time % 10;
        string timer_text = to_string(ten_min) + to_string(single_min) + ":" + to_string(ten_sec) + to_string(single_sec);
        glColor3f(1, 1, 1);
        glRasterPos2f(pos_x, pos_y);
        for (char c : timer_text) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
        glFlush();
}

void draw_menu(int window_width, int window_height) {
        glColor3f(0, 0.9, 0.9);
        double width = 320;
        double height = (double)window_height * 2;
        double pos_x = 960;
        double pos_y = 0;
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
