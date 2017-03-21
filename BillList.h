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
    enum class WriteStyle
    {Append, Start};
private:
    //read RemainMoney, current year, current month, current day from the file
    QVector<QString> ReadFile(QString path);
    //write the updated information or billList to file
    void WriteFile(QString str, WriteStyle style);
    //update the information from the infor file and use this function when progress begin
    void UpdateInfor();
private:
    Ui::BillList *ui;
    QString inforPath;
    QString billPath;
    int remainMoney;
};

#endif // BILLLIST_H
