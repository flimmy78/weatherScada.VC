#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTranslator *translator = NULL;
	translator = new QTranslator(0);
	translator->load("language/weatherScada_zh.qm");
	a.installTranslator(translator);
    MainWindow w;
    w.show();

    return a.exec();
}
