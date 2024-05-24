#pragma once
#include "board.h"
#include <string>
class screen{
public:
		void clearScreen(); // clears the screen

		std::string askName(std::string playerColor); // gets the player's name
		std::string askStartPosition(); //gets startingCell
		std::string askEndPosition(); //gets endingCell
		std::string askChooseGame();
		bool askStopReplay();
		char askPawnPromotion(); //gets input for what piece the player wants their pawn to be
		bool askDraw50MoveRule();

		void printOfferedDraw();
		void printDraw(std::string);
		void printPlayerWon(std::string playerColor);
			
		void printGameList(std::string gameList);
		void printGameInfo();
		void printTurn(std::string playerName, int turn); // shows turn and whos move it is
		void printPiecesTaken(std::string piecesTaken, int piecePoints, std::string playerName); // print pieces in order of point value that have been taken by whom
		void printInvalidMove(std::string startingCell, std::string endingCell, std::string errorReason); //prints invalid move and reason why its invalid
		void printInCheck(); 
		void printBoard(board::cell board_position[][8]);// prints the chess board of cells

		void colorlessPrintBoard(board::cell board_position[][8]); //prints the chess board of cells (colorless)
private:

			
			std::string colorBackgroundDecide(board::cell cell, bool background); // determines what color the outputted parts of a cell should be for below functions
			void colorPrint(board::cell board_position[][8], int y); //prints the top and bottom of a cell with its cellColor
			void piecePrint(board::cell board_position[][8], int y); //prints the middle of a cell with its piece and potentially its cellColor	

			void colorlessColorPrint(board::cell board_position[][8], int y); //prints the top and bottom of a cell with its cellColor (colorless)
public: void colorlessPiecePrint(board::cell board_position[][8], int y); //prints the middle of a cell with its piece and potentially its cellColor (colorless)
};
