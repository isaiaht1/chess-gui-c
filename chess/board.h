#pragma once
#include <string>
class board {
	public:
//cells of a board
		struct piece{
			char pieceColor;
			char pieceType;
			int enpassantable;
			bool castleable;
			piece(char tmpPieceType, char tmpPieceColor){
				pieceType=tmpPieceType;
				pieceColor=tmpPieceColor;
				enpassantable=-1;
				if (pieceType=='K' or pieceType=='R'){
					castleable=true;
				} else{
					castleable=false;
				}


			}
		};


		struct cell{
			char cellColor;
			piece myPiece;
			
			//used for constructing the array
			cell() : myPiece('E', 'R') {
				cellColor='E';
			}
//constructs the cells used in a board
			cell(char tmpPieceType, char tmpColor, char tmpPieceColor) : myPiece(tmpPieceType, tmpPieceColor) {
				cellColor=tmpColor;
			}
		};

    cell board_position[8][8]={
{board::cell('R','b','W'),board::cell('P','w','W'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','B'),board::cell('R','w','B')},
{board::cell('N','w','W'),board::cell('P','b','W'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','B'),board::cell('N','b','B')},
{board::cell('B','b','W'),board::cell('P','w','W'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','B'),board::cell('B','w','B')},
{board::cell('Q','w','W'),board::cell('P','b','W'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','B'),board::cell('Q','b','B')},
{board::cell('K','b','W'),board::cell('P','w','W'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','B'),board::cell('K','w','B')},
{board::cell('B','w','W'),board::cell('P','b','W'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','B'),board::cell('B','b','B')},
{board::cell('N','b','W'),board::cell('P','w','W'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','B'),board::cell('N','w','B')},
{board::cell('R','w','W'),board::cell('P','b','W'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','B'),board::cell('R','b','B')}
};

    /*cell board_position[8][8]={
{board::cell('R','w','B'),board::cell('P','b','B'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','W'),board::cell('R','b','W')},
{board::cell('N','b','B'),board::cell('P','w','B'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','W'),board::cell('N','w','W')},
{board::cell('B','w','B'),board::cell('P','b','B'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','W'),board::cell('B','b','W')},
{board::cell('Q','b','B'),board::cell('P','w','B'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','W'),board::cell('Q','w','W')},
{board::cell('K','w','B'),board::cell('P','b','B'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','W'),board::cell('K','b','W')},
{board::cell('B','b','B'),board::cell('P','w','B'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','W'),board::cell('B','w','W')},
{board::cell('N','w','B'),board::cell('P','b','B'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('P','w','W'),board::cell('N','b','W')},
{board::cell('R','b','B'),board::cell('P','w','B'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('P','b','W'),board::cell('R','w','W')}
};*/
/*cell board_position[8][8]={
{board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0')},
{board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0')},
{board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0')},
{board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0')},
{board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0')},
{board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0')},
{board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('Q','w','W'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0')},
{board::cell('K','b','B'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('\0','w','\0'),board::cell('\0','b','\0'),board::cell('K','w','W')}
};*/
//print code changed to screen.h
	void copyBoard(board::cell originalArray[][8]);

	std::string getBoardIdentification();
		 
};
