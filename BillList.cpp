#include "BillList.h"
#include "ui_BillList.h"
#include <QPaintEvent>
#include <QPainter>

BillList::BillList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillList)
{
    ui->setupUi(this);
    setMaximumSize(406, 245);
    setMinimumSize(406, 245);
    remainMoney = 5000;
}

BillList::~BillList()
{
    delete ui;
}

void BillList::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    QFont font("Courier New");
    font.setPixelSize(50);
    painter.setFont(font);
    QString str;
    str.setNum(remainMoney);
    painter.drawText(250, 150, str);
}
