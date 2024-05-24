#include "board.h"
#include <string>
/*the chess board
default cell properties when 3 peramaters are specifieed
enpassantable=-1
castlable=true only if piece is rook or king else false
cell pieceType is first peramater
cell color is second parameter
cell pieceColor is the third paramater

default properties when no cell properties are specified(SHOULD NOT HAPPEN UNLESS THE CELL IN ITSELF IS AN ARRAY)
enpassantable=-2
castleable=false
cell pieceType is'E'
cell pieceColor is 'R'
cell color is'!'


cell board_position[8][8] initilized as a 2d array fo cells
*/




//most code here changed to screen.cpp, may eventually add duplicate board to check for checks
void board::copyBoard(board::cell originalArray[][8]){
	for(int x=0; x<8; x++){	
		for(int y=0; y<8; y++){
			board_position[x][y]=originalArray[x][y];
		}
	}
}

std::string board::getBoardIdentification(){
	std::string boardID="";
	for(int x=0; x<8; x++){
		for(int y=0; y<8; y++){
			if (board_position[x][y].myPiece.pieceType!='\0'){
				boardID+=board_position[x][y].myPiece.pieceType;
				boardID+=board_position[x][y].myPiece.pieceColor;
			} else {
				boardID+='0';
			}
		}
	}
	return boardID;
}
