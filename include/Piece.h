#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <unordered_map>
#include <utility>

enum class Label {
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN,
        EMPTY
};

static std::unordered_map<Label, char> label_fen = {{Label::KING, 'k'}, {Label::QUEEN, 'q'}, {Label::ROOK, 'r'}, {Label::BISHOP, 'b'}, {Label::KNIGHT, 'n'}, {Label::PAWN, 'p'}};

enum class Color {
        WHITE,
        BLACK,
        EMPTY
};

static std::unordered_map<Label, std::string> color_string;

class Piece {
      private:
        std::unordered_map<std::string, Piece *> action_table;
        std::pair<int, int> pos;

      public:
        Label label;
        Color color;
        Piece(Label, Color, int, int);
        ~Piece();
        std::string toString();
        void printActionTable();
        void updateActionTable();
        void play(std::string position);
        bool find(std::string position);
        int getFile();
        int getRank();
        std::pair<int, int> getPos();
        void setFile(int file);
        void setRank(int rank);
        void setPos(std::pair<int, int>);
        Piece *get(std::string position);
};

#endif
