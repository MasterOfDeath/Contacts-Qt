#include "databasehandler.h"

DatabaseHandler::DatabaseHandler()
{
    nameDB = "contacts.db";
}

DatabaseHandler::~DatabaseHandler()
{
    db.close();
}

bool DatabaseHandler::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nameDB);
    QFile dbFile(nameDB);
    if (dbFile.exists()) {
        // Open databasee
        return db.open();
    } else {
        db.open();
        return createPersonTable();
    }
}

QSqlError DatabaseHandler::lastError()
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseHandler::deleteDB()
{
    // Close database
    db.close();
    return QFile::remove(nameDB);
}

bool DatabaseHandler::createPersonTable()
    {
    // Create table "persons"
    bool ret = false;
    if (db.isOpen())
        {
        QSqlQuery query;
        ret = query.exec(Person::CREATE_TABLE);

        }
    return ret;
    }

Person *DatabaseHandler::getPerson(long id) {

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;

    query->prepare("SELECT * FROM Persons WHERE _id = :id");
    query->bindValue(":id",(qlonglong)id);
    if(!query->exec())
        {
            QMessageBox::critical(0,"Database error",query->lastError().text());
            //qDebug() << query.lastQuery();
        }

    model->setQuery(*query);

    Person *item = new Person(*model);

    delete query;
    delete model;

    return item;
    }

bool DatabaseHandler::putPerson(Person person) {
    bool success = false;
    bool result = false;

    QSqlTableModel model;
    model.setTable(Person::TABLE_NAME);
    model.setFilter(Person::COL_ID + " = " + QString::number(person.id));
    model.select();

    QSqlRecord values = person.getContent(model.record());
    values.remove(0);

    if (person.id > -1) {
        result = model.setRecord(0,values);
        model.submitAll();
    }

    if (result) {
        success = true;
    } else {
        // Update failed or wasn't possible, insert instead
        result = model.insertRecord(-1,values);
        model.submitAll();
        qDebug() << "Insert";

        if (result) {
            //person.id = id;
            success = true;
        } else {qDebug() << model.lastError().text();}
    }

    return success;
    }

bool DatabaseHandler::removePerson(long id) {
    bool result = false;
    QSqlQuery query;
    query.prepare("DELETE FROM Persons WHERE _id = :id");
    query.bindValue(":id",(qlonglong)id);

    result = query.exec();
    return result;
    }

QSqlQueryModel *DatabaseHandler::queryAllData() {
    QSqlQueryModel *result =  new QSqlQueryModel;
    result->setQuery("SELECT * FROM Persons");
    return result;
    }

QSqlQueryModel *DatabaseHandler::queryOneRow(long id) {
    QSqlQueryModel *result =  new QSqlQueryModel;
    result->setQuery("SELECT * FROM Persons WHERE _id = " + QString::number(id));

    return result;
    }

