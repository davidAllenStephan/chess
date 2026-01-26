#ifndef PIECE_HPP
#define PIECE_HPP

#include "texture_manager.hpp"
#include "uuid.hpp"
#include <cstddef>
#include <string>
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
        int moved;
        bool two_square;
        COLOR color;
        vector<pair<int, int>> movement_mask;
        vector<pair<int, int>> capture_mask;
        vector<pair<int, int>> special_movement_mask;
        vector<pair<int, int>> special_capture_mask;
        int texture_id;

        virtual pair<int, int> valid_move(int rank, int file);
        virtual pair<int, int> valid_special_move(int rank, int file);
        virtual pair<int, int> valid_capture(int rank, int file);
        virtual pair<int, int> valid_special_capture(int rank, int file);

        piece();
        virtual void update_color(COLOR color);
        virtual ~piece() = default;
};

#endif
