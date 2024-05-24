#pragma once
#include <string>
#include "board.h"
class player{
	public:
		
		std::string playerName; // the players name
		char playerColor; //the players color
		std::string errorReason; //gives feedback on the users errors so it can be corrected
		std::string piecesTaken; //list of piecesTaken (1 char per piece)
		bool castledThisTurn; // used to activate the specific move function moveEnpassant()
		bool enpassantedThisTurn; //used to activate the specific move function moveCastle()
		bool pawnPromotionThisTurn; //checks if a pawn promotion happened on the turn so it can properly promote with promotePawn()
		int move50RuleCheck;
		bool checkEnoughMaterial;
//constructs the player object
		player(std::string tmpPlayerName, char tmpPlayerColor);
	//takes in board, current position, and desired position. asks checkLegalMove if the move is legal, if so it moves.
		int countPiecePoints(); //used to count how many points the player has taken from the pieces of the oponents

		void promotePawn(std::string cell, board::cell board_position[][8], char newPiece); //promotes piece, should only be activated if pawn is already checked to be promotable

		bool setupMove(board::cell board_position[][8], std::string startingCell, std::string endingCell, int gameTurn);// executes the players move if it is legal using the below functions
		void move(board::cell board_position[][8], int startingCellX, int startingCellY, int endingCellX, int endingCellY, bool simulatedMove);
private:
		void movePiece(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], bool simulatedMove); //moves pieces that follow standard-ish rules(aka not below ones)
		void moveEnpassant(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], bool simulatedMove);//moves pawns that enpassant and takes enppasanted pawns
		void moveCastle(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]); //castles king and rook

		bool checkInputError(std::string startingCell, std::string endingCell); //checks for user error when choosing spaces before any detrimental errors could be caused

		//checks if move is legal using below functions
		bool checkLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, char pieceColor, char pieceType, char endPieceColor, bool checkDrawMove);
		bool checkPieceLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove);
//checks for illegal moves that universally apply to every piece using the 3 below tabbed functions
			bool initialChecks(char pieceColor, int startingCellX, int startingCellY, int endingCellX, int endingCellY, char endPieceColor); //checks for universal illigalities
				bool rangeChecks(int startingCellX, int startingCellY, int endingCellX, int endingCellY); //checks to make sure the cells you are trying to access are on the board
				bool startColorCheck(char pieceColor);  //checks to make sure you are moving only your own piece
				bool endColorCheck(char endPieceColor); //checks to make sure you arent taking your own piece
									
//if checkLegalMove states that the piece being moved is a pawn, checkPawnLegalMove will decide if the pawn move is legal using the below 5 tabbed functions. 
				bool checkPawnLegalMove (int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove);
					int checkPawnIncrement(board::cell board_position[][8], int startingCellX, int startingCellY);
					//checks to see if a pawn can move one space forward legally
					bool checkPawnMove1(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, board::cell board_position[][8]);
					//checks to see if a pawn can move 2 spaces forward legally
					bool checkPawnMove2(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, int gameTurn, board::cell board_position[][8]);
					//checks to see if a pawn can take legally
					bool checkPawnTake(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, board::cell board_position[][8]);
					//checks to see if a pawn can enpassant legally (does not actually enpassant)
					bool checkPawnEnpassant(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, int gameTurn, board::cell board_position[][8]);

				bool checkBishopLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]); //checks to see if a bishop can move legally

				bool checkRookLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]);  //checks to see if a rook can move legally
	
				bool checkQueenLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]); //checks to see if a knight can move legally

				bool checkKnightLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]);// checks to see if a queen can move legally
				//uses 2 below functions to check if the king can move legally
				bool checkKingLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove); 
					bool checkKingRingMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]); //checks to see if a king can move normally
					bool checkKingCastle(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove); //checks if the king can castle
																	       
			bool checkMoveCheck(board::cell board_position[][8], int startingCellX, int startingCellY, int endingCellX, int endingCellY, int gameTurn);


					bool checkPieceInWay(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]);//checks if any pieces in between start and end coords
					int checkIncrement(int startingCellCoordinate,int endingCellCoordinate);// checks to see what direction the piece is moving in.
														
			int alphabetToInt(char letter); //used to convert the alphabet to its equivalent int value (a=0, b=1, etc)


			
	bool checkEnoughMaterialDraw(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]);
	public:
		bool checkStalemate(board::cell board_position[][8], int gameTurn);
		bool checkCheckmate(board::cell board_position[][8], int gameTurn);
		bool checkCurrentlyInCheck(board::cell board_position[][8], int gameTurn);
};

