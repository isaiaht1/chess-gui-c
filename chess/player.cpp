#include "player.h"
#include "board.h"
#include <QDebug>
#include <iostream>
//purpose: to assign piece type during construction
player::player(std::string tmpPlayerName, char tmpPlayerColor){
	playerName=tmpPlayerName; //Name of the player
	playerColor=tmpPlayerColor; //color of the player

	errorReason=""; //gives feedback on the users errors so it can be corrected
	piecesTaken=""; //list of piecesTaken (1 char per piece)
	castledThisTurn=false; // used to activate the specific move function moveEnpassant()
	enpassantedThisTurn=false; //used to activate the specific move function moveCastle()
	pawnPromotionThisTurn=false; //checks if a pawn promotion happened on the turn so it can properly promote with promotePawn()
    move50RuleCheck=0;
	checkEnoughMaterial=true;
}


 //used to count how many points the player has taken from the pieces of the oponents
int player::countPiecePoints(){
	int pointCount=0;
	for (int i=0; i<piecesTaken.size(); i++){
		switch(piecesTaken[i]){
			case 'P':
				pointCount+=1;
				break;
			case 'B':
				pointCount+=3;
				break;
			case 'N':
				pointCount+=3;
				break;
			case 'R':
				pointCount+=5;
				break;
			case 'Q':
				pointCount+=9;
				break;
		}
	}
	return pointCount;
}
//checks for user error when choosing spaces before any detrimental errors could be caused
bool player::checkInputError(std::string startingCell, std::string endingCell){
	char numbers[]="1234567890";
	bool startingCellYCheck=false;
	bool endingCellYCheck=false;
	//makes sure user response is only 2 char long per cell as the identifier for cells is only 2 char long
	if (startingCell.size()!=2 or endingCell.size()!=2){
		errorReason="input for piece more then 2 characters.";
		return false;	
	}
	//makes sure x coordinates are given in letters
	if (alphabetToInt(startingCell[0])==-1 or alphabetToInt(endingCell[0])==-1){
		errorReason="first character of piece is not a letter";
		return false;
	}
	//makes sure the y coordinates are given in digits
	for(int i=0; i<=10; i++){
		if ((char)tolower(startingCell[1])==numbers[i]){
			startingCellYCheck=true;
		}
		if ((char)tolower(endingCell[1])==numbers[i]){	
			endingCellYCheck=true;
		}
	}
	if (not(startingCellYCheck and endingCellYCheck)){
		errorReason="second character of piece not a digit";
		return false;
	}
	return true;
	
}
//used to convert the alphabet to its equivalent int value (a=0, b=1, etc)
int player::alphabetToInt(char letter){
	char alphabet[]="abcdefghijklmnopqrstuvwxyz";
	for(int i=0; i<=26; i++){
		if ((char)tolower(letter)==alphabet[i]){
			return i;
		}
	}
	return -1;
}
//promotes piece, should only be activated if pawn is already checked to be promotable
void player::promotePawn(std::string cell, board::cell board_position[][8], char newPiece){
	int cellX=alphabetToInt(cell[0]);
	int cellY = 8-(cell[1]-'0');
	std::string piece="";
    board_position[cellX][cellY].myPiece.pieceColor=toupper(playerColor);
    board_position[cellX][cellY].myPiece.pieceType=newPiece;
    return;
}

//attempt to move
//does the players move if it is legal through below functions
bool player::setupMove(board::cell board_position[][8], std::string startingCell, std::string endingCell, int gameTurn){
    qDebug()<<"test2"<< playerColor;
	if (not checkInputError(startingCell, endingCell)){
		return false;
	}
    int startingCellY = startingCell[1]-'0';
	int startingCellX=alphabetToInt(startingCell[0]);
    int endingCellY = endingCell[1]-'0';
	int endingCellX=alphabetToInt(endingCell[0]);
	char pieceColor;
	char endPieceColor;
	char pieceType;
	pieceType=board_position[startingCellX][startingCellY].myPiece.pieceType;
	pieceColor=(char)tolower(board_position[startingCellX][startingCellY].myPiece.pieceColor);
	endPieceColor=(char)tolower(board_position[endingCellX][endingCellY].myPiece.pieceColor);
	//move was succesful
	if (checkLegalMove(startingCellX, startingCellY, endingCellX, endingCellY, board_position, gameTurn, pieceColor, pieceType, endPieceColor, false)){
        //qDebug()<<"3"<<board_position[5][1].myPiece.pieceType;
		move(board_position, startingCellX, startingCellY, endingCellX, endingCellY, false);
        //qDebug()<<"4"<<board_position[5][1].myPiece.pieceType;

		return true;
	}
		//move was unsucessful
		return false;
}

void player::move(board::cell board_position[][8], int startingCellX, int startingCellY, int endingCellX, int endingCellY, bool simulatedMove){
	if(enpassantedThisTurn==false and castledThisTurn==false){
        //qDebug()<<"51";
		movePiece(startingCellX, startingCellY, endingCellX, endingCellY, board_position, simulatedMove);	
	} else if(enpassantedThisTurn==true){
        //qDebug()<<"52";
		moveEnpassant(startingCellX, startingCellY, endingCellX, endingCellY, board_position, simulatedMove);
	} else if(castledThisTurn==true){
        //qDebug()<<"53";
		moveCastle(startingCellX, startingCellY, endingCellX, endingCellY, board_position);
	} 
	if (not simulatedMove){
		move50RuleCheck+=1;
	}
}


//perforems standard moves that do not have weird rulesets that effect multiple pieces(aka the ones below)
void player::movePiece(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], bool simulatedMove){
	if (not simulatedMove and board_position[endingCellX][endingCellY].myPiece.pieceType!='\0'){
		piecesTaken+=board_position[endingCellX][endingCellY].myPiece.pieceType;
        move50RuleCheck=0;
	}

    if(not simulatedMove and board_position[startingCellX][startingCellY].myPiece.pieceType=='P'){
		move50RuleCheck=0;
	}
	char tmpColorSwap;
	char tmpPieceSwap;
	tmpColorSwap=board_position[startingCellX][startingCellY].myPiece.pieceColor;
	board_position[startingCellX][startingCellY].myPiece.pieceColor='\0';
	board_position[endingCellX][endingCellY].myPiece.pieceColor=tmpColorSwap;

	
	tmpPieceSwap=board_position[startingCellX][startingCellY].myPiece.pieceType;
	board_position[startingCellX][startingCellY].myPiece.pieceType='\0';
	board_position[endingCellX][endingCellY].myPiece.pieceType=tmpPieceSwap;

	board_position[startingCellX][startingCellY].myPiece.castleable=false;
	board_position[endingCellX][endingCellY].myPiece.castleable=false;


}
// moves a pawn thats enpassanting and takes the enpassanted pawn
void player::moveEnpassant(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], bool simulatedMove){
	if(not simulatedMove){
		piecesTaken+=board_position[endingCellX][startingCellY].myPiece.pieceType;
		move50RuleCheck=0;
	
	}
	board_position[endingCellX][endingCellY].myPiece.pieceType=board_position[startingCellX][startingCellY].myPiece.pieceType;
	board_position[endingCellX][endingCellY].myPiece.pieceColor=board_position[startingCellX][startingCellY].myPiece.pieceColor;

	board_position[startingCellX][startingCellY].myPiece.pieceColor='\0';
	board_position[startingCellX][startingCellY].myPiece.pieceType='\0';
	board_position[endingCellX][startingCellY].myPiece.pieceType='\0';
}
//castles your king and rook
void player::moveCastle(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){
	int castledRookEndX;//where rook will end
	int castledRookStartX;// where rook starts
	if (endingCellX-startingCellX==-2){
		castledRookEndX=3;
		castledRookStartX=0;

	} else{
		castledRookEndX=5;
		castledRookStartX=7;
	}

	board_position[endingCellX][endingCellY].myPiece.pieceType=board_position[startingCellX][startingCellY].myPiece.pieceType;
	board_position[startingCellX][startingCellY].myPiece.pieceType='\0';
	
	board_position[castledRookEndX][endingCellY].myPiece.pieceType=board_position[castledRookStartX][endingCellY].myPiece.pieceType;
	board_position[castledRookStartX][endingCellY].myPiece.pieceType='\0';
	
	board_position[castledRookEndX][endingCellY].myPiece.pieceColor=board_position[castledRookStartX][endingCellY].myPiece.pieceColor;
	board_position[castledRookStartX][endingCellY].myPiece.pieceColor='\0';

	board_position[endingCellX][endingCellY].myPiece.pieceColor=board_position[startingCellX][startingCellY].myPiece.pieceColor;
	board_position[startingCellX][startingCellY].myPiece.pieceColor='\0';


	board_position[castledRookStartX][endingCellY].myPiece.castleable=false;
	board_position[startingCellX][startingCellY].myPiece.castleable=false;
}




//returns true if the move the player is trying to make is legal, and false if not
bool player::checkLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, char pieceColor, char pieceType, char endPieceColor, bool checkDrawMove){
	if (not checkDrawMove){
		enpassantedThisTurn=false;
		castledThisTurn=false;
		pawnPromotionThisTurn=false;
	}
	if (not(initialChecks (pieceColor, startingCellX, startingCellY, endingCellX, endingCellY, endPieceColor))){
		return false;	
	}

//checks what piece is being moved and checks if the move is legal using the appropriate logic
	if (not(checkPieceLegalMove(startingCellX, startingCellY, endingCellX, endingCellY, board_position, gameTurn, false))){
		return false; 
	}
	if (not castledThisTurn){
		if(not(checkMoveCheck(board_position, startingCellX, startingCellY, endingCellX, endingCellY, gameTurn))){
			return false;
		}
	}

	checkEnoughMaterialDraw(startingCellX, startingCellY, endingCellX, endingCellY, board_position);
	if (not checkDrawMove){
		checkStalemate(board_position, gameTurn);
	}
	return true;
}


bool player::checkPieceLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove){
	switch (board_position[startingCellX][startingCellY].myPiece.pieceType){
		case 'B' :
			return checkBishopLegalMove(startingCellX, startingCellY, endingCellX, endingCellY, board_position);
		case 'R' :
			return checkRookLegalMove  (startingCellX, startingCellY, endingCellX, endingCellY, board_position);
		case 'Q' :
			return checkQueenLegalMove (startingCellX, startingCellY, endingCellX, endingCellY, board_position);
        case 'K' :
            //qDebug()<<"";
			return checkKingLegalMove  (startingCellX, startingCellY, endingCellX, endingCellY, board_position, gameTurn, simulatedMove);
		case 'N' :
			return checkKnightLegalMove(startingCellX, startingCellY, endingCellX, endingCellY, board_position);
		case 'P':
			return checkPawnLegalMove  (startingCellX, startingCellY, endingCellX, endingCellY, board_position, gameTurn, simulatedMove);


	}
	return false;

}
//checks if the players move violates any rule that is universally applicable to every piece (cant move other players piece and cant take your own pieces). returns true if the move is illegal for these reasons, false if not
bool player::initialChecks(char pieceColor, int startingCellX, int startingCellY, int endingCellX, int endingCellY, char endPieceColor){
	if (rangeChecks(startingCellX, startingCellY, endingCellX, endingCellY) and
	    startColorCheck(pieceColor) and 
	    endColorCheck(endPieceColor)){
		return true;
	}
	return false; 
}
//checks if move inputs are in range
bool player::rangeChecks(int startingCellX, int startingCellY, int endingCellX, int endingCellY){
	if (not ((startingCellX>7 or startingCellX<0) or (startingCellY>7 or startingCellY<0) or (endingCellX>7 or endingCellX<0) or (endingCellY>7 or endingCellY<0))){
		return true;
	}
	errorReason="cell(s) not in range";
	return false;
}
//checks to make sure the colors turn matches with what piece they are moving
bool player::startColorCheck(char pieceColor){
	if (pieceColor==playerColor){
		return true;
	}
	errorReason="color of piece does not match your color";
	return false;
}
//checks to make sure the player isnt taking their own piece
bool player::endColorCheck(char endPieceColor){
	if (endPieceColor!=playerColor){
		return true;
	}
	errorReason="You cannot take your own piece";
	return false;
}

//checks to see if a pawn can move forward legally with the 5 below functions
bool player::checkPawnLegalMove (int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove){
	int colorIncrement=checkPawnIncrement(board_position, startingCellX, startingCellY); //increment is used to tell if the pawn can go up in the y direction or down in the y direction based off of its color
	if     (checkPawnMove1     (startingCellX, startingCellY, endingCellX, endingCellY, colorIncrement, board_position)           or 
		checkPawnMove2     (startingCellX, startingCellY, endingCellX, endingCellY, colorIncrement, gameTurn, board_position) or 
		checkPawnTake      (startingCellX, startingCellY, endingCellX, endingCellY, colorIncrement, board_position)           or
		checkPawnEnpassant (startingCellX, startingCellY, endingCellX, endingCellY, colorIncrement, gameTurn, board_position)){
		if (endingCellY==0 or endingCellY==7){ 
			if (not simulatedMove)
			pawnPromotionThisTurn=true;
            //qDebug()<<"promoteTest";
		}
		return true;
	}	
	errorReason="Pawn can only move 1 cell vertically in the opponents direction, move 2 cells forward if it hasnt moved before, take a piece diagnolly in the vertical direction of the opponent, or take a pawn that is on the same row that on that turn moved 2 cells forward not through or on a piece.";
	return false;
}



//tells what direction the pawn can go in. returns 1 if the pawn can only go in the negative direction, and -1 if the pawn can only go in the positive direction
int player::checkPawnIncrement(board::cell board_position[][8], int startingCellX, int startingCellY){
    if (board_position[startingCellX][startingCellY].myPiece.pieceColor=='W'){
		return -1;
	} else{
		return 1;
	}
}

//checks if pawn can move one space legally 
bool player::checkPawnMove1(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, board::cell board_position[][8]){
	if(startingCellY-endingCellY==colorIncrement and board_position[endingCellX][endingCellY].myPiece.pieceType=='\0' and startingCellX==endingCellX){
		return true;
	}
	return false;
}

//checks if pawn can move forward 2 cells legally
bool player::checkPawnMove2(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, int gameTurn, board::cell board_position[][8]){
	if ((startingCellY+1==2 or startingCellY+1==7) and startingCellY-endingCellY==colorIncrement*2 and startingCellX==endingCellX and board_position[endingCellX][endingCellY].myPiece.pieceType=='\0'){
		if (checkPieceInWay(startingCellX, startingCellY, endingCellX, endingCellY, board_position)){
			board_position[endingCellX][endingCellY].myPiece.enpassantable=gameTurn+1;
			return true;
		} else{
			errorReason="Pawn cannot move through pieces";	
		}
	}
	return false;
}

//check if the pawn can take normally legally
bool player::checkPawnTake(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, board::cell board_position[][8]){
	if (abs(startingCellX-endingCellX)==1 and startingCellY-endingCellY==colorIncrement and board_position[endingCellX][endingCellY].myPiece.pieceType!='\0'){
		return true;
	}
	return false;
}
//checks if piece can enpassant legally (does not actually enpassant)
bool player::checkPawnEnpassant(int startingCellX, int startingCellY, int endingCellX, int endingCellY, int colorIncrement, int gameTurn, board::cell board_position[][8]){
	if (board_position[endingCellX][startingCellY].myPiece.enpassantable==gameTurn and (startingCellX-endingCellX==1 or startingCellX-endingCellX==-1) and startingCellY-endingCellY==colorIncrement){
		enpassantedThisTurn=true;
		return true;				
	}
	return false;
}
//checks to see if a bishop can move legally
bool player::checkBishopLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){//possibly divide up into further functions later
	int xIncrement=checkIncrement(startingCellX, endingCellX);
	int yIncrement=checkIncrement(startingCellY, endingCellY);
	//checks to make sure the bishop is moving diagnolly
	if (abs(endingCellX-startingCellX)!=abs(endingCellY-startingCellY)){
		errorReason="The bishop can only move diagnolly in a 45 degree angle";
		return false;
	}
	if(checkPieceInWay(startingCellX, startingCellY, endingCellX, endingCellY, board_position)){
		return true;
	} else{
		errorReason="There is a piece in the way of the direction you are trying to move";
		return false;
	}

}

//checks to see if there is a piece in the way
bool player::checkPieceInWay(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){
	int xIncrement=checkIncrement(startingCellX, endingCellX);
	int yIncrement=checkIncrement(startingCellY, endingCellY);
	int bishopMultiplier=1;// used to alter the below for statement to act accurately if its a rook or bishop, 0 for bishop, 1 for rook
	if (abs(xIncrement)==abs(yIncrement)){
			bishopMultiplier=0;
	}

//checks to make sure there are no pieces in the way of the piece and its ending position
	for(int i=1; i<abs(((startingCellX-endingCellX)*bishopMultiplier)+(startingCellY-endingCellY)); i++){
		if (board_position[startingCellX+i*xIncrement][startingCellY+i*yIncrement].myPiece.pieceType!='\0'){
			return false;
		}
	}
	return true;
}

//checks to see what direction the piece is moving
int player::checkIncrement(int startingCellCoordinate,int endingCellCoordinate){
	if(endingCellCoordinate-startingCellCoordinate>0){
		return 1;
	} else if(endingCellCoordinate-startingCellCoordinate<0) {
		return -1;
	} else {
		return 0;
	}
}

bool player::checkRookLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){
	//checks to make sure rook is only moving one direction
	if ((endingCellX-startingCellX==0)==(endingCellY-startingCellY==0)){
		errorReason="The rook can only move verticaly or horizontal";
		return false;
	}
	if (checkPieceInWay(startingCellX, startingCellY, endingCellX, endingCellY, board_position)){
		return true;
	} else {
		errorReason="There is a piece in the way of the direction you are trying to move";
		return false;
	}

}
//checks to see if a queen can move legally
bool player::checkQueenLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){
	//checks to see if queen is moving like a rook or bishop
	if ((abs(endingCellX-startingCellX)!=abs(endingCellY-startingCellY)) and ((endingCellX-startingCellX==0)==(endingCellY-startingCellY==0))){
		errorReason="Queen can only move vertically or horizontally or diagnolly at a 45 degree angle.";
		return false;
	//checks to see if there is a piece in the way of the queens path
	} else if (checkPieceInWay(startingCellX, startingCellY, endingCellX, endingCellY, board_position)){
		return true;
	}
		errorReason="There is a piece in the way of the direction you are trying to move";
		return false;
}
//checks to see if a knight can move legally
bool player::checkKnightLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){
	if ((abs(startingCellX-endingCellX)==2 and abs(startingCellY-endingCellY)==1) or (abs(startingCellX-endingCellX)==1 and abs(startingCellY-endingCellY)==2)){
		return true;
	} else {
		errorReason="Knight can only move in 2 cells in one axis and then one cell in the other axis.";
		return false;
	}
}
//uses 2 below functions to check if the king can move legally
bool player::checkKingLegalMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove){
    //qDebug()<<"test2"<<checkKingRingMove(startingCellX, startingCellY, endingCellX, endingCellY, board_position)<<checkKingCastle(startingCellX, startingCellY, endingCellX, endingCellY, board_position, gameTurn,  simulatedMove);
	if (checkKingRingMove(startingCellX, startingCellY, endingCellX, endingCellY, board_position) or checkKingCastle(startingCellX, startingCellY, endingCellX, endingCellY, board_position, gameTurn,  simulatedMove)){
		return true;
	}

	return false;
}
//checks to see if a king can move normally
bool player::checkKingRingMove(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){
	if ( (abs(endingCellX-startingCellX)<=1) and (abs(endingCellY-startingCellY)<=1) ){
		return true;
	}

	errorReason="king can only move in a ring patter or 2 to the side to castle if neither the rook or king has moved and no pieces in the way. Also Cannot castle in or threw check.";
	return false;
}

//checks if the king can castle
bool player::checkKingCastle(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8], int gameTurn, bool simulatedMove){
	int castlingRookX; //used to keep track of where the rook is that is castling with the king
	//checks what side the rook is and if the king is moving the right number of cells
	int castleCheckIncrement;
	if (endingCellX-startingCellX==2){
		castlingRookX=7;
		castleCheckIncrement=-1;
	} else if(endingCellX-startingCellX==-2){
		castleCheckIncrement=1;
		castlingRookX=0;
	} else{
		errorReason="cell not 2 cells away from the king";
		return false;
	} 
	//checks if the king can castle through without bein in check
	if (not simulatedMove){
		for (int x=0; x<=2; x++){
			if (not checkMoveCheck(board_position, startingCellX, startingCellY, endingCellX+(x*castleCheckIncrement), endingCellY, gameTurn)){
				errorReason="cannot castle in or threw check";
				return false;
			}
		}
	}
	//checks if the king or rook is castleable
	if (board_position[startingCellX][startingCellY].myPiece.castleable!=true or board_position[castlingRookX][endingCellY].myPiece.castleable!=true)
	{
		errorReason="king or rook isnt castleable";
		return false;
	}

	//check if there is a piece in the kings or rooks way
	if (not checkPieceInWay(startingCellX, startingCellY, castlingRookX, endingCellY, board_position)){
		errorReason="there is a piece in the way of the king";
		return false;

	}
	
        castledThisTurn=true;//used to execute move later
        return true;


}

bool player::checkMoveCheck(board::cell board_position[][8], int startingCellX, int startingCellY, int endingCellX, int endingCellY, int gameTurn){
	board simulatedBoard;
	simulatedBoard.copyBoard(board_position);
	move(simulatedBoard.board_position, startingCellX, startingCellY, endingCellX, endingCellY, true);
    //bool tmpCastledThisTurn=castledThisTurn;
    //bool tmpEnpassantedThisTurn=enpassantedThisTurn;
    //bool tmpPawnPromotionThisTurn=pawnPromotionThisTurn;
	bool inCheck=false;
	int kingCellX;
	int kingCellY;
	for (int x=0; x<8; x++){
		for(int y=0; y<8; y++){
			if(simulatedBoard.board_position[x][y].myPiece.pieceType=='K' and (char)tolower(simulatedBoard.board_position[x][y].myPiece.pieceColor)==(char)tolower(playerColor)){
				kingCellX=x;
				kingCellY=y;
			}
		}
	}
	for(int x=0; x<8; x++){
		for(int y=0; y<8; y++){
			if(inCheck){
				break;	
			}
			if ((char)tolower(simulatedBoard.board_position[x][y].myPiece.pieceColor)!=(char)tolower(playerColor) and simulatedBoard.board_position[x][y].myPiece.pieceType!='\0'){
				inCheck=checkPieceLegalMove(x, y, kingCellX, kingCellY, simulatedBoard.board_position, gameTurn, true);
                if (inCheck){
                    qDebug()<<"test1"<<playerColor;
                }
			}
		}
		if (inCheck){
			break;
		}
		
	}
	if (inCheck){
		errorReason="If you move here, you will be in check";
		return false;
	} else{

		return true;
	}

}


bool player::checkEnoughMaterialDraw(int startingCellX, int startingCellY, int endingCellX, int endingCellY, board::cell board_position[][8]){
    int myBishopCount=0;
    int myKnightCount=0;
    int notMyBishopCount=0;
    int notMyKnightCount=0;

	for(int x=0; x<8; x++){
		for(int y=0; y<8; y++){
            if(tolower(board_position[x][y].myPiece.pieceColor)==tolower(playerColor)){
                switch(board_position[x][y].myPiece.pieceType){
                    case 'P':
                        return true;
                    case 'Q':
                        return true;
                    case 'R':
                        return true;
                    case 'B':
                        myBishopCount+=1;
                        break;
                    case 'N':
                        myKnightCount+=1;
                        break;
                }
            if(myBishopCount>=2 or (myBishopCount>=1 and myKnightCount>=1) or myKnightCount>=3){
				return true;
            }} else{
                if(tolower(board_position[x][y].myPiece.pieceColor)!=tolower(playerColor)){
                    switch(board_position[x][y].myPiece.pieceType){
                        case 'P':
                            return true;
                        case 'Q':
                            return true;
                        case 'R':
                            return true;
                        case 'B':
                            notMyBishopCount+=1;
                            break;
                        case 'N':
                            notMyKnightCount+=1;
                            break;
                    }
                    if(notMyBishopCount>=2 or (notMyBishopCount>=1 and notMyKnightCount>=1) or notMyKnightCount>=3){
                        return true;
                    }
                }
            }
        }
   }
	checkEnoughMaterial=false;
	return false;   
}
//split later into methods
bool player::checkStalemate(board::cell board_position[][8], int gameTurn){
	for (int x1=0; x1<8; x1++){
		for(int y1=0; y1<8; y1++){
			if (tolower(board_position[x1][y1].myPiece.pieceColor)==tolower(playerColor)){
				for(int x2=0; x2<8; x2++){	
					for(int y2=0; y2<8; y2++){
						if(checkLegalMove(x1, y1, x2, y2, board_position, gameTurn, tolower(board_position[x1][y1].myPiece.pieceColor), tolower(board_position[x1][y1].myPiece.pieceType), tolower(board_position[x2][y2].myPiece.pieceColor), true)){	
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}
bool player::checkCheckmate(board::cell board_position[][8], int gameTurn){
	if(checkCurrentlyInCheck(board_position, gameTurn) and checkStalemate(board_position, gameTurn)){
		return true;
	}
	return false;
}

bool player::checkCurrentlyInCheck(board::cell board_position[][8], int gameTurn){
	int KingCellX;
	int KingCellY;
	for (int x=0; x<8; x++){
		for(int y=0; y<8; y++){
			if(board_position[x][y].myPiece.pieceType=='K' and (char)tolower(board_position[x][y].myPiece.pieceColor)==(char)tolower(playerColor)){
				KingCellX=x;
				KingCellY=y;
			}
		}
	}
	if(not checkMoveCheck(board_position, KingCellX, KingCellY, KingCellX, KingCellY, gameTurn)){
		return true;
	}
	return false;
}
