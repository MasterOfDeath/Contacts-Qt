#include "mainwindow.h"
#include "databasehandler.h"
#include "person.h"
#include <QApplication>
#include <QDebug>
#include <QTableView>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //qDebug() << Person::CREATE_TABLE;

    DatabaseHandler d;
    d.openDB();

    /*Person pers;
    pers.id=1;
    pers.fio="oooo";

    d.putPerson(pers);*/

    //QSqlQueryModel *model = new QSqlQueryModel;
    //model->setQuery("SELECT * FROM Persons");

    QTableView *viewTable = new QTableView;
    viewTable->setModel(d.queryAllData());
    viewTable->show();

    //Person *pers = d.getPerson(45);
    //qDebug() << pers->fio;


    /*for (int i = 0; i < model.rowCount(); ++i) {
            int id = model.record(i).value("_id").toInt();
            QString name = model.record(i).value("fio").toString();
            qDebug() << id << name;
        }*/

    //MainWindow w;
    //w.show();

    return a.exec();
}
