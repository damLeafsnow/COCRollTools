#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QVector>
#include <QSpinBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_rollButton_clicked();

    void on_featureButton_clicked();

private:
    int rollAdBplusC(int A, int B, int C);

private:
    Ui::MainWindow *ui;
    QTime t;
    QVector<QSpinBox*> pointVec;
};

#endif // MAINWINDOW_H
