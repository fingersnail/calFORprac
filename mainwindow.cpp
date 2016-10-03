#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    QObject::connect(ui->CEButton,SIGNAL(clicked()),this,SLOT(CEButtonClicked()));
}

void MainWindow::button0Clicked() {

    if(isZoreCanOutput()) {
        numberButtonClicked(0);
    }
}

bool MainWindow::isZoreCanOutput() {
    QString alreadyInputString= ui->resultLineEdit->text();
    if (alreadyInputString.isEmpty()) {
        return true;
    }

    QChar lastCharOfResult = alreadyInputString[alreadyInputString.size()-1];
    if(alreadyInputString.size() == 1) {
        return lastCharOfResult != '0';
    }

    QChar secondLastCharOfResult = alreadyInputString[alreadyInputString.size()-2];
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

void MainWindow::dotButtonClicked(){
    if (isDotCanOutPut()) {
        QString alreadyInputString= ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + ".");
    }
}

bool MainWindow::isDotCanOutPut() {
    QString alreadyInputString= ui->resultLineEdit->text();
    if (alreadyInputString.isEmpty()) {
        return false;
    }

    QChar lastCharOfResult = alreadyInputString[alreadyInputString.size()-1];
    return lastCharOfResult.isDigit();
}

void MainWindow::numberButtonClicked(int clickedNUmber){
    QString alreadyInputString= ui->resultLineEdit->text();
    ui->resultLineEdit->setText(alreadyInputString + QString::number(clickedNUmber));
}

void MainWindow::plusButtonClicked(){
    if (isOperandCanOutPut()) {
        QString alreadyInputString= ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "+");
    }
}

void MainWindow::minusButtonClicked(){
    if (isOperandCanOutPut()) {
        QString alreadyInputString= ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "-");
    }
}

void MainWindow::byButtonClicked() {
    if (isOperandCanOutPut()) {
        QString alreadyInputString= ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "*");
    }
}

void MainWindow::divideButtonClicked(){
    if (isOperandCanOutPut()) {
        QString alreadyInputString= ui->resultLineEdit->text();
        ui->resultLineEdit->setText(alreadyInputString + "÷");
    }
}

bool MainWindow::isOperandCanOutPut(){
    QString alreadyInputString= ui->resultLineEdit->text();
    if (alreadyInputString.isEmpty()) {
        return false;
    }

    QChar lastCharOfResult = alreadyInputString[alreadyInputString.size()-1];
    return lastCharOfResult.isDigit();
}

void MainWindow::CButtonClicked() {
    ui->resultLineEdit->clear();
}

void MainWindow::CEButtonClicked() {
    ui->resultLineEdit->clear();
}
