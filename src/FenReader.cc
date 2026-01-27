#include "FenReader.h"
#include "PairHash.h"
#include "Piece.h"

static const std::unordered_map<char, Label> fen2label = {{'p', Label::PAWN}, {'n', Label::KNIGHT}, {'b', Label::BISHOP}, {'r', Label::ROOK}, {'q', Label::QUEEN}, {'k', Label::KING}};

std::unordered_map<std::pair<int, int>, Piece *, PairHash> FenReader::readFen(const char *path) {
        std::unordered_map<std::pair<int, int>, Piece *, PairHash> map;
        FILE *fp = fopen(path, "r");
        if (!fp) {
                return {};
        }
        int rank = 7;
        int file = 0;
        int i = 0;
        char c;
        while ((c = fgetc(fp)) != EOF && c != ' ') {
                if (c == '/') {
                        file = 0;
                        rank--;
                        continue;
                }
                if (isdigit(c)) {
                        file += c - '0';
                        continue;
                }
                Piece *p = new Piece(fen2label.at(tolower(c)), islower(c) ? Color::BLACK : Color::WHITE, file, rank);
                map.insert_or_assign((std::pair<int, int>){file, rank}, p);
                file++;
        }
        return map;
}
