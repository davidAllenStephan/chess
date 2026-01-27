#ifndef FEN_READER_H
#define FEN_READER_H

#include "PairHash.h"
#include "Piece.h"
#include <unordered_map>

class FenReader {
      public:
        static std::unordered_map<std::pair<int, int>, Piece *, PairHash> readFen(const char *path);
};

#endif // !FEN_READER_H
