#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    alreadyInputString = ui->resultLineEdit->text();
    setSLOT();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSLOT() {
    QObject::connect(ui->button0,SIGNAL(clicked()),this,SLOT(button0Clicked()));
    QObject::connect(ui->button1,SIGNAL(clicked()),this,SLOT(button1Clicked()));
    QObject::connect(ui->button2,SIGNAL(clicked()),this,SLOT(button2Clicked()));
    QObject::connect(ui->button3,SIGNAL(clicked()),this,SLOT(button3Clicked()));
    QObject::connect(ui->button4,SIGNAL(clicked()),this,SLOT(button4Clicked()));
    QObject::connect(ui->button5,SIGNAL(clicked()),this,SLOT(button5Clicked()));
    QObject::connect(ui->button6,SIGNAL(clicked()),this,SLOT(button6Clicked()));
    QObject::connect(ui->button7,SIGNAL(clicked()),this,SLOT(button7Clicked()));
    QObject::connect(ui->button8,SIGNAL(clicked()),this,SLOT(button8Clicked()));
    QObject::connect(ui->button9,SIGNAL(clicked()),this,SLOT(button9Clicked()));
    QObject::connect(ui->dotButton,SIGNAL(clicked()),this,SLOT(dotButtonClicked()));
    QObject::connect(ui->plusButton,SIGNAL(clicked()),this,SLOT(plusButtonClicked()));
    QObject::connect(ui->minusButton,SIGNAL(clicked()),this,SLOT(minusButtonClicked()));
    QObject::connect(ui->byButton,SIGNAL(clicked()),this,SLOT(byButtonClicked()));
    QObject::connect(ui->divideButton,SIGNAL(clicked()),this,SLOT(divideButtonClicked()));
    QObject::connect(ui->CButton,SIGNAL(clicked()),this,SLOT(CButtonClicked()));
    //QObject::connect(ui->CEButton,SIGNAL(clicked()),this,SLOT(CEButtonClicked()));
    QObject::connect(ui->backButton,SIGNAL(clicked()),this,SLOT(backButtonClicked()));
    QObject::connect(ui->equalsButton,SIGNAL(clicked()),this,SLOT(equalsButtonClicked()));
    QObject::connect(ui->sinButton,SIGNAL(clicked()),this,SLOT(sinButtonClicked()));
    QObject::connect(ui->cosButton,SIGNAL(clicked()),this,SLOT(cosButtonClicked()));
    QObject::connect(ui->lnButton,SIGNAL(clicked()),this,SLOT(lnButtonClicked()));
    QObject::connect(ui->leftBraketButton,SIGNAL(clicked()),this,SLOT(leftBraketButtonClicked()));
    QObject::connect(ui->rightBracketButton,SIGNAL(clicked()),this,SLOT(rightBraketButtonClicked()));
}

void MainWindow::button0Clicked() {

    if(isZoreCanOutput()) {
        numberButtonClicked(0);
    }
}

bool MainWindow::isZoreCanOutput() {
    alreadyInputString= ui->resultLineEdit->text();
    if (alreadyInputString.isEmpty()) {
        return true;
    }

    QChar lastCharOfResult = alreadyInputString[alreadyInputString.size() - 1];
    if(alreadyInputString.size() == 1) {
        return lastCharOfResult != '0';
    }

    QChar secondLastCharOfResult = alreadyInputString[alreadyInputString.size() - 2];
    return secondLastCharOfResult.isDigit();
}

void MainWindow::button1Clicked() {
    numberButtonClicked(1);
}

void MainWindow::button2Clicked() {
    numberButtonClicked(2);
}

void MainWindow::button3Clicked() {
    numberButtonClicked(3);
}

void MainWindow::button4Clicked() {
    numberButtonClicked(4);
}

void MainWindow::button5Clicked() {
    numberButtonClicked(5);
}

void MainWindow::button6Clicked() {
    numberButtonClicked(6);
}

void MainWindow::button7Clicked() {
    numberButtonClicked(7);
}

void MainWindow::button8Clicked() {
    numberButtonClicked(8);
}

void MainWindow::button9Clicked() {
    numberButtonClicked(9);
}

void MainWindow::numberButtonClicked(int clickedNUmber){
    alreadyInputString = ui->resultLineEdit->text();
    ui->resultLineEdit->setText(alreadyInputString + QString::number(clickedNUmber));
}

void MainWindow::dotButtonClicked(){
    if (isDotCanOutPut()) {
        alreadyInputString = ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + ".");
    }
}

bool MainWindow::isDotCanOutPut() {
    alreadyInputString = ui->resultLineEdit->text();
    if (alreadyInputString.isEmpty()) {
        return false;
    }

    QChar lastCharOfResult = alreadyInputString[alreadyInputString.size() - 1];
    return lastCharOfResult.isDigit();
}



void MainWindow::plusButtonClicked(){
    if (isOperatorCanOutPut()) {
        alreadyInputString = ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "+");
    }
}

void MainWindow::minusButtonClicked(){
    if (isOperatorCanOutPut()) {
        alreadyInputString = ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "-");
    }
}

void MainWindow::byButtonClicked() {
    if (isOperatorCanOutPut()) {
        alreadyInputString = ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "×");
    }
}

void MainWindow::divideButtonClicked(){
    if (isOperatorCanOutPut()) {
        alreadyInputString = ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "÷");
    }
}

bool MainWindow::isOperatorCanOutPut(){
    alreadyInputString = ui->resultLineEdit->text();
    if (alreadyInputString.isEmpty()) {
        return false;
    }

    QChar lastCharOfResult = alreadyInputString[alreadyInputString.size() - 1];
    return lastCharOfResult.isDigit() || lastCharOfResult == ')';
}

void MainWindow::CButtonClicked() {
    ui->resultLineEdit->clear();
}

//void MainWindow::CEButtonClicked() {
//    ui->resultLineEdit->clear();
//}

void MainWindow::backButtonClicked() {
    alreadyInputString = ui->resultLineEdit->text();
    if (alreadyInputString.isEmpty()) {
        return;
    }

    alreadyInputString.remove(alreadyInputString.size() - 1, 1);
    ui->resultLineEdit->setText(alreadyInputString);
}
void MainWindow::sinButtonClicked() {
    alreadyInputString = ui->resultLineEdit->text();
    ui->resultLineEdit->setText(alreadyInputString+"sin");
}

void MainWindow::cosButtonClicked() {
    alreadyInputString = ui->resultLineEdit->text();
    ui->resultLineEdit->setText(alreadyInputString+"cos");
}

void MainWindow::lnButtonClicked() {
    alreadyInputString = ui->resultLineEdit->text();
    ui->resultLineEdit->setText(alreadyInputString+"ln");
}

void MainWindow::leftBraketButtonClicked() {
    alreadyInputString = ui->resultLineEdit->text();
    ui->resultLineEdit->setText(alreadyInputString+"(");
}

void MainWindow::rightBraketButtonClicked() {
    alreadyInputString = ui->resultLineEdit->text();
    ui->resultLineEdit->setText(alreadyInputString+")");
}

void MainWindow::equalsButtonClicked() {
    alreadyInputString = ui->resultLineEdit->text();
    double result = expression::cal_E(alreadyInputString);
    ui->resultLineEdit->setText(QString::number(result));
}
