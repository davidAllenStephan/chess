#include "Mouse.h"
#include "BoardState.h"
#include "GLUT/glut.h"
#include "Piece.h"
#include "PositionMap.h"
#include "SelectionState.h"
#include <utility>

void Mouse::handleMouse(int button, int state, int x, int y, int window_width, int window_height) {
        if (state != GLUT_DOWN) {
                return;
        }
        std::pair<int, int> position = {x / (window_height / 8), 7 - (y / (window_height / 8))};
        if (SelectionState::instance().selected == "") {
                SelectionState::instance().selected = PositionMap::get(position);
        } else {
                BoardState::replace(PositionMap::get(position), SelectionState::instance().selected);
                SelectionState::instance().selected = "";
        }
}
