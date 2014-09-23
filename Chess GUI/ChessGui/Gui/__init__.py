import pexpect
import serial
import pygame, sys
import Piece
from pygame.locals import *

pygame.init() # initialize pygame
fps_Clock = pygame.time.Clock() # set the FPS clock

# size constants
WIDTH = 426
HEIGHT = 426
WHITE = pygame.Color(255,255,255)
SQUARE_SIZE = 53
PIECE_SIZE = 49

# game handling constants
BYTES_TO_READ = 4

# create the canvas
canvas = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Chess')

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

def initialize_board():
    """
    places all 32 pieces in their initial positions.
    """
    pieces = []
    pieces.append(Piece.Piece([cols[0], lines[0]], w_r))
    pieces.append(Piece.Piece([cols[1], lines[0]], w_n))
    pieces.append(Piece.Piece([cols[2], lines[0]], w_b))
    pieces.append(Piece.Piece([cols[3], lines[0]], w_q))
    pieces.append(Piece.Piece([cols[4], lines[0]], w_k, True))
    pieces.append(Piece.Piece([cols[5], lines[0]], w_b))
    pieces.append(Piece.Piece([cols[6], lines[0]], w_n))
    pieces.append(Piece.Piece([cols[7], lines[0]], w_r))
    pieces.append(Piece.Piece([cols[0], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[1], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[2], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[3], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[4], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[5], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[6], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[7], lines[1]], w_p))
    pieces.append(Piece.Piece([cols[0], lines[7]], b_r))
    pieces.append(Piece.Piece([cols[1], lines[7]], b_n))
    pieces.append(Piece.Piece([cols[2], lines[7]], b_b))
    pieces.append(Piece.Piece([cols[3], lines[7]], b_q))
    pieces.append(Piece.Piece([cols[4], lines[7]], b_k, True))
    pieces.append(Piece.Piece([cols[5], lines[7]], b_b))
    pieces.append(Piece.Piece([cols[6], lines[7]], b_n))
    pieces.append(Piece.Piece([cols[7], lines[7]], b_r))
    pieces.append(Piece.Piece([cols[0], lines[6]], b_p))
    pieces.append(Piece.Piece([cols[1], lines[6]], b_p))
    pieces.append(Piece.Piece([cols[2], lines[6]], b_p))
    pieces.append(Piece.Piece([cols[3], lines[6]], b_p))
    pieces.append(Piece.Piece([cols[4], lines[6]], b_p))
    pieces.append(Piece.Piece([cols[5], lines[6]], b_p))
    pieces.append(Piece.Piece([cols[6], lines[6]], b_p))
    pieces.append(Piece.Piece([cols[7], lines[6]], b_p))
    return pieces;

def draw(pieces):
    """
    draws the board and the pieces that are on it.
    """
    canvas.fill(WHITE)
    canvas.blit(board_image, (0, 0))
        
    for piece in pieces:
        piece.draw(canvas)
            
    pygame.display.update()
    fps_Clock.tick(60)

def move_piece(pieces, origin, destination):
    """
    changes the location of a piece on the board. this function should be called 
    only after the move was checked and found legal.
    """
    for piece in pieces:
        current = [piece.pos[0] // SQUARE_SIZE , 7 - piece.pos[1] // SQUARE_SIZE]
        if current == destination:
            pieces.remove(piece)
            break
    for piece in pieces:
        current = [piece.pos[0] // SQUARE_SIZE , 7 - piece.pos[1] // SQUARE_SIZE]
        if current == origin:
            piece.pos = [cols[destination[0]], lines[destination[1]]]
            # handle castling moves
            if piece.is_king and (destination[0] - origin[0]) == 2:
                move_piece(pieces, [7 ,destination[1]],[destination[0] - 1, destination[1]])
            elif piece.is_king and (destination[0] - origin[0]) == -2:
                move_piece(pieces, [0 ,destination[1]],[destination[0] + 1, destination[1]])
            break
        
def check_move(move_checker, origin_file, origin_rank, dest_file, dest_rank):
    """
    checks if the move is legal, and if so calls 'move_piece' to do it, if not it should print
    an appropriate message
    """
    move_checker.send(origin_file + '\n')
    move_checker.send(origin_rank + '\n')
    move_checker.send(dest_file + '\n')
    move_checker.send(dest_rank + '\n')
    index = move_checker.expect(['Legal', 'Illegal', pexpect.EOF])
    if index == 0:
        result = 'Legal move'
    elif index == 1:
        result = 'Illegal move!'
    elif index == 2:
        result = 'Game ended'
    return result    
    

def game():
    """
    this function handles the game. it waits to receive a move, checks if it is legal 
    with the pexpect subprocess, and makes the moves on the board.
    """
    pieces = initialize_board()
    move_checker = pexpect.spawn('/home/pi/Desktop/ChessBoard/ChessBoard\ cpp\ files/ChessBoard/Chess')
    serial_MCU = serial.Serial('/dev/ttyAMA0')
    selected = False # is there a selected piece (in other words- first or second mouse click)
    origin_pos = [0, 0]
    done = False
    
    while not done:
        for event in pygame.event.get():
            # exit if ESC pressed or 'x' clicked. 
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):     
                done = True
            # receiving moves with the mouse for DEBUG purposes.
            if event.type == MOUSEBUTTONDOWN: 
                position = [event.pos[0] // SQUARE_SIZE, 7 - event.pos[1] // SQUARE_SIZE]
                if selected:
                    if position != origin_pos: 
                        # lines and columns are numbered 1-8 in the subprocess and not 0-7,
                        # hence the '+1' in the command parameters.
                        result = check_move(move_checker, str(origin_pos[0] + 1), 
                                            str(origin_pos[1] + 1), str(position[0] + 1), 
                                            str(position[1] + 1))
                        if result == 'Legal move':
                            move_piece(pieces, origin_pos, position)
                        else:
                            print result
                    selected = False          
                else:
                    origin_pos = position
                    selected = True
        # receiving moves from the MCU
        if serial_MCU.inWaiting() >= BYTES_TO_READ :
            move = serial_MCU.read(BYTES_TO_READ)
            result = check_move(move_checker, move[0], move[1], move[2], move[3])
            if result == 'Legal move':
                # MCU moves are in actual rank and file numbers (1-8 and not 0-7), hence the 
                # minus 1 in the elements
                origin = [int(move[0]) - 1, int(move[1]) - 1]
                destination = [int(move[2]) - 1, int(move[3]) - 1]
                move_piece(pieces, origin, destination)
                #serial_MCU.write('0') # assert the MCU that the move is correct and was done
            else:
                print result
                #serial_MCU.write('1') # tell the MCU that the move can't be done
        draw(pieces)
        
    pygame.quit()
    
# start the game
game()
