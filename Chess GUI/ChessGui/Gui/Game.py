'''
Created on 5 2014

@author: Or
'''

import Piece
import pygame
from pygame.locals import *

# size constants
WHITE = pygame.Color(255,255,255)
SQUARE_SIZE = 53
PIECE_SIZE = 49

# helper lists and dictionaries 
lines = [3 + (SQUARE_SIZE / 2) + SQUARE_SIZE * line for line in range(7, -1, -1)]
cols = [3 + (SQUARE_SIZE / 2) + SQUARE_SIZE * col for col in range(8)]
piece_colors = {'black' : 36, 'white' : 107}
piece_type = {'king' : 37, 'queen' : 121, 'rook' : 204, 'bishop' : 289, 'knight' : 373, 'pawn' : 457}


# load images
pieces_image = pygame.image.load('chess_set_symbols.png')
pieces_image = pygame.transform.scale(pieces_image, (482, 144))
board_image = pygame.image.load('board.png')


# create the pieces images (sprites) from the tiled ones
w_k = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
w_k.blit(pieces_image, (0, 0), (piece_type['king'] - PIECE_SIZE / 2, piece_colors['white'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = w_k.get_at((0,0))
w_k.set_colorkey(colorkey, RLEACCEL)
b_k = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
b_k.blit(pieces_image, (0, 0), (piece_type['king'] - PIECE_SIZE / 2, piece_colors['black'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = b_k.get_at((0,0))
b_k.set_colorkey(colorkey, RLEACCEL)
w_q = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
w_q.blit(pieces_image, (0, 0), (piece_type['queen'] - PIECE_SIZE / 2, piece_colors['white'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = w_q.get_at((0,0))
w_q.set_colorkey(colorkey, RLEACCEL)
b_q = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
b_q.blit(pieces_image, (0, 0), (piece_type['queen'] - PIECE_SIZE / 2, piece_colors['black'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = b_q.get_at((0,0))
b_q.set_colorkey(colorkey, RLEACCEL)
w_r = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
w_r.blit(pieces_image, (0, 0), (piece_type['rook'] - PIECE_SIZE / 2, piece_colors['white'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = w_r.get_at((0,0))
w_r.set_colorkey(colorkey, RLEACCEL)
b_r = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
b_r.blit(pieces_image, (0, 0), (piece_type['rook'] - PIECE_SIZE / 2, piece_colors['black'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = b_r.get_at((0,0))
b_r.set_colorkey(colorkey, RLEACCEL)
w_b = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
w_b.blit(pieces_image, (0, 0), (piece_type['bishop'] - PIECE_SIZE / 2, piece_colors['white'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = w_b.get_at((0,0))
w_b.set_colorkey(colorkey, RLEACCEL)
b_b = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
b_b.blit(pieces_image, (0, 0), (piece_type['bishop'] - PIECE_SIZE / 2, piece_colors['black'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = b_b.get_at((0,0))
b_b.set_colorkey(colorkey, RLEACCEL)
w_n = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
w_n.blit(pieces_image, (0, 0), (piece_type['knight'] - PIECE_SIZE / 2, piece_colors['white'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = w_n.get_at((0,0))
w_n.set_colorkey(colorkey, RLEACCEL)
b_n = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
b_n.blit(pieces_image, (0, 0), (piece_type['knight'] - PIECE_SIZE / 2, piece_colors['black'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = b_n.get_at((0,0))
b_n.set_colorkey(colorkey, RLEACCEL)
w_p = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
w_p.blit(pieces_image, (0, 0), (piece_type['pawn'] - PIECE_SIZE / 2, piece_colors['white'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = w_p.get_at((0,0))
w_p.set_colorkey(colorkey, RLEACCEL)
b_p = pygame.Surface((PIECE_SIZE, PIECE_SIZE))
b_p.blit(pieces_image, (0, 0), (piece_type['pawn'] - PIECE_SIZE / 2, piece_colors['black'] - PIECE_SIZE / 2, PIECE_SIZE, PIECE_SIZE))
colorkey = b_p.get_at((0,0))
b_p.set_colorkey(colorkey, RLEACCEL)


class Game():
    '''
    this class should handle all the gui game aspects
    '''
    

    def __init__(self):
        '''
        Constructor
        '''        
        # initialize the board
        self.pieces = []
        self.pieces.append(Piece.Piece([cols[0], lines[0]], w_r))
        self.pieces.append(Piece.Piece([cols[1], lines[0]], w_n))
        self.pieces.append(Piece.Piece([cols[2], lines[0]], w_b))
        self.pieces.append(Piece.Piece([cols[3], lines[0]], w_q))
        self.pieces.append(Piece.Piece([cols[4], lines[0]], w_k, True))
        self.pieces.append(Piece.Piece([cols[5], lines[0]], w_b))
        self.pieces.append(Piece.Piece([cols[6], lines[0]], w_n))
        self.pieces.append(Piece.Piece([cols[7], lines[0]], w_r))
        self.pieces.append(Piece.Piece([cols[0], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[1], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[2], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[3], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[4], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[5], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[6], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[7], lines[1]], w_p))
        self.pieces.append(Piece.Piece([cols[0], lines[7]], b_r))
        self.pieces.append(Piece.Piece([cols[1], lines[7]], b_n))
        self.pieces.append(Piece.Piece([cols[2], lines[7]], b_b))
        self.pieces.append(Piece.Piece([cols[3], lines[7]], b_q))
        self.pieces.append(Piece.Piece([cols[4], lines[7]], b_k, True))
        self.pieces.append(Piece.Piece([cols[5], lines[7]], b_b))
        self.pieces.append(Piece.Piece([cols[6], lines[7]], b_n))
        self.pieces.append(Piece.Piece([cols[7], lines[7]], b_r))
        self.pieces.append(Piece.Piece([cols[0], lines[6]], b_p))
        self.pieces.append(Piece.Piece([cols[1], lines[6]], b_p))
        self.pieces.append(Piece.Piece([cols[2], lines[6]], b_p))
        self.pieces.append(Piece.Piece([cols[3], lines[6]], b_p))
        self.pieces.append(Piece.Piece([cols[4], lines[6]], b_p))
        self.pieces.append(Piece.Piece([cols[5], lines[6]], b_p))
        self.pieces.append(Piece.Piece([cols[6], lines[6]], b_p))
        self.pieces.append(Piece.Piece([cols[7], lines[6]], b_p))
        
        
    def draw(self, canvas):
    	''' draw all the pieces on the board '''
        canvas.blit(board_image, (0, 0))
            
        for piece in self.pieces:
            piece.draw(canvas)
        
    def move_piece(self, origin, destination):
    	'''
    	changes the location of a piece on the board. this function should be called 
    	only after the move was checked and found legal.
    	'''
        for piece in self.pieces:
            current = [piece.pos[0] // SQUARE_SIZE , 7 - piece.pos[1] // SQUARE_SIZE]
            if current == destination:
                self.pieces.remove(piece)
                break
        for piece in self.pieces:
            current = [piece.pos[0] // SQUARE_SIZE , 7 - piece.pos[1] // SQUARE_SIZE]
            if current == origin:
                piece.pos = [cols[destination[0]], lines[destination[1]]]
                # handle castling moves
                if piece.is_king and (destination[0] - origin[0]) == 2:
                    move_piece(self.pieces, [7 ,destination[1]],[destination[0] - 1, destination[1]])
                elif piece.is_king and (destination[0] - origin[0]) == -2:
                    move_piece(self.pieces, [0 ,destination[1]],[destination[0] + 1, destination[1]])
                break
            