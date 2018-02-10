#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QVector>
#include <QSpinBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QDebug>

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

    void on_STRPoint_valueChanged(int arg1);

    void on_CONPoint_valueChanged(int arg1);

    void on_SIZPoint_valueChanged(int arg1);

    void on_DEXPoint_valueChanged(int arg1);

    void on_APPPoint_valueChanged(int arg1);

    void on_INTPoint_valueChanged(int arg1);

    void on_POWPoint_valueChanged(int arg1);

    void on_EDUPoint_valueChanged(int arg1);

    void on_LUCPoint_valueChanged(int arg1);

    void on_rollExpressionPushButton_clicked();

private:
    int rollAdBplusC(int A, int B, int C);
    void readJsonData();
    void changeDBTGValue();
    void changeMOVValue();

private:
    Ui::MainWindow *ui;
    QTime t;
    QVector<QSpinBox*> pointVec;
    QJsonParseError jsonError;
    QVector<QString> convictionVec, VIPVec, VIPreasonVec, VIPlaceVec, VIThingVec, FeatureVec;
    QVector<QString> STRVec, CONVec, SIZVec, DEXVec, APPVec, INTVec, POWVec, EDUVec;
};

#endif // MAINWINDOW_H
