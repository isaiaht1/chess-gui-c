#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "player.h"
#include "screen.h"
#include "notepad.h"
#include "/Users/isaiahmac/Downloads/json-develop/single_include/nlohmann/json.hpp"
#include <promotescreen.h>

#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <iostream>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>
#include <QEventLoop>


//globals
board board1;
QVector<QVector<QPushButton*>> cellButtons(8);
QVector<QLineEdit*> lineEditNames;

QLabel* whoTurnLabel;
QLabel* currentTurnLabel;
QLabel* errorReasonLabel;
QLabel* replayLabel;
QPushButton* replayYesButton;
QPushButton* replayNoButton;
QPushButton* drawButton;
QPushButton* resignButton;


screen screen1;
std::string tmpTest="";
notepad pad;
player playersArr[2]={player("null",'w'), player("null",'b')}; //array of players

std::string myTime;
int turn=0;
//std::string startingCell;
//std::string endingCell;
int validMove=false;
bool drawOffered=false;
std::vector<std::string> boardIdentifiers;
int positionRepeat=0;
std::string errorReason = "";
QString replayGameFile="";
bool replayGameBool=false;

bool startOfTurn=true;
QString startTurn;
QString endTurn;
QString promotionPiece="";

const int cellSize=70;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(900,700);


//gets time and gives it to notepad
    myTime=getTime();
    pad.initilizeNotePad(myTime);


    if(QMessageBox::question(this, "replay game?", "Do you wish to replay a game")==QMessageBox::Yes){
        replayGameFile = QFileDialog::getOpenFileName(this,
            "Open Save File", "/Users/isaiahmac/Documents/code/QT/chess/chess/moveFiles", "Image Files (*.json)");
        replayGameBool=true;
    }

//line edit for  first player to enter name and adds it to name vector
    QLineEdit* name1 =new QLineEdit(this);
    name1->setFixedSize(100, 15);
    name1->move(65, 10);
    name1->setStyleSheet("border: 1px solid black;");
    lineEditNames.append(name1);


//text to show purpose of name1 line edit
    QLabel* nameLabel1 =new QLabel(this);
    nameLabel1->setFixedSize(80, 15);
    nameLabel1->move(10, 10);
    nameLabel1->setText("Name: ");

//line edit for second player to enter name and adds it to name vector
    QLineEdit* name2 =new QLineEdit(this);
    name2->setFixedSize(100, 15);
    name2->move(65, 70+cellSize*8);
    name2->setStyleSheet("border: 1px solid black;");
    lineEditNames.append(name2);

//line edit for  first player to enter name and adds it to name vector
    QLineEdit* lineBlank=new QLineEdit(this);
    lineBlank->setFixedSize(100, 15);
    lineBlank->move(1000, 1000);
    lineBlank->setStyleSheet("border: 1px solid black;");

//text to show purpose of name2 line edit
    QLabel* nameLabel2 =new QLabel(this);
    nameLabel2->setFixedSize(80, 15);
    nameLabel2->move(10, 70+cellSize*8);
    nameLabel2->setText("Name: ");


//text to show turn number
    currentTurnLabel =new QLabel(this);
    currentTurnLabel->setFixedSize(80, 15);
    currentTurnLabel->move(600, 10);
    currentTurnLabel->setText("Turn: "+ QString::number((turn-turn%2)/2));

//text to show whos move
    whoTurnLabel =new QLabel(this);
    whoTurnLabel->setFixedSize(200, 15);
    whoTurnLabel->move(600, 30);
    whoTurnLabel->setText("Who's turn: "+ QString(lineEditNames[(turn+1)%2]->text()));

//text to show whos move
    errorReasonLabel =new QLabel(this);
    errorReasonLabel->setFixedSize(300, 200);
    errorReasonLabel->move(600, 100);
    errorReasonLabel->setText("Error reason: "+ QString::fromStdString(errorReason));
    errorReasonLabel->hide();
    errorReasonLabel->adjustSize();
//draw button
    drawButton =new QPushButton(this);
    drawButton->setFixedSize(100, 25);
    drawButton->move(600, 500);
    drawButton->setText("draw");
    drawButton->setStyleSheet("border: 1px solid black;");
    connect(drawButton, SIGNAL(pressed()), this, SLOT(drawButtonPressedSlot()));
//resign button
    resignButton =new QPushButton(this);
    resignButton->setFixedSize(100, 25);
    resignButton->move(720, 500);
    resignButton->setText("resign");
    resignButton->setStyleSheet("border: 1px solid black;");
    connect(resignButton, SIGNAL(pressed()), this, SLOT(resignButtonPressedSlot()));

//initilizes buttons, adds them to cellButtons vector, and gives some attributes, connects them to buttonPressedSlot()
    for (int x=0; x<8; x++){
       for(int y=0; y<8; y++){
           cellButtons[x].append(new QPushButton(this));
           cellButtons[x][y]->setFixedSize(cellSize,cellSize);
           cellButtons[x][y]->move(20+x*cellSize,550-y*cellSize);
           cellButtons[x][y]->setStyleSheet("border: 1px solid black;");

           if (board1.board_position[x][y].cellColor=='w'){
               cellButtons[x][y]->setStyleSheet("border: 1px solid black; background-color: white;");
           } else if(board1.board_position[x][y].cellColor=='b') {
               cellButtons[x][y]->setStyleSheet("border: 1px solid black; background-color: green;");
           }
           connect(cellButtons[x][y], SIGNAL(pressed()), this, SLOT(buttonPressedSlot()));
       }
    }
    updateDisplay();
    if(replayGameBool){
        replayLabel =new QLabel(this);
        replayLabel->setFixedSize(100, 15);
        replayLabel->move(600, 580);
        replayLabel->setText("replay next turn?");

        replayYesButton =new QPushButton(this);
        replayYesButton->setFixedSize(50, 25);
        replayYesButton->move(600, 600);
        replayYesButton->setText("yes");
        replayYesButton->setStyleSheet("border: 1px solid black;");
        connect(replayYesButton, SIGNAL(pressed()), this, SLOT(replayYesButtonPressedSlot()));


        replayNoButton =new QPushButton(this);
        replayNoButton->setFixedSize(50, 25);
        replayNoButton->move(670, 600);
        replayNoButton->setText("No");
        replayNoButton->setStyleSheet("border: 1px solid black;");
        connect(replayNoButton, SIGNAL(pressed()), this, SLOT(replayNoButtonPressedSlot()));

    }

}

void MainWindow::replayYesButtonPressedSlot(){
    if (turn>=pad.getTotalTurn(replayGameFile.toStdString())){
        replayGameBool=false;

        replayYesButton->deleteLater();
        replayYesButton->disconnect();

        delete replayLabel;

        replayNoButton->disconnect();
        delete replayNoButton;
        return;
    }
    startTurn=QString::fromStdString(pad.getStartMove(replayGameFile.toStdString(), turn+1));
    endTurn=QString::fromStdString(pad.getEndMove(replayGameFile.toStdString(), turn+1));
    qDebug()<<"2"<<board1.board_position[5][1].myPiece.pieceType;
    validMove=playersArr[(turn+0)%2].setupMove(board1.board_position, startTurn.toStdString(), endTurn.toStdString(), turn);
    turn+=1;
    qDebug()<<"1"<<board1.board_position[5][1].myPiece.pieceType;

    if (playersArr[(turn+0)%2].pawnPromotionThisTurn==true){
        promotionPiece=QString::fromStdString(pad.getPromotionPiece(replayGameFile.toStdString(), turn));
        onPromotionPieceChoseSlot();
    } else {
        pad.writeMove(myTime, turn, startTurn.toStdString(), endTurn.toStdString(), 'E');
    }
    if (playersArr[0].move50RuleCheck>=50 and playersArr[1].move50RuleCheck>=50){
            if(QMessageBox::question(this, "replay game?", "Do you wish to draw the game (50 move rule)")==QMessageBox::Yes){
                    QMessageBox::information(this, "game over", "game drawn due to 50 move rule");
                    close();
            }
    }

    if(playersArr[(turn+0)%2].checkCheckmate(board1.board_position, turn)){
        QMessageBox::information(this, "game over", QString(lineEditNames[(turn+1)%2]->text()) +" won due to checkmate");
        close();
    } else
    if(playersArr[(turn+0)%2].checkStalemate(board1.board_position, turn)){
        QMessageBox::information(this, "game over", "game drawn due to stalemate");
        close();
    }

    if(not playersArr[(turn+0)%2].checkEnoughMaterial){
        QMessageBox::information(this, "game over", "game drawn due to not enough material");
        close();
    }

    updateDisplay();

    return;

}

void MainWindow::MainWindow::replayNoButtonPressedSlot(){
    replayGameBool=false;

    replayNoButton->deleteLater();
    replayNoButton->disconnect();

    delete replayLabel;
    replayYesButton->disconnect();
    delete replayYesButton;
    return;
}

void MainWindow::drawButtonPressedSlot(){
    if(QMessageBox::question(this, "draw game?", "Do you wish to draw this game?")==QMessageBox::Yes){
        QMessageBox::information(this, "game ended", "game was ended due to an agreement");
        close();

    }
}

void MainWindow::resignButtonPressedSlot(){
    QMessageBox::information(this, "game ended", lineEditNames[(turn+1)%2]->text() +" won due to resignation");
    close();
}

void MainWindow::buttonPressedSlot(){
    //qDebug()<<board1.board_position[0][0].myPiece.pieceType;
    if(replayGameBool){ return;}
    QPushButton *myPushButton = qobject_cast<QPushButton *>(sender());
    if(not boardIdentifiers.empty()){
        positionRepeat=0;
        for(const std::string& i : boardIdentifiers){
            if (i==boardIdentifiers.back()){
                positionRepeat+=1;
            }
        }
    }

    if (positionRepeat>=3){
        QMessageBox::information(this, "Game has been drawn", "this application will now close");
        close();
    }
    for(int x=0; x<8; x++){
        for(int y=0; y<8; y++){
            if(cellButtons[x][y]==myPushButton){
                if(startOfTurn){
                    cellButtons[x][y]->setStyleSheet("border: 4px solid black; background-color: red");
                    startTurn=QString(numberToAlphabet(x+ '0'))+QString::number((y));
                    startOfTurn=false;
                } else {
                    endTurn=QString(numberToAlphabet(x+ '0'))+QString::number((y));
                    qDebug()<<startTurn<<endTurn;
                    startOfTurn=true;
                    validMove=playersArr[(turn+0)%2].setupMove(board1.board_position, startTurn.toStdString(), endTurn.toStdString(), turn);
                    if (validMove){
                        turn+=1;
                        errorReasonLabel->setVisible(false);
                        boardIdentifiers.push_back(board1.getBoardIdentification());

                        if (playersArr[(turn+1)%2].pawnPromotionThisTurn==true){
                            promotePiece();

                        } else {
                            promotionPiece="";
                            pad.writeMove(myTime, turn, startTurn.toStdString(), endTurn.toStdString(), 'E');
                        }
                        if (playersArr[0].move50RuleCheck>=50 and playersArr[1].move50RuleCheck>=50){
                                if(QMessageBox::question(this, "replay game?", "Do you wish to draw the game (50 move rule)")==QMessageBox::Yes){
                                        QMessageBox::information(this, "game over", "game drawn due to 50 move rule");
                                        close();
                                }
                        }
                        if(not playersArr[(turn+0)%2].checkEnoughMaterial){
                            QMessageBox::information(this, "game over", "game drawn due to not enough material");
                            close();
                        }

                        if(playersArr[(turn+0)%2].checkCheckmate(board1.board_position, turn)){
                            QMessageBox::information(this, "game over", QString(lineEditNames[(turn+1)%2]->text()) +" won due to checkmate");
                            close();
                        }

                        if(playersArr[(turn+0)%2].checkStalemate(board1.board_position, turn)){
                            QMessageBox::information(this, "game over", "game drawn due to stalemate");
                            close();
                        }


                    } else {
                        errorReason = playersArr[turn%2].errorReason;
                        errorReasonLabel->setText("Error reason: "+ QString::fromStdString(errorReason));
                        errorReasonLabel->setVisible(true);
                        errorReasonLabel->setWordWrap(true);
                    }
                }
            }
        }
    }
    updateDisplay();
}

void MainWindow::updateDisplay(){
    QPixmap whitePawn(":/image/Images/whitePawn.png");
    QIcon whitePawnIcon(whitePawn);

    QPixmap whiteKnight(":/image/Images/whiteKnight.png");
    QIcon whiteKnightIcon(whiteKnight);

    QPixmap whiteBishop(":/image/Images/whiteBishop.png");
    QIcon whiteBishopIcon(whiteBishop);

    QPixmap whiteRook(":/image/Images/whiteRook.png");
    QIcon whiteRookIcon(whiteRook);

    QPixmap whiteQueen(":/image/Images/whiteQueen.png");
    QIcon whiteQueenIcon(whiteQueen);

    QPixmap whiteKing(":/image/Images/whiteKing.png");
    QIcon whiteKingIcon(whiteKing);

    QPixmap blackPawn(":/image/Images/blackPawn.png");
    QIcon blackPawnIcon(blackPawn);

    QPixmap blackKnight(":/image/Images/blackKnight.png");
    QIcon blackKnightIcon(blackKnight);

    QPixmap blackBishop(":/image/Images/blackBishop.png");
    QIcon blackBishopIcon(blackBishop);

    QPixmap blackRook(":/image/Images/blackRook.png");
    QIcon blackRookIcon(blackRook);

    QPixmap blackQueen(":/image/Images/blackQueen.png");
    QIcon blackQueenIcon(blackQueen);

    QPixmap blackKing(":/image/Images/blackKing.png");
    QIcon blackKingIcon(blackKing);

    QPixmap blank(":/image/Images/Blank.png");
    QIcon blankIcon(blank);

    for (int x=0; x<8; x++){
        for(int y=0; y<8; y++){
            if(board1.board_position[x][y].myPiece.pieceColor=='B'){
                 switch (board1.board_position[x][y].myPiece.pieceType){
                    case 'P':
                     cellButtons[x][y]->setIcon(blackPawnIcon);
                     break;
                    case 'N':
                     cellButtons[x][y]->setIcon(blackKnightIcon);
                     break;
                    case 'B':
                     cellButtons[x][y]->setIcon(blackBishopIcon);
                     break;
                    case 'R':
                     cellButtons[x][y]->setIcon(blackRookIcon);
                     break;
                    case 'Q':
                     cellButtons[x][y]->setIcon(blackQueenIcon);
                     break;
                    case 'K':
                     cellButtons[x][y]->setIcon(blackKingIcon);
                     break;
                    default:
                     cellButtons[x][y]->setIcon(blankIcon);

                }

            } else {
                switch (board1.board_position[x][y].myPiece.pieceType){
                   case 'P':
                    cellButtons[x][y]->setIcon(whitePawnIcon);
                    break;
                   case 'N':
                    cellButtons[x][y]->setIcon(whiteKnightIcon);
                    break;
                   case 'B':
                    cellButtons[x][y]->setIcon(whiteBishopIcon);
                    break;
                   case 'R':
                    cellButtons[x][y]->setIcon(whiteRookIcon);
                    break;
                   case 'Q':
                    cellButtons[x][y]->setIcon(whiteQueenIcon);
                     break;
                   case 'K':
                    cellButtons[x][y]->setIcon(whiteKingIcon);
                    break;
                   default:
                    cellButtons[x][y]->setIcon(blankIcon);
                }

            }
            cellButtons[x][y]->setIconSize(QSize(cellSize*0.75, cellSize*0.75));
            if(startOfTurn){
                if (board1.board_position[x][y].cellColor=='w'){
                    cellButtons[x][y]->setStyleSheet("border: 1px solid black; background-color: white;");
                } else if(board1.board_position[x][y].cellColor=='b') {
                    cellButtons[x][y]->setStyleSheet("border: 1px solid black; background-color: green;");
                }
            }
        }
    }
    currentTurnLabel->setText("Turn: "+ QString::number((turn-turn%2)/2));
    whoTurnLabel->setText("Who's turn: "+ QString(lineEditNames[(turn+1)%2]->text()));
    for(int i = 0; i<playersArr[0].piecesTaken.size() ;i++){
        QLabel* piecesTakenLabel=new QLabel(this);
        piecesTakenLabel->setFixedSize(30,30);
        piecesTakenLabel->move(20+i*30,650);
        piecesTakenLabel->setStyleSheet("border: 0px solid black;");
        piecesTakenLabel->show();
             switch (playersArr[0].piecesTaken[i]){
                case 'P':
                 blackPawn.scaled(1,1);
                 piecesTakenLabel->setPixmap(blackPawn.scaled(30, 30));
                 break;
                case 'N':
                 blackPawn.scaled(1,1);
                 piecesTakenLabel->setPixmap(blackKnight.scaled(30, 30));                 break;
                case 'B':
                 blackBishop.scaled(1,1);
                 piecesTakenLabel->setPixmap(blackBishop.scaled(30, 30));                 break;
                case 'R':
                 blackRook.scaled(1,1);
                 piecesTakenLabel->setPixmap(blackRook.scaled(30, 30));                 break;
                case 'Q':
                 blackQueen.scaled(1,1);
                 piecesTakenLabel->setPixmap(blackQueen.scaled(30, 30));                 break;
                case 'K':
                 blackKing.scaled(1,1);
                 piecesTakenLabel->setPixmap(blackKing.scaled(30, 30));                 break;
                default:
                 blank.scaled(1,1);
                 piecesTakenLabel->setPixmap(blank.scaled(30, 30));
             }
        }
    for(int i = 0; i<playersArr[1].piecesTaken.size() ;i++){
        QLabel* piecesTakenLabel=new QLabel(this);
        piecesTakenLabel->setFixedSize(30,30);
        piecesTakenLabel->move(20+i*30,28);
        piecesTakenLabel->setStyleSheet("border: 0px solid black;");
        piecesTakenLabel->show();
        switch (playersArr[1].piecesTaken[i]){
            case 'P':
             whitePawn.scaled(1,1);
             piecesTakenLabel->setPixmap(whitePawn.scaled(30, 30));
             break;
            case 'N':
             whiteKnight.scaled(1,1);
             piecesTakenLabel->setPixmap(whiteKnight.scaled(30, 30));
             break;
            case 'B':
             whiteBishop.scaled(1,1);
             piecesTakenLabel->setPixmap(whiteBishop.scaled(30, 30));
             break;
            case 'R':
             whiteRook.scaled(1,1);
             piecesTakenLabel->setPixmap(whiteRook.scaled(30, 30));             break;
            case 'Q':
             whiteBishop.scaled(1,1);
             piecesTakenLabel->setPixmap(whiteQueen.scaled(30, 30));
             break;
            case 'K':
             whiteBishop.scaled(1,1);
             piecesTakenLabel->setPixmap(whiteKing.scaled(30, 30));
             break;
            default:
             blank.scaled(1,1);
             piecesTakenLabel->setPixmap(blank.scaled(30, 30));
         }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::getTime(){
    time_t time = std::time(nullptr);
    tm time2 = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&time2, "%d-%m-%Y_%H-%M-%S");
    return oss.str();
}


void MainWindow::promotePiece(){
    promoteScreen* screen= new promoteScreen(playersArr[turn%2].playerColor, promotionPiece, nullptr);
    connect(screen, SIGNAL(accepted()), SLOT(onPromotionPieceChoseSlot()));
    screen->setModal(true);
    screen->show();
}

void MainWindow::onPromotionPieceChoseSlot(){
    playersArr[(turn+1)%2].promotePawn(endTurn.toStdString(), board1.board_position, promotionPiece.toStdString()[0]);
    pad.writeMove(myTime, turn, startTurn.toStdString(), endTurn.toStdString(), promotionPiece.toStdString()[0]);
    playersArr[(turn+1)%2].pawnPromotionThisTurn=false;
    updateDisplay();
}


char MainWindow::numberToAlphabet(char num){
    std::string alphabet= "abcdefghijklmnopqrstuvwxyz";
    std::string numbers= "0123456789";
    for (int i=0; i<alphabet.size(); i++){
        if(num==numbers[i]){
            return alphabet[i];
        }
    }

    return 'z';
}

//optional: find reason behind color bug that may or may not be re appearing




