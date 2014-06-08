'''
Created on 3 2014
@author: Or
'''

PIECE_SIZE = 49

class Piece():
    '''
    this class is a piece on the board. 
    '''
    

    def __init__(self, pos, image):
        '''
        Constructor
        '''
        self.pos = pos
        self.image = image
        
    def draw(self, canvas):
        '''
        print the piece on the board.
        '''
        canvas.blit(self.image, (self.pos[0] - PIECE_SIZE / 2, self.pos[1] - PIECE_SIZE / 2))
        