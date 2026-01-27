#ifndef SELECTION_STATE_H
#define SELECTION_STATE_H

#include <string>

class SelectionState {
      public:
        static SelectionState &instance();
        std::string selected;

      private:
        SelectionState();
        SelectionState(const SelectionState &) = delete;
        SelectionState operator=(const SelectionState &) = delete;
};

#endif
