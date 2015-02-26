#include "databasehandler.h"

DatabaseHandler::DatabaseHandler()
{
    dateFormat = "dd-MM-yyyy";

    dirDB = QDir("database");
    dirBackUp = QDir(dirDB.path() + "/backup");
    dirBackUp.setNameFilters(QStringList("??-??-????.db"));
    nameDB = dirDB.path() + "/contacts.db";

    if (!dirDB.exists()){
        QDir().mkdir(dirDB.path());
    }

    if (!dirBackUp.exists()){
        QDir().mkdir(dirBackUp.path());
    }

    //Делаем бэкап но не более 5-ти копий
    if (!QFile::exists(dirBackUp.path()+"/"+QDate::currentDate().toString(dateFormat)+".db")){
        if (dirBackUp.entryList().count() >= 5) {
            removeOldest(&dirBackUp);
        }
        doBackup(nameDB,&dirBackUp);
    }
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

void DatabaseHandler::closeDB()
{
    db.close();
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

        //Указываем версию базы (иначе в Андроиде ошибка будет)
        query.exec("PRAGMA user_version = 1");

        //Таблица настроек
        query.exec("CREATE TABLE Settings (pos INTEGER NOT NULL DEFAULT (0), status TEXT NOT NULL DEFAULT (1), id INTEGER NOT NULL DEFAULT(0), import TEXT NOT NULL DEFAULT (1))");
        query.exec("INSERT INTO Settings (pos,status,id,import) VALUES ('0','1','0','" + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm") + "')");
        //Основная таблица
        ret = query.exec(Person::CREATE_TABLE);

        }

    Person person = Person();
    person.id = 10;
    person.fio = "Иванова Алёна +79586541257 3 этаж";
    person.dr = 755654400000L;
    person.parents = "Андрей +7 999 33 44 44\nСветлана +7 999 555 55 55";
    person.m_addr = "ул. Ленина, д1, кв 45";
    person.a_addr = "";
    person.info = "";
    person.d_dolten = 1404432000000L;
    person.dolten = "Узнать, что случилось";
    person.d_nextdate = 1400889600000L;
    person.nextdate = "Просто поговорить";
    person.d_lastdate = 1400457600000L;
    person.lastdate = "07.07.2014 Просто пообщались\n----------\n05.05.2014 Уточнить, что случилось";
    person.status = 1;
    putPerson(person);

    person.id = 15;
    person.fio = "Петров Сергей Первомайская налево +79125745896";
    person.dr = 895536000000L;
    person.parents = "Павел +7 999 33 44 44\nИрина +7 999 555 55 55";
    person.m_addr = "ул. Первомайская, д102, кв 435";
    person.a_addr = "";
    person.info = "";
    person.d_dolten = 1404259200000L;
    person.dolten = "Узнать, что случилось";
    person.d_nextdate = 1402790400000L;
    person.nextdate = "Просто поговорить";
    person.d_lastdate = 1315850400000L;
    person.lastdate = "07.07.2014 Просто пообщались\n----------\n05.05.2014 Уточнить, что случилось";
    person.status = 0;
    putPerson(person);

    person.id = 23;
    person.fio = "Сидоров Пётр соседский дом +79455891247";
    person.dr = 916444800000L;
    person.parents = "Надежда +7 999 33 44 44\nИван +7 999 555 55 55";
    person.m_addr = "ул. 50 лет октября, д12, кв 35";
    person.a_addr = "";
    person.info = "";
    person.d_dolten = 1409356800000L;
    person.dolten = "Узнать, что случилось";
    person.d_nextdate = 1403827200000L;
    person.nextdate = "Просто поговорить";
    person.d_lastdate = 0L;
    person.lastdate = "07.07.2014 Просто пообщались\n----------\n05.05.2014 Уточнить, что случилось";
    person.status = 1;
    putPerson(person);


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
    //model.setFilter(Person::COL_ID + " = " + QString::number(person.id));
    model.setFilter("rowid = " + QString::number(person.id));
    model.select();

    QSqlRecord values = person.getContent(model.record());
    //values.remove(0);

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

void DatabaseHandler::setLastPos(int pos, QString curStatus){
    bool result = false;

    QSqlTableModel model;
    model.setTable("Settings");
    model.select();

    QSqlRecord values = model.record();
    values.setValue("pos",pos);
    values.setValue("status",curStatus);
    values.setValue("id",0);
    values.setValue("import",model.data(model.index(0,3)));

    result = model.setRecord(0,values);
    model.submitAll();

    if (!result){

        result = model.insertRecord(-1,values);
        model.submitAll();
    }

}


void DatabaseHandler::getLastPos(int& pos,QString& curStatus){
    QSqlTableModel model;
    model.setTable("Settings");
    model.select();

    pos = model.data(model.index(0,0)).toInt();
    if (model.data(model.index(0,1)) == QVariant::Invalid){
        curStatus = "1";
    }
    else {
        curStatus = model.data(model.index(0,1)).toString();
    }
}


void DatabaseHandler::doBackup(QString nameDB, QDir *dirBackUp){
    QFile::copy(nameDB,
                dirBackUp->path()+"/"+QDate::currentDate().toString(dateFormat)+".db");
}

void DatabaseHandler::removeOldest(QDir *dirBackUp){
    QDate d1 = QDate().fromString(dirBackUp->entryInfoList().at(0).baseName(),dateFormat);
    QString fileForDel = dirBackUp->entryInfoList().at(0).absoluteFilePath();
    QDate d2;
    for (int i = 1; i < dirBackUp->entryInfoList().count(); i++){
        d2 = QDate().fromString(dirBackUp->entryInfoList().at(i).baseName(),dateFormat);
        if (d1 > d2){
            d1 = d2;
            fileForDel = dirBackUp->entryInfoList().at(i).absoluteFilePath();
        }
    }

    QFile::remove(fileForDel);
}

