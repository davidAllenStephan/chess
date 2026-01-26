#include "../include/board.hpp"
#include "../include/stb_image.h"
#include "fen.hpp"
#include "menu.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int WINDOW_ID;
int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;

board *b = new board();
int seconds = 0;

void closeWindow() {
        exit(0);
}

void display() {
        b->draw_board(WINDOW_WIDTH, WINDOW_HEIGHT);
        draw_menu(WINDOW_WIDTH, WINDOW_HEIGHT);
        display_timer(WINDOW_WIDTH, WINDOW_HEIGHT, seconds);
        glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
        b->handle_mouse(button, state, x, y, WINDOW_WIDTH, WINDOW_HEIGHT);
        glutPostRedisplay();
}

void timer(int time) {
        glutPostRedisplay();
        seconds++;
        glutTimerFunc(1000, timer, 0);
}

int main(int argc, char *argv[]) {
        cout << "display..." << endl;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        WINDOW_ID = glutCreateWindow("Hello, World!");
        glClearColor(0.1, 0.1, 0.1, 1.0);
        cout << "read_fen..." << endl;
        b = read_fen("../assets/fens/start.fen");
        glutDisplayFunc(display);
        glutTimerFunc(1000, timer, 0);
        glutMouseFunc(mouse);
        glutMainLoop();
        return 0;
}
