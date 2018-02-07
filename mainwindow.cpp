#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 100);

    ui->xinggeBox->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->rollPointBox->setAttribute(Qt::WA_TranslucentBackground, true);

    //3d6
    pointVec.append(ui->STRPoint);
    pointVec.append(ui->DEXPoint);
    pointVec.append(ui->CONPoint);
    pointVec.append(ui->APPPoint);
    pointVec.append(ui->POWPoint);
    pointVec.append(ui->LUCPoint);

    //2d6+6
    pointVec.append(ui->EDUPoint);
    pointVec.append(ui->INTPoint);
    pointVec.append(ui->SIZPoint);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rollButton_clicked()
{
    for(int i = 0; i < 6; ++i)
    {
        pointVec[i]->setValue(rollAdBplusC(3, 6, 0));   //3d6
    }
    for(int i = 6; i < 9; ++i)
    {
        pointVec[i]->setValue(rollAdBplusC(2, 6, 6));   //2d6+6
    }
}

int MainWindow::rollAdBplusC(int A = 1, int B = 100, int C = 0) //normal is 1d100+0
{
    int point = C;
    for (int i = 0; i < A; ++i)
    {
        point += 1 + qrand() % (B - 1);
    }
    return point;
}

void MainWindow::on_featureButton_clicked()
{

}
