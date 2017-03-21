#ifndef BILLLIST_H
#define BILLLIST_H

#include <QWidget>

namespace Ui {
class BillList;
}

class BillList : public QWidget
{
    Q_OBJECT

public:
    explicit BillList(QWidget *parent = 0);
    ~BillList();
    void paintEvent(QPaintEvent *event) override;
    enum class ReadContent
    {REMAIN, YEAR, MONTH, DAT};
    enum class WriteStyle
    {Append, Start};
private:
    int ReadFile(QString path, ReadContent content);
    void WriteFile(QString path, QString str, WriteStyle style);
private:
    Ui::BillList *ui;
    int remainMoney;
};

#endif // BILLLIST_H
