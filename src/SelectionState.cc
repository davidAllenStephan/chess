#include "SelectionState.h"

SelectionState::SelectionState() {
        selected = "";
}

SelectionState &SelectionState::instance() {
        static SelectionState instance;
        return instance;
}
