#ifndef PROMOTESCREEN_H
#define PROMOTESCREEN_H

#include <QDialog>

namespace Ui {
class promoteScreen;
}

class promoteScreen : public QDialog
{
    Q_OBJECT

public:
    explicit promoteScreen(char colorChar, QString& piece,  QWidget *parent = nullptr);
    ~promoteScreen();

private slots:
    void promoteToKnightSlot();
    void promoteToBishopSlot();
    void promoteToRookSlot();
    void promoteToQueenSlot();


private:
    Ui::promoteScreen *ui;
};

#endif // PROMOTESCREEN_H
