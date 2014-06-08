CC=g++
CFLAGS=-c 

all: Chess

Chess: Chess.o Board.o Bishop.o King.o Knight.o NonKingPiece.o Pawn.o Piece.o Position.o Queen.o Rook.o
	$(CC) Chess.o Board.o Bishop.o King.o Knight.o NonKingPiece.o Pawn.o Piece.o Position.o Queen.o Rook.o -o Chess
	
Chess.o: Chess.cpp Board.hpp
	$(CC) $(CFLAGS) Chess.cpp
	
Bishop.o: Bishop.cpp Bishop.hpp NonKingPiece.hpp
	$(CC) $(CFLAGS) Bishop.cpp
	
King.o:	King.cpp King.hpp Piece.hpp
	$(CC) $(CFLAGS) King.cpp
	
Knight.o: Knight.cpp Knight.hpp NonKingPiece.hpp
	$(CC) $(CFLAGS) Knight.cpp
	
NonKingPiece.o: NonKingPiece.cpp NonKingPiece.hpp Piece.hpp
	$(CC) $(CFLAGS) NonKingPiece.cpp
	
Pawn.o: Pawn.cpp Pawn.hpp NonKingPiece.hpp
	$(CC) $(CFLAGS) Pawn.cpp
	
Piece.o: Piece.cpp Piece.hpp Position.hpp
	$(CC) $(CFLAGS) Piece.cpp
	
Position.o: Position.cpp Position.hpp
	$(CC) $(CFLAGS) Position.cpp
	
Queen.o:
	$(CC) $(CFLAGS) Queen.cpp
	
Rook.o:
	$(CC) $(CFLAGS) Rook.cpp