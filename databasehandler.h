#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H
#include "person.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

class DatabaseHandler
{
public:
    DatabaseHandler();
    ~DatabaseHandler();
public:
    bool openDB();
    void closeDB();
    bool deleteDB();
    bool createPersonTable();
    QSqlError lastError();
    Person *getPerson(long id);
    void setLastPos(int pos, QString curStatus);
    //int getLastPos();
    void getLastPos(int& pos,QString& curStatus);
    bool putPerson(Person person);
    bool removePerson(long id);
    QSqlQueryModel *queryAllData();
    QSqlQueryModel *queryOneRow(long id);

private:
    QSqlDatabase db;
    QString nameDB;
    QDir dirDB;
    QDir dirBackUp;
    QString dateFormat;
    void doBackup(QString nameDB, QDir *dirBackUp);
    void removeOldest(QDir *dirBackUp);
};

#endif // DATABASEHANDLER_H
