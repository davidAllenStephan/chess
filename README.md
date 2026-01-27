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
Testing something

Each piece should store its own valid movement mask.
After each move every piece should update their movement mask.
This would be at least 32 pieces with at most ~20 valid moves.
So this would be 32 * 20 = 2080 iterations.
Maybe only update the pieces movement mask when its selected.
This would split the process into chunks rather than one large sweep.

Another important improvement would be for each piece to store its own movement code.
For many pieces a mask is enough but for king and pawn they have special cases to account for.
King has castle and pawn has double move and passant.
When a piece is selected we iterate through its movement mask and eliminate moves that aren't possible.

The board class is over crowded it is the driving force for too many operaitons.
This is because pieces do not extend the board rather they are represented by ids.
The pieces do not know their position relative to other pieces.
So we need the board class to connect the pieces to each other.
The pieces to be able to access each other without the board.
Currently the board acts as an api between the other pieces.

Some sort of data structure to connect all the pieces may be neccessary.
Then disconnect the board and the pieces.
The pieces should have relationships with each other.
The board should be purely there to draw the board and other features.

Maybe the pieces have access to the pieces within there mask.
A new piece called "EMPTY" could be used to fill the empty areas.
Then it would be simply swapping the positions of the pieces for movement and captures.

Each piece holds a map that uses a mask as the key and a piece as the value.
On every movement or selection this map would be updated.









