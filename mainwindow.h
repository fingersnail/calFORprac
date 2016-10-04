#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <expression.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString alreadyInputString;
    enum operand{plus, minus, by, divide};
    void setSLOT();
    bool isZoreCanOutput();
    bool isDotCanOutPut();
    bool isOperatorCanOutPut();
    void numberButtonClicked(int clickedNUmber);
private slots:
    void button0Clicked();
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();
    void button5Clicked();
    void button6Clicked();
    void button7Clicked();
    void button8Clicked();
    void button9Clicked();
    void dotButtonClicked();
    void signButtonClicked();
    void plusButtonClicked();
    void minusButtonClicked();
    void byButtonClicked();
    void divideButtonClicked();
    void powerButtonClicked();
    void CButtonClicked();
    //void CEButtonClicked();
    void backButtonClicked();
    void equalsButtonClicked();
    void sinButtonClicked();
    void cosButtonClicked();
    void lnButtonClicked();
    void leftBraketButtonClicked();
    void rightBraketButtonClicked();

};

#endif // MAINWINDOW_H
