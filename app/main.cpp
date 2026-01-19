#include "../include/board.hpp"
#include "../include/stb_image.h"
#include "fen.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int WINDOW_ID;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;

board *b = new board();

void closeWindow() {
        exit(0);
}

void display() {
        b->draw_board(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
        b->handle_mouse(button, state, x, y, WINDOW_WIDTH, WINDOW_HEIGHT);
        glutPostRedisplay();
}

int main(int argc, char *argv[]) {
        cout << "display..." << endl;
        WINDOW_WIDTH = atoi(argv[1]);
        WINDOW_HEIGHT = atoi(argv[2]);
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        WINDOW_ID = glutCreateWindow("Hello, World!");
        glClearColor(0.1, 0.1, 0.1, 1.0);

        cout << "read_fen..." << endl;
        b = read_fen("../assets/fens/start.fen");

        glutDisplayFunc(display);

        glutMouseFunc(mouse);

        glutMainLoop();
        return 0;
}
