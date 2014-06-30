#include "mainwindow.h"
#include "databasehandler.h"
#include "person.h"
#include "customwidget.h"
#include <QApplication>
#include <QDebug>
#include <QTableView>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    /*Person pers;
    pers.id=1;
    pers.fio="oooo";

    d.putPerson(pers);*/

    //QSqlQueryModel *model = new QSqlQueryModel;
    //model->setQuery("SELECT * FROM Persons");

    /*QTableView *viewTable = new QTableView;
    viewTable->setModel(d.queryAllData());
    viewTable->show();*/

    /*MyWidget *tableView = new MyWidget;
    tableView->show();*/
    //Person *pers = d.getPerson(45);
    //qDebug() << pers->fio;


    /*for (int i = 0; i < model.rowCount(); ++i) {
            int id = model.record(i).value("_id").toInt();
            QString name = model.record(i).value("fio").toString();
            qDebug() << id << name;
        }*/

    a.setWindowIcon(QIcon(":icons/ic_launcher"));

    MainWindow w;
    w.show();

    return a.exec();
}
