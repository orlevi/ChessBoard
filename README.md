ChessBoard
==========

chess board that creates a PGN files of the games that are played 
on it.

this project is consisted of three parts:

1.	C++ prog for the chess game tracking. this code is 
	responsible to tracking the piece positions on the 
	board verifying the legality of the moves, and 
	producing the PGN file of the game.

2.	Python GUI. this part is essentialy an empty shell.
	it displays the board position graphically. it 
	should receive the moves from the MCU, check it's 
	legality with the previous part runned as a sub-
	process. and if the move is legal update the board 
	display. it can also receive moves from the mouse 
	for debug purposes.

3. 	C files for the MCU. this code is designed for the 
	MSP430 series and specifically for the MSP430G2553.
	this files shloud handle the reading of the sensors,
	"understanding" if and what move has been done, and 
	communicating with the python GUI.
	 
