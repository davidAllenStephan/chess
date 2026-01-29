#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <unordered_map>

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

      public:
        Label label;
        Color color;
        std::string id;
	bool moved = false;
        Piece(Label, Color, std::string id);
        ~Piece();
        std::string toString();
        void printActionTable();
        void updateActionTable();
        bool actionTableContains(std::string id);
        Piece *get(std::string id);
};

static Piece *EMPTY_PIECE = new Piece(Label::EMPTY, Color::EMPTY, "");

#endif
