#ifndef STATE_MANAGER_CC
#define STATE_MANAGER_CC

#include "../include/state_manager.hpp"

state_manager::state_manager() : selected("") {};

state_manager &state_manager::instance() {
        static state_manager instance;
        return instance;
}

#endif
