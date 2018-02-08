#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 100);

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

    readJsonData();

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

void MainWindow::readJsonData()
{
    QFile file(":/new/json/resourse/feature.json");
    if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "read json file failed";
            return;
        }
    QByteArray byteArray = file.readAll();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("data"))
            {
                QJsonValue dataValue = object.value("data");
                if(dataValue.isObject())    // dataValue 是对象
                {
                    QJsonObject data = dataValue.toObject();
                    if (data.contains("conviction"))
                    {
                        QJsonValue value = data.value("conviction");
                        if (value.isArray())
                        {  // Version 的 value 是数组
                            QJsonArray array = value.toArray();
                            int nSize = array.size();
                            for (int i = 0; i < nSize; ++i)
                            {
                                QJsonValue value = array.at(i);
                                if (value.isString())
                                {
                                    QString str = value.toString();
                                    convictionVec.append(str);
                                    qDebug() << "conviction : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("VIP"))
                    {
                        QJsonValue value = data.value("VIP");
                        if (value.isArray())
                        {  // Version 的 value 是数组
                            QJsonArray array = value.toArray();
                            int nSize = array.size();
                            for (int i = 0; i < nSize; ++i)
                            {
                                QJsonValue value = array.at(i);
                                if (value.isString())
                                {
                                    QString str = value.toString();
                                    VIPVec.append(str);
                                    qDebug() << "VIP : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("VIPreason"))
                    {
                        QJsonValue value = data.value("VIPreason");
                        if (value.isArray())
                        {  // Version 的 value 是数组
                            QJsonArray array = value.toArray();
                            int nSize = array.size();
                            for (int i = 0; i < nSize; ++i)
                            {
                                QJsonValue value = array.at(i);
                                if (value.isString())
                                {
                                    QString str = value.toString();
                                    VIPreasonVec.append(str);
                                    qDebug() << "VIPreason : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("VIPlace"))
                    {
                        QJsonValue value = data.value("VIPlace");
                        if (value.isArray())
                        {  // Version 的 value 是数组
                            QJsonArray array = value.toArray();
                            int nSize = array.size();
                            for (int i = 0; i < nSize; ++i)
                            {
                                QJsonValue value = array.at(i);
                                if (value.isString())
                                {
                                    QString str = value.toString();
                                    VIPlaceVec.append(str);
                                    qDebug() << "VIPlace : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("VIThing"))
                    {
                        QJsonValue value = data.value("VIThing");
                        if (value.isArray())
                        {  // Version 的 value 是数组
                            QJsonArray array = value.toArray();
                            int nSize = array.size();
                            for (int i = 0; i < nSize; ++i)
                            {
                                QJsonValue value = array.at(i);
                                if (value.isString())
                                {
                                    QString str = value.toString();
                                    VIThingVec.append(str);
                                    qDebug() << "VIThing : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("Feature"))
                    {
                        QJsonValue value = data.value("Feature");
                        if (value.isArray())
                        {  // Version 的 value 是数组
                            QJsonArray array = value.toArray();
                            int nSize = array.size();
                            for (int i = 0; i < nSize; ++i)
                            {
                                QJsonValue value = array.at(i);
                                if (value.isString())
                                {
                                    QString str = value.toString();
                                    FeatureVec.append(str);
                                    qDebug() << "Feature : " << str;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::on_featureButton_clicked()
{
    ui->lineEdit_conviction->setText(convictionVec[qrand() % convictionVec.size()]);
    ui->lineEdit_VIP->setText(VIPVec[qrand() % VIPVec.size()]);
    ui->lineEdit_VIPreason->setText(VIPreasonVec[qrand() % VIPreasonVec.size()]);
    ui->lineEdit_VIPlace->setText(VIPlaceVec[qrand() % VIPlaceVec.size()]);
    ui->lineEdit_VIThing->setText(VIThingVec[qrand() % VIThingVec.size()]);
    ui->lineEdit_Feature->setText(FeatureVec[qrand() % FeatureVec.size()]);
}
