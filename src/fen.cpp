#ifndef FEN_CPP
#define FEN_CPP

#include "fen.hpp"
#include "bishop.hpp"
#include "board.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <memory>
#include <utility>

using namespace std;

board *read_fen(const char *path) {
        board *b = new board();
        FILE *fp = fopen(path, "r");
        if (!fp) {
                printf("NOT OPENED!\n");
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

                COLOR color = isupper(c) ? WHITE : BLACK;

                piece *p;

                switch (tolower(c)) {
                case 'p':
                        p = new pawn(rank, file, color);
                        break;
                case 'n':
                        p = new knight(rank, file, color);
                        break;
                case 'b':
                        p = new bishop(rank, file, color);
                        break;
                case 'r':
                        p = new rook(rank, file, color);
                        break;
                case 'q':
                        p = new queen(rank, file, color);
                        break;
                case 'k':
                        p = new king(rank, file, color);
                        break;
                }

                if (p) {
                        b->insert_piece_map(p);
                        b->insert_placement(p);
                }

                file++;
        }
        b->print_board();
        return b;
}

#endif
