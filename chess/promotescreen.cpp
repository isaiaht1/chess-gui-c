#include "promotescreen.h"
#include "ui_promotescreen.h"
#include <QPushButton>

QPushButton* knightPromotionButton;
QPushButton* bishopPromotionButton;
QPushButton* rookPromotionButton;
QPushButton* queenPromotionButton;

QString* myPiece;
int buttonSize=100;

promoteScreen::promoteScreen(char colorChar, QString& piece, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::promoteScreen)
{
    setWindowTitle("pawn promotion");
    QString color;
    if(colorChar=='w'){
        color="white";

    } else {
        color="black";
    }
    myPiece = &piece;
    ui->setupUi(this);
//sets up images
    QPixmap knight(":/image/Images/" + color +"Knight.png");
    QIcon knightIcon(knight);

    QPixmap bishop(":/image/Images/" + color +"Bishop.png");
    QIcon bishopIcon(bishop);

    QPixmap rook(":/image/Images/" + color + "Rook.png");
    QIcon rookIcon(rook);

    QPixmap queen(":/image/Images/" + color + "Queen.png");
    QIcon queenIcon(queen);


//knight promotion button
    knightPromotionButton =new QPushButton(this);
    knightPromotionButton->setFixedSize(buttonSize, buttonSize);
    knightPromotionButton->move(0+buttonSize*0, 100);
    knightPromotionButton->setText("");
    knightPromotionButton->setStyleSheet("border: 1px solid black;");
    knightPromotionButton->setIcon(knightIcon);
    knightPromotionButton->setIconSize(QSize(buttonSize*0.75, buttonSize*0.75));

    connect(knightPromotionButton, SIGNAL(pressed()), this, SLOT(promoteToKnightSlot()));
//bishop promotion button
    bishopPromotionButton =new QPushButton(this);
    bishopPromotionButton->setFixedSize(buttonSize, buttonSize);
    bishopPromotionButton->move(0+buttonSize*1, 100);
    bishopPromotionButton->setText("");
    bishopPromotionButton->setIcon(bishopIcon);
    bishopPromotionButton->setIconSize(QSize(buttonSize*0.75, buttonSize*0.75));

    bishopPromotionButton->setStyleSheet("border: 1px solid black;");

    connect(bishopPromotionButton, SIGNAL(pressed()), this, SLOT(promoteToBishopSlot()));
//rook promotion button
    rookPromotionButton =new QPushButton(this);
    rookPromotionButton->setFixedSize(buttonSize, buttonSize);
    rookPromotionButton->move(0+buttonSize*2, 100);
    rookPromotionButton->setText("");
    rookPromotionButton->setIcon(rookIcon);
    rookPromotionButton->setStyleSheet("border: 1px solid black;");
    rookPromotionButton->setIconSize(QSize(buttonSize*0.75, buttonSize*0.75));

    connect(rookPromotionButton, SIGNAL(pressed()), this, SLOT(promoteToRookSlot()));
//Queen promotion button
    queenPromotionButton =new QPushButton(this);
    queenPromotionButton->setFixedSize(buttonSize, buttonSize);
    queenPromotionButton->move(0+buttonSize*3, 100);
    queenPromotionButton->setText("");
    queenPromotionButton->setIcon(queenIcon);
    queenPromotionButton->setStyleSheet("border: 1px solid black;");
    queenPromotionButton->setIconSize(QSize(buttonSize*0.75, buttonSize*0.75));

    connect(queenPromotionButton, SIGNAL(pressed()), this, SLOT(promoteToQueenSlot()));
}

promoteScreen::~promoteScreen()
{
    delete ui;
}

void promoteScreen::promoteToKnightSlot(){
    *myPiece="K";
    accept();
}
void promoteScreen::promoteToBishopSlot(){
    *myPiece="B";
    accept();
}
void promoteScreen::promoteToRookSlot(){
    *myPiece="R";
    accept();
}
void promoteScreen::promoteToQueenSlot(){
    *myPiece="Q";
    accept();
}
