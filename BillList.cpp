#include "BillList.h"
#include "ui_BillList.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDate>
#include <QDir>
#include <QDebug>

BillList::BillList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillList)
{
    ui->setupUi(this);
    //set the widget size
    setMaximumSize(406, 245);
    setMinimumSize(406, 245);
    inforPath = QApplication::applicationDirPath() + QString("/infor");
    billPath = QApplication::applicationDirPath() + QString("/bill");
    UpdateInfor();
    //use lambda to represent the
    connect(ui->EnterButton, &QPushButton::clicked, [this](){
        QString name = ui->NameLineEdit->text();
        QString money = ui->MoneyLineEdit->text();
        //update remain money
        remainMoney -= money.toInt();
        QString remainMoneyStr;
        remainMoneyStr.setNum(remainMoney);
        WriteFile(remainMoneyStr, WriteStyle::Start);
        repaint();
        //write the cost to the file
        QString content = name + "\t" + money;
        WriteFile(content, WriteStyle::Append);
        //clear the lineEdit
        ui->MoneyLineEdit->clear();
        ui->NameLineEdit->clear();
    });
}

BillList::~BillList()
{
    delete ui;
}

//update the information from the infor file and use this function when progress begin
void BillList::UpdateInfor()
{
    auto information = ReadFile(inforPath);
    remainMoney = information[0].toInt();
    //change int to string to campare
    QString currentYear, currentMonth, currentDay;
    currentDay.setNum(QDate::currentDate().day());
    currentMonth.setNum(QDate::currentDate().month());
    currentYear.setNum(QDate::currentDate().year());

    //这里有个短路判断， 所以让day先比较为佳
    if(currentDay != information[3]
        || currentMonth != information[2]
        || currentYear != information[1])
    {
        QString dateTitle = currentYear + "-" + currentMonth
                + "-" + currentDay + ":";
        //update the information
        WriteFile(information[0], WriteStyle::Start);
        //print the date title
        WriteFile(dateTitle, WriteStyle::Append);
    }
}

void BillList::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::red); //set color
    QFont font("Courier New"); //set font
    font.setPixelSize(50); //set fontsize
    painter.setFont(font);
    //change int to string
    QString str;
    str.setNum(remainMoney);
    painter.drawText(250, 150, str);
    QRectF target(0, -30, 400, 160);
    QRectF source(0, 0, 1000, 400);
    //put the img folder to the dirpath that our executive file exits, i.e. ApplicationDirPath()
    QString imgpath = QApplication::applicationDirPath() + "/img/title.png";
    QImage img(imgpath);
    //QImage img("C:/Users/ventury/Documents/QT/2017/2017_03/20170321/WhereMyMoney/img/title.png");
    painter.drawImage(target, img, source);
}

//read the information from the file
//as for infor file, the first line is Remain Money
//and next is year, next is month, finally day
QVector<QString> BillList::ReadFile(QString path)
{
    QVector<QString> vstr;
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        //cpoy the every line to the container
        while(!in.atEnd())
        {
            QString line = in.readLine();
            vstr.push_back(line);
        }
        file.close();
    }
    return vstr;
}

void BillList::WriteFile(QString str, WriteStyle style)
{
    //write to infor ----> Start
    QFile file;
    if(style == WriteStyle::Start)
    {
        file.setFileName(inforPath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            exit(-1);
    }
    //write to bill ----> Append
    else
    {
        file.setFileName(billPath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
            exit(-1);
    }
    QTextStream out(&file);
    out << str << "\n";
    if(style == WriteStyle::Start)
    {
        out << QDate::currentDate().year() << "\n";
        out << QDate::currentDate().month() << "\n";
        out << QDate::currentDate().day() << "\n";
    }
    file.close();
}
