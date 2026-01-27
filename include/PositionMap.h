#ifndef POSITION_MAP_H
#define POSITION_MAP_H

#include "PairHash.h"
#include <string>
#include <unordered_map>
#include <utility>

class PositionMap {
      private:
        static const std::unordered_map<std::pair<int, int>, std::string, PairHash> position_map;

      public:
        static std::string get(std::pair<int, int>);
};

#endif
