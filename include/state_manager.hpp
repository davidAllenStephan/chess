#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <string>
using namespace std;

class state_manager {
      public:
        static state_manager &instance();
        string selected;

      private:
        state_manager();
        state_manager(const state_manager &) = delete;
        state_manager operator=(const state_manager &) = delete;
};

#endif
