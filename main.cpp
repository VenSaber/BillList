#include <QApplication>
#include "BillList.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    auto mywidgets = new BillList();
    mywidgets->show();
    app.exec();
    return 0;
}
