#include <iostream>
#include "screen.h"
#include <QDebug>



//clears screen
void screen::clearScreen(){	
	system("clear");
}
//asks for name
std::string screen::askName(std::string playerColor){
	std::string name;
    qDebug()<< QString::fromStdString(playerColor) <<", what do you wish to be called?\n";
	std::cin>>name;
	return name;
	
}
//asks for startingCell
std::string screen::askStartPosition(){
	std::string startingCell;
    qDebug()<<"What is the cell id of the piece you want to move: ";
	std::cin>>startingCell;
	return startingCell;
}
//asks for endingCell
std::string screen::askEndPosition(){
	std::string endingCell;
    qDebug()<<"What is the cell id of the place you want your piece to move: ";
	std::cin>>endingCell;
	return endingCell;

}
std::string screen::askChooseGame(){
	std::string fileName;
    qDebug()<<"enter (n)o to quit or enter in a valid file name to repeat the moves of: ";
	std::cin>> fileName;
	return fileName;
}

bool screen::askStopReplay(){
	std::string stopReplay;
    qDebug()<<"do you want to stop the replay game here? (y)es or (n)o: ";
	std::cin>>stopReplay;
	if (stopReplay=="y"){
		return true;
	} else{
		return false;
	}
}

bool screen::askDraw50MoveRule(){
	std::string responseToDraw;
    qDebug()<<"50 moves has passes without a pawn moving or piece capture, would you like to draw?(opponent does not have to accept). (y)es or (n)o: ";
	std::cin>>responseToDraw;
	if (responseToDraw=="y"){
		return true;
	} else {
		return false;
	}


}

//input for pawn promotions
char screen::askPawnPromotion(){
	std::string piecePromotion="";
	bool attemptedMoreThenOnce=false;
	while(piecePromotion!="n" and piecePromotion!="b" and piecePromotion!="r" and piecePromotion!="q"){// executes over again if selection is invalid
		if (attemptedMoreThenOnce){
            qDebug()<<"\nInvalid promotion\n";
		}
        qDebug()<<"Your pawn has made it to the end of the board, what do you wish to promote it to? k(n)ignt, (b)ishop, (r)ook, or (q)ueen?: ";
		std::cin>>piecePromotion;
		attemptedMoreThenOnce=true;
	}
		return (char)toupper(piecePromotion[0]);
}

void screen::printOfferedDraw(){
    qDebug()<<"You were offered a draw, enter DD to accept\n";
}

void screen::printDraw(std::string reason){
    qDebug()<<"Game has ended in draw do to "<<QString::fromStdString(reason)<< "\n";
}

void screen::printPlayerWon(std::string playerColor){
    qDebug()<<QString::fromStdString(playerColor)<< " has won\n";
}

void screen::printGameList(std::string gameList){
    qDebug()<<QString::fromStdString(gameList);
}

void screen::printGameInfo(){
    qDebug()<<"enter DD to offer draw, or RE to resign\n";
}

//shows current turn and whos move
void screen::printTurn(std::string playerName, int turn){
    qDebug()<<"turn "<<turn<<"\n";
    qDebug()<< QString::fromStdString(playerName)<<"'s turn"<<"\n";
}

//prints all pieces taken in order of point value
void screen::printPiecesTaken(std::string piecesTaken, int piecePoints, std::string playerName){
	std::string tempPossiblePiecesTaken="PNBRQ";
    qDebug()<<"\n"<<"pieces taken by "<<QString::fromStdString(playerName)<<": ";
	for(int i=0; i<=tempPossiblePiecesTaken.size(); i++){
		for(int j=0; j<=piecesTaken.size(); j++){
			if (piecesTaken[j]==tempPossiblePiecesTaken[i]){
                qDebug()<<piecesTaken[j];
			}
		}
	}
    qDebug()<<" totalling to "<< piecePoints <<"\n"<<"\n";
}
//print invalid move with reason why it is invalid
void screen::printInvalidMove(std::string startingCell, std::string endingCell, std::string errorReason){
    qDebug()<<"\n invalid input \n tried to move "<< QString::fromStdString((startingCell)) << " to "<< QString::fromStdString(endingCell)<< "\n";
    qDebug()<<" "<< QString::fromStdString(errorReason)<< "\n";
}

void screen::printInCheck(){
    qDebug()<<"you are now in check"<<"\n";
}
//prints the entire board using the below functions
void screen::printBoard(board::cell board_position[][8]){
    qDebug()<<"   -----------------------------------------------\n";
	for (int y=0; y<8; y++){
        qDebug()<<"  |";
		colorPrint(board_position, y);
        qDebug()<<"\n";
        qDebug()<<8-y<<" |";
		piecePrint(board_position, y);
        qDebug()<<"\n"<< "  |";
		colorPrint(board_position, y);
        qDebug()<<"  ";
        qDebug()<<"\n   -----------------------------------------------\n";
		
	}
    qDebug()<<  "    a     b     c     d     e     f     g     h \n";
}
// implements color for below functions
std::string screen::colorBackgroundDecide(board::cell cell, bool background){
	std::string colorBuffer="\033[";
	if (not background){
		if (cell.myPiece.pieceColor=='W'){
			colorBuffer+="97";//bright white text
		} else{
			colorBuffer+="30"; //black text
		}
	} else {
		if(cell.cellColor=='w'){
			colorBuffer+="37"; //grey ish text
		} else{
			colorBuffer+="35"; //purple ish text
		}
	}
	if (colorBuffer!="\033["){
		colorBuffer+=';';//if text changes made, semicolon to addon for background
	}
	if(cell.cellColor=='w'){
		colorBuffer+="47";//grey ish highlighting
	} else{
		colorBuffer+="45";//purple ish highlighting
	}	
	return colorBuffer+'m';//m to let the program know to enact the color change instead of listening for more changes
	
}
//prints cell color as background
void screen::colorPrint(board::cell board_position[][8], int y){
	for(int x=0; x<8; x++){
        qDebug()<<QString::fromStdString(colorBackgroundDecide(board_position[x][y], true))<<" "<<QString::fromStdString(std::string(3, board_position[x][y].cellColor))<<" \033[0m" <<"|";
	}
}
//prints the piece in color
void screen::piecePrint(board::cell board_position[][8], int y){
	for(int x=0; x<8; x++){
        qDebug()<<QString::fromStdString(colorBackgroundDecide(board_position[x][y], false));
		if(board_position[x][y].myPiece.pieceType=='\0'){
            qDebug()<<" ";
		}
        qDebug()<<"  "<<board_position[x][y].myPiece.pieceType<<" ";
        qDebug()<<" \033[0m|";
	}
}

//prints the board colorless(old
void screen::colorlessPrintBoard(board::cell board_position[][8]){
	for (int y=0; y<8; y++){
        //qDebug().nospace().noquote()<<"  ";
        //colorlessColorPrint(board_position, y);
        //qDebug().nospace().noquote()<<"\n";
        qDebug().nospace().noquote()<<8-y<<" ";
        colorlessPiecePrint(board_position, y);
        qDebug().nospace().noquote()<<"\n"<< "  ";
        //colorlessColorPrint(board_position, y);
        //qDebug().nospace().noquote()<<"  ";
        qDebug().nospace().noquote()<<"\n------------------------------------------------\n";
		
	}
    qDebug().nospace().noquote()<<  "   a     b     c     d     e     f     g     h \n";
}

//prints the top and bottom row with the color of the cell(old)
void screen::colorlessColorPrint(board::cell board_position[][8], int y){
	for(int x=0; x<8; x++){
        qDebug().nospace().noquote()<<QString::fromStdString(std::string(3, board_position[x][y].cellColor))<<" | ";
	}
}

//prints the row with piece and cell color (old)
void screen::colorlessPiecePrint(board::cell board_position[][8], int y){
    //qDebug()<<" "<<board_position[0][0].myPiece.pieceType;
	for(int x=0; x<8; x++){
        //if (board_position[x][y].myPiece.pieceType!='\0'){
            qDebug()<<" "<<board_position[x][y].myPiece.pieceColor<<board_position[x][y].myPiece.pieceType<<" ";
            qDebug()<<" | ";
        //}
	}
}

