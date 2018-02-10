#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRegExp"
#include "QStringList"
//#include "QRandomGenerator"

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
    if(B == 1)
    {
        return A * B + C;
    }

//    QRandomGenerator r(1, B);
//    for(int i = 0;i < 10; ++i)
//    {
//        qDebug() << r.generate() << endl;
//    }

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
    file.close();

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
                                    //qDebug() << "conviction : " << str;
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
                                    //qDebug() << "VIP : " << str;
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
                                    //qDebug() << "VIPreason : " << str;
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
                                    //qDebug() << "VIPlace : " << str;
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
                                    //qDebug() << "VIThing : " << str;
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
                                    //qDebug() << "Feature : " << str;
                                }
                            }
                        }
                    }
                    //----------------------------------------------------
                    if (data.contains("STR"))
                    {
                        QJsonValue value = data.value("STR");
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
                                    STRVec.append(str);
                                    //qDebug() << "STR : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("CON"))
                    {
                        QJsonValue value = data.value("CON");
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
                                    CONVec.append(str);
                                    //qDebug() << "CON : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("SIZ"))
                    {
                        QJsonValue value = data.value("SIZ");
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
                                    SIZVec.append(str);
                                    //qDebug() << "SIZ : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("DEX"))
                    {
                        QJsonValue value = data.value("DEX");
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
                                    DEXVec.append(str);
                                    //qDebug() << "DEX : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("APP"))
                    {
                        QJsonValue value = data.value("APP");
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
                                    APPVec.append(str);
                                    //qDebug() << "APP : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("INT"))
                    {
                        QJsonValue value = data.value("INT");
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
                                    INTVec.append(str);
                                    //qDebug() << "INT : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("POW"))
                    {
                        QJsonValue value = data.value("POW");
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
                                    POWVec.append(str);
                                    //qDebug() << "POW : " << str;
                                }
                            }
                        }
                    }
                    if (data.contains("EDU"))
                    {
                        QJsonValue value = data.value("EDU");
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
                                    EDUVec.append(str);
                                    //qDebug() << "EDU : " << str;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::changeDBTGValue()
{
    int str = ui->STRPoint->value();
    int siz = ui->SIZPoint->value();
    int sum = (str + siz) * 5;
    if(sum >= 2 && sum < 64)
    {
        ui->DBshow_lineEdit->setText("-2");
        ui->TGshow_lineEdit->setText("-2");
    }
    else if(sum >= 64 && sum < 84)
    {
        ui->DBshow_lineEdit->setText("-1");
        ui->TGshow_lineEdit->setText("-1");
    }
    else if(sum >= 84 && sum < 124)
    {
        ui->DBshow_lineEdit->setText("0");
        ui->TGshow_lineEdit->setText("0");
    }
    else if(sum >= 125 && sum < 164)
    {
        ui->DBshow_lineEdit->setText("1d4");
        ui->TGshow_lineEdit->setText("1");
    }
    else if(sum >= 165 && sum < 204)
    {
        ui->DBshow_lineEdit->setText("1d6");
        ui->TGshow_lineEdit->setText("2");
    }
    else
    {
        sum -= 204;
        int sum1 = sum / 80;
        int sum2 = sum % 80;
        int sum3 = sum1 + (sum2 && 1);
        //qDebug() << "sum1:" << sum1 << "sum2" << sum2 << "sum3" << sum3;
        ui->DBshow_lineEdit->setText(QString::number(sum3 + 1, 10) + "d6");
        ui->TGshow_lineEdit->setText(QString::number(sum3 + 2, 10));
    }
}

void MainWindow::changeMOVValue()
{
    int str = ui->STRPoint->value();
    int dex = ui->DEXPoint->value();
    int siz = ui->SIZPoint->value();
    if(str < siz && dex < siz)
    {
        ui->MOVshow_lineEdit->setText("7");
    }
    else if(str > siz && dex > siz)
    {
        ui->MOVshow_lineEdit->setText("9");
    }
    else
    {
        ui->MOVshow_lineEdit->setText("8");
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

void MainWindow::on_STRPoint_valueChanged(int arg1)
{
    ui->STRshow_lineEdit->setText(QString::number(arg1 * 5, 10));

    this->changeDBTGValue();
    this->changeMOVValue();

    //change describe text
    int str = arg1 * 5;
    if(str >= 200)
    {
        ui->STRdes_lineEdit->setText(STRVec[6]);
    }
    else if(str >= 140)
    {
        ui->STRdes_lineEdit->setText(STRVec[5]);
    }
    else if(str >= 99)
    {
        ui->STRdes_lineEdit->setText(STRVec[4]);
    }
    else if(str >= 90)
    {
        ui->STRdes_lineEdit->setText(STRVec[3]);
    }
    else if(str >= 50)
    {
        ui->STRdes_lineEdit->setText(STRVec[2]);
    }
    else if(str >= 15)
    {
        ui->STRdes_lineEdit->setText(STRVec[1]);
    }
    else
    {
        ui->STRdes_lineEdit->setText(STRVec[0]);
    }
}

void MainWindow::on_CONPoint_valueChanged(int arg1)
{
    ui->CONshow_lineEdit->setText(QString::number(arg1 * 5, 10));

    ui->HPshow_lineEdit->setText(QString::number((ui->CONPoint->value() + ui->SIZPoint->value()) / 2, 10));

    //change describe text
    int con = arg1 * 5;
    if(con >= 200)
    {
        ui->CONdes_lineEdit->setText(CONVec[7]);
    }
    else if(con >= 140)
    {
        ui->CONdes_lineEdit->setText(CONVec[6]);
    }
    else if(con >= 99)
    {
        ui->CONdes_lineEdit->setText(CONVec[5]);
    }
    else if(con >= 90)
    {
        ui->CONdes_lineEdit->setText(CONVec[4]);
    }
    else if(con >= 50)
    {
        ui->CONdes_lineEdit->setText(CONVec[3]);
    }
    else if(con >= 15)
    {
        ui->CONdes_lineEdit->setText(CONVec[2]);
    }
    else if(con >= 1)
    {
        ui->CONdes_lineEdit->setText(CONVec[1]);
    }
    else
    {
        ui->CONdes_lineEdit->setText(CONVec[0]);
    }
}

void MainWindow::on_SIZPoint_valueChanged(int arg1)
{
    ui->SIZshow_lineEdit->setText(QString::number(arg1 * 5, 10));

    ui->HPshow_lineEdit->setText(QString::number((ui->CONPoint->value() + ui->SIZPoint->value()) / 2, 10));

    this->changeDBTGValue();

    //change describe text
    int siz = arg1 * 5;
    if(siz >= 200)
    {
        ui->SIZdes_lineEdit->setText(SIZVec[7]);
    }
    else if(siz >= 180)
    {
        ui->SIZdes_lineEdit->setText(SIZVec[6]);
    }
    else if(siz >= 150)
    {
        ui->SIZdes_lineEdit->setText(SIZVec[5]);
    }
    else if(siz >= 99)
    {
        ui->SIZdes_lineEdit->setText(SIZVec[4]);
    }
    else if(siz >= 80)
    {
        ui->SIZdes_lineEdit->setText(SIZVec[3]);
    }
    else if(siz >= 60)
    {
        ui->SIZdes_lineEdit->setText(SIZVec[2]);
    }
    else if(siz >= 15)
    {
        ui->SIZdes_lineEdit->setText(SIZVec[1]);
    }
    else
    {
        ui->SIZdes_lineEdit->setText(SIZVec[0]);
    }
}

void MainWindow::on_DEXPoint_valueChanged(int arg1)
{
    ui->DEXshow_lineEdit->setText(QString::number(arg1 * 5, 10));

    this->changeMOVValue();

    //change describe text
    int dex = arg1 * 5;
    if(dex >= 200)
    {
        ui->DEXdes_lineEdit->setText(DEXVec[6]);
    }
    else if(dex >= 120)
    {
        ui->DEXdes_lineEdit->setText(DEXVec[5]);
    }
    else if(dex >= 99)
    {
        ui->DEXdes_lineEdit->setText(DEXVec[4]);
    }
    else if(dex >= 90)
    {
        ui->DEXdes_lineEdit->setText(DEXVec[3]);
    }
    else if(dex >= 50)
    {
        ui->DEXdes_lineEdit->setText(DEXVec[2]);
    }
    else if(dex >= 15)
    {
        ui->DEXdes_lineEdit->setText(DEXVec[1]);
    }
    else
    {
        ui->DEXdes_lineEdit->setText(DEXVec[0]);
    }
}

void MainWindow::on_APPPoint_valueChanged(int arg1) // <=99
{
    if(arg1 >= 20)
    {
        ui->APPshow_lineEdit->setText("99");
    }
    else
    {
        ui->APPshow_lineEdit->setText(QString::number(arg1 * 5, 10));
    }

    //change describe text
    int app = arg1 * 5;
    if(app >= 99)
    {
        ui->APPdes_lineEdit->setText(APPVec[4]);
    }
    else if(app >= 90)
    {
        ui->APPdes_lineEdit->setText(APPVec[3]);
    }
    else if(app >= 50)
    {
        ui->APPdes_lineEdit->setText(APPVec[2]);
    }
    else if(app >= 15)
    {
        ui->APPdes_lineEdit->setText(APPVec[1]);
    }
    else
    {
        ui->APPdes_lineEdit->setText(APPVec[0]);
    }
}

void MainWindow::on_INTPoint_valueChanged(int arg1)
{
    ui->INTshow_lineEdit->setText(QString::number(arg1 * 5, 10));

    //change describe text
    int intelligence = arg1 * 5;
    if(intelligence >= 210)
    {
        ui->INTdes_lineEdit->setText(INTVec[6]);
    }
    else if(intelligence >= 140)
    {
        ui->INTdes_lineEdit->setText(INTVec[5]);
    }
    else if(intelligence >= 99)
    {
        ui->INTdes_lineEdit->setText(INTVec[4]);
    }
    else if(intelligence >= 90)
    {
        ui->INTdes_lineEdit->setText(INTVec[3]);
    }
    else if(intelligence >= 50)
    {
        ui->INTdes_lineEdit->setText(INTVec[2]);
    }
    else if(intelligence >= 15)
    {
        ui->INTdes_lineEdit->setText(INTVec[1]);
    }
    else
    {
        ui->INTdes_lineEdit->setText(INTVec[0]);
    }
}

void MainWindow::on_POWPoint_valueChanged(int arg1)
{
    ui->POWshow_lineEdit->setText(QString::number(arg1 * 5, 10));

    ui->SANshow_lineEdit->setText(QString::number(arg1 * 5, 10));

    ui->MPshow_lineEdit->setText(QString::number(arg1, 10));

    //change describe text
    int pow = arg1 * 5;
    if(pow >= 210)
    {
        ui->POWdes_lineEdit->setText(POWVec[6]);
    }
    else if(pow >= 140)
    {
        ui->POWdes_lineEdit->setText(POWVec[5]);
    }
    else if(pow >= 100)
    {
        ui->POWdes_lineEdit->setText(POWVec[4]);
    }
    else if(pow >= 90)
    {
        ui->POWdes_lineEdit->setText(POWVec[3]);
    }
    else if(pow >= 50)
    {
        ui->POWdes_lineEdit->setText(POWVec[2]);
    }
    else if(pow >= 15)
    {
        ui->POWdes_lineEdit->setText(POWVec[1]);
    }
    else
    {
        ui->POWdes_lineEdit->setText(POWVec[0]);
    }
}

void MainWindow::on_EDUPoint_valueChanged(int arg1) // <=99
{
    if(arg1 >= 20)
    {
        ui->EDUshow_lineEdit->setText("99");
    }
    else
    {
        ui->EDUshow_lineEdit->setText(QString::number(arg1 * 5, 10));
    }

    //change describe text
    int edu = arg1 * 5;
    if(edu >= 200)
    {
        ui->EDUdes_lineEdit->setText(EDUVec[7]);
    }
    else if(edu >= 140)
    {
        ui->EDUdes_lineEdit->setText(EDUVec[6]);
    }
    else if(edu >= 99)
    {
        ui->EDUdes_lineEdit->setText(EDUVec[5]);
    }
    else if(edu >= 90)
    {
        ui->EDUdes_lineEdit->setText(EDUVec[4]);
    }
    else if(edu >= 50)
    {
        ui->EDUdes_lineEdit->setText(EDUVec[3]);
    }
    else if(edu >= 15)
    {
        ui->EDUdes_lineEdit->setText(EDUVec[2]);
    }
    else if(edu >= 1)
    {
        ui->EDUdes_lineEdit->setText(EDUVec[1]);
    }
    else
    {
        ui->EDUdes_lineEdit->setText(EDUVec[0]);
    }
}

void MainWindow::on_LUCPoint_valueChanged(int arg1)
{
    ui->LUCshow_lineEdit->setText(QString::number(arg1 * 5, 10));
}

void MainWindow::on_rollExpressionPushButton_clicked()
{
    QString expression = ui->rollExpressionLineEdit->text();

    QStringList strList = expression.split(QRegExp("+"));

    QRegExp pattern("[1-9][0-9]*d[1-9][0-9]*");
    QRegExp pattern2("[1-9][0-9]*");

    QRegExp reg(pattern);
    QRegExp reg2(pattern2);

    QString rollText = expression + " = ";
    int rollAnswer = 0;

    for(QString s : strList)
    {
        qDebug() << s << " ";
        if(reg.exactMatch(s))   //xdy
        {
            QStringList tList = s.split(QRegExp("d"));
            if(!tList.isEmpty())
            {
                int x = tList.at(0).toInt();
                int y = tList.at(1).toInt();
                int ans = rollAdBplusC(x, y, 0);
                rollAnswer += ans;
                rollText.append(s + "(" + QString::number(ans, 10) + ") ");
            }
        }
        else if(reg2.exactMatch(s)) //z
        {
            rollText.append("(" + s + ") ");
            rollAnswer += s.toInt();
        }
        else
        {
            ui->rollExpressionLineEdit->setToolTip("格式：(个数)d(骰面数)*m + (常数)*n");
            return;
        }
    }

    rollText.append(" = " + QString::number(rollAnswer, 10));
    ui->rollExpressionTextEdit->setPlainText(rollText);
}

