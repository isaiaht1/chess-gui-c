#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void buttonPressedSlot();
    void replayYesButtonPressedSlot();
    void replayNoButtonPressedSlot();
    void drawButtonPressedSlot();
    void resignButtonPressedSlot();
    void onPromotionPieceChoseSlot();

private:
    Ui::MainWindow *ui;
    char numberToAlphabet(char num);
    std::string getTime();
    std::string chooseGame();
    void promotePiece();
    void updateDisplay();



};
#endif // MAINWINDOW_H
