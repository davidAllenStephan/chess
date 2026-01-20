#ifndef PIECE_HPP
#define PIECE_HPP

#include "texture_manager.hpp"
#include "uuid.hpp"
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum COLOR {
        WHITE,
        BLACK,
        EMPTY
};

class piece {
      public:
        string id;
        string fen;
        int rank;
        int file;
        int value;
        COLOR color;
	vector<pair<int,int>> move_mask;
        int texture_id;

        piece();
        virtual void update_color(COLOR color);
        virtual ~piece() = default;
};

#endif
