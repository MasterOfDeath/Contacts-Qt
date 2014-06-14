#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H
#include "person.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QFile>

#include <QMessageBox>
#include <QDebug>

class DatabaseHandler
{
public:
    DatabaseHandler();
    ~DatabaseHandler();
public:
    bool openDB();
    bool deleteDB();
    bool createPersonTable();
    QSqlError lastError();
    Person *getPerson(long id);
    bool putPerson(Person person);
    bool removePerson(long id);
    QSqlQueryModel *queryAllData();
    QSqlQueryModel *queryOneRow(long id);

private:
    QSqlDatabase db;
    QString nameDB;
};

#endif // DATABASEHANDLER_H
