#include "mainwindow.h"
#include "databasehandler.h"
#include "person.h"
#include <QApplication>
#include <QDebug>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":icons/ic_launcher"));

    MainWindow w;
    w.show();

    QTranslator *qt_translator = new QTranslator;
    if ( qt_translator->load( ":tr/qtbase_ru.qm" ) )
    {
        a.installTranslator( qt_translator );
    }

    return a.exec();
}
