import pexpect
import serial
import pygame, sys
import Piece
import Game
from pygame.locals import *

pygame.init() # initialize pygame
fps_Clock = pygame.time.Clock() # set the FPS clock

# size constants
WIDTH = 426
HEIGHT = 426
SQUARE_SIZE = 53
ILLEGAL_SIZE = 256


# game handling constants
BYTES_TO_READ = 3
CORRECT_MOVE_LENGTH = 4
WAIT_TO_MOVE = 30
WHITE = pygame.Color(255,255,255)

# game handling public vars
wait_counter = 0
wait_count = False
illegal_move = False
first_up = None
second_up = None
down = None

# create the canvas
canvas = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Chess')
        
# load illegal move image
illegal_image = pygame.image.load('illegal.png')

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

def move_from_change(change):
    """
    takes the change on the board (piece up or piece down) and converts it to a move (four 
    charcters of numbers of origin and destination files and ranks).
    """
    global wait_count, wait_counter, first_up, second_up, down
    move = []
    if change[0] == 'U': # a piece was lifted from the board
        if change[1:2] == down and wait_count: # dragging a piece on the board 
            down = None
            wait_counter = 0
            wait_count = False 
        elif first_up == None:
            first_up = change[1:2]
        elif second_up == None:
            second_up = change[1:2]
            ###################################################################################### handle too many pieces up
    elif change[0] == 'D': # a piece was placed on the board
        ################################################################## handle piece down with no pieces up
        if second_up == None or second_up == change[1:2]:
            down = change[1:2]
            move.extend(first_up)
            move.extend(down)
            wait_count = True
    else:
        print "error in change recieved from MCU, first letter is not D or U"
        
    return move

def game():
    """
    this function handles the game. it waits to receive a move, checks if it is legal 
    with the pexpect subprocess, and makes the moves on the board.
    """
    global wait_count, wait_counter
    current_game = Game.Game()
    move_checker = pexpect.spawn('/home/pi/Desktop/ChessBoard/ChessBoard\ cpp\ files/ChessBoard/Chess')
    serial_MCU = serial.Serial('/dev/ttyAMA0') # UART communication with the MCU
    selected = False # is there a selected piece (in other words- first or second mouse click)
    origin_pos = [0, 0]
    done = False
    illegal_move = False
    
    while not done:
        for event in pygame.event.get():
            # exit if ESC pressed or 'x' clicked. 
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):     
                done = True
            ######################################################
            # receiving moves with the mouse for DEBUG purposes. #
            ######################################################
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
                            current_game.move_piece(origin_pos, position)
                            illegal_move = False
                        else:
                            print result
                            illegal_move = True
                    selected = False          
                else:
                    origin_pos = position
                    selected = True
        ################################
        # receiving moves from the MCU #
        ################################
        if serial_MCU.inWaiting() >= BYTES_TO_READ :
            change = serial_MCU.read(BYTES_TO_READ) # get the change from the MCU 
            move = move_from_change(change)
        if wait_count and wait_counter < WAIT_TO_MOVE: # we are waiting to certify a move
            wait_counter += 1
        if wait_count and wait_counter == WAIT_TO_MOVE: # counting to certify the move is over. try the move. 
            wait_count = False
            wait_counter = 0
            first_up = None
            second_up = None
            down = None
            result = check_move(move_checker, move[0], move[1], move[2], move[3])
            if result == 'Legal move':
                # MCU moves are in actual rank and file numbers (1-8 and not 0-7), hence the 
                # minus 1 in the elements
                origin = [int(move[0]) - 1, int(move[1]) - 1]
                destination = [int(move[2]) - 1, int(move[3]) - 1]
                current_game.move_piece(origin, destination)
                #serial_MCU.write('0') # assert the MCU that the move is correct and was done
                illegal_move = False
            else:
                print result
                #serial_MCU.write('1') # tell the MCU that the move can't be done
                illegal_move = True
        
        canvas.fill(WHITE)
        current_game.draw(canvas)
        if illegal_move:
            canvas.blit(illegal_image, (HEIGHT / 2 - ILLEGAL_SIZE / 2 , WIDTH / 2 - ILLEGAL_SIZE / 2))
        
        pygame.display.update()
        fps_Clock.tick(60)
        
    pygame.quit()
    
# start the game
game()
