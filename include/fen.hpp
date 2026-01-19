#ifndef FEN_HPP
#define FEN_HPP

#include "board.hpp"
#include <cstddef>

using namespace std;

board *read_fen(const char *path);

#endif
