/*#include "board.h"
#include "player.h"
#include "screen.h"
#include "notepad.h"

#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <iostream>

std::string getTime(){
	time_t time = std::time(nullptr);
	tm time2 = *std::localtime(&time);

	std::ostringstream oss;
	oss << std::put_time(&time2, "%d-%m-%Y_%H-%M-%S");
	return oss.str();
}



std::string chooseGame(){
	screen screen1;
	notepad pad;
	screen1.printGameList(pad.returnGameList());
	return screen1.askChooseGame(); 	
}

int main()
{
//initilize objects and variables
	board board1;
	screen screen1;
	std::string tmpTest="";
	notepad pad;
	player playersArr[2]={player("null",'w'), player("null",'b')}; //array of players
	std::string time=getTime();
	pad.initilizeNotePad(time);
	int turn=0;
	std::string startingCell;
	std::string endingCell;
	int validMove=false; 
	bool drawOffered=false;
	std::vector<std::string> boardIdentifiers;
	int positionRepeat=0;

//values of the players
	playersArr[0].playerName=screen1.askName("White");	
	playersArr[1].playerName=screen1.askName("Black");
//does turns
	screen1.clearScreen();
	std::string gameFile=chooseGame();
	bool replayGame=false;
	if (gameFile!="n"){
		replayGame=true;	
	}
	screen1.clearScreen();
	screen1.printGameInfo();
	while(true){
		validMove=false;
		while(validMove==false){
//print board with extra info
			screen1.printTurn(playersArr[turn%2].playerName, turn);
			screen1.printPiecesTaken(playersArr[1].piecesTaken, playersArr[1].countPiecePoints(), playersArr[1].playerName);
			screen1.printBoard(board1.board_position);
			screen1.printPiecesTaken(playersArr[0].piecesTaken, playersArr[0].countPiecePoints(), playersArr[0].playerName);


//gets input for move

			if (replayGame){
			
				if (turn>=pad.getTotalTurn(gameFile)){
					replayGame=false;
				}
				if (screen1.askStopReplay()){
					replayGame=false;
				}
			}
			if(not boardIdentifiers.empty()){
				positionRepeat=0;
				for(const std::string& i : boardIdentifiers){
					if (i==boardIdentifiers.back()){
						positionRepeat+=1;
					}
				}
			}

			if (positionRepeat>=3){
				screen1.printDraw("repition of positions");
				return 0;
			}
			if (not replayGame){
				startingCell=screen1.askStartPosition();
			} else {
				startingCell=pad.getStartMove(gameFile, turn);
			}
			
			if(startingCell=="DD"){
				if (drawOffered){
					screen1.printDraw("both sides agreeing to a draw");
					return 0;
				}
				drawOffered=true;
				screen1.clearScreen();
				if (drawOffered){
					screen1.printOfferedDraw();

				}
				continue;
			
			}
			if(startingCell=="RE"){
				screen1.printPlayerWon(playersArr[(turn+1)%2].playerName);
				return 0;
			}
			if (not replayGame){
				endingCell=screen1.askEndPosition();
			} else {
				endingCell=pad.getEndMove(gameFile, turn);
			}
//the player checks if the move was valid and executes the move
			validMove=playersArr[turn%2].setupMove(board1.board_position, startingCell, endingCell, turn);
//pawn promotion handling
			if (playersArr[turn%2].pawnPromotionThisTurn==true){
				playersArr[turn%2].promotePawn(endingCell, board1.board_position, screen1.askPawnPromotion());
				playersArr[turn%2].pawnPromotionThisTurn=false;
			}
			if (playersArr[0].move50RuleCheck>=50 and playersArr[1].move50RuleCheck<=50){
				if (screen1.askDraw50MoveRule()){
					screen1.printDraw("the 50 move rule");
					return 0;
				}

			}
			if(not playersArr[turn%2].checkEnoughMaterial){
				screen1.printDraw("not enough material to force a checkmate");
				return 0;
			}
			if(playersArr[(turn+1)%2].checkCheckmate(board1.board_position, turn)){
				screen1.printPlayerWon(playersArr[(turn)%2].playerName);
				return 0;
			}
			if(playersArr[(turn+1)%2].checkStalemate(board1.board_position, turn)){
				screen1.printDraw("being in stalemate");
				return 0;
			}
			

			screen1.clearScreen();
			if(playersArr[(turn+1)%2].checkCurrentlyInCheck(board1.board_position, turn)){
				screen1.printInCheck();
			}
//if move isnt valid, print the error message.
			if(not validMove) {
				screen1.printInvalidMove(startingCell, endingCell, playersArr[turn%2].errorReason);
			} else {
				pad.writeMove(time, turn, startingCell, endingCell);
				boardIdentifiers.push_back(board1.getBoardIdentification());
			}
		}
		turn+=1;
	}
	return 0;
}
*/
