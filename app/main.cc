#include "BoardState.h"
#include "Display.h"
#include "FenReader.h"
#include "Mouse.h"
#include "PairHash.h"
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <utility>

int WINDOW_ID;
int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;

void closeWindow() {
        exit(0);
}

void display() {
        Display::displayBoard(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
        Mouse::handleMouse(button, state, x, y, WINDOW_WIDTH, WINDOW_HEIGHT);
        glutPostRedisplay();
}

int main(int argc, char *argv[]) {
        std::unordered_map<std::pair<int, int>, Piece *, PairHash> fen = FenReader::readFen("../assets/fens/start.fen");
        std::cout << BoardState::toString() << std::endl;
        BoardState::load(fen);
        std::cout << BoardState::toString() << std::endl;
        BoardState::get("a2")->printActionTable();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        WINDOW_ID = glutCreateWindow("Hello, World!");
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMainLoop();
        return 0;
}
