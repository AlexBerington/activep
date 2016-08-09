#include <QApplication>
#include "wind.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wind window;

    window.setWindowIcon(QIcon("logo.png"));
    window.show();
    window.move(500,300);
    window.resize(450,350);
    QMessageBox::information(NULL, "Внимание", "Для начала работы выберите файл *.csv !");
    window.activateWindow();
    return a.exec();
}
