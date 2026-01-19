# Chess

## Build and run
```bash
mkdir build && cd build
cmake ..
make
./main [window_width] [window_height]
```

## Description
Currently an unfinished chess simulator.
Simply let two people play chess over a LAN connection.

## TODO
Create a simple interface.
Set a default window size and make it adjustable in a menu.
Constrict piece placement by rule.

BOARD --> PIECE ==> [PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING]

- Rule 1: a piece who shares the same color as another piece can not capture it.
- Rule 2: a piece must travel uninterrupted with the exeption of the horse.
- Rule 3: a piece who does not share the same color as another piece can capture it.

To be continued...
