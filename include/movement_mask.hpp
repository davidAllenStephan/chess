#ifndef MOVEMENT_MASK_HPP
#define MOVEMENT_MASK_HPP

#include <utility>
#include <vector>

using namespace std;

class movement_mask {
      public:
        static const vector<pair<int, int>> knight;
        static const vector<pair<int, int>> bishop;
        static const vector<pair<int, int>> rook;
        static const vector<pair<int, int>> queen;
        static const vector<pair<int, int>> king;
};

#endif
