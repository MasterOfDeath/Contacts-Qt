#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

class Person
{
public:
    Person();
    Person(QSqlQueryModel &model);
    QSqlRecord getContent(QSqlRecord origRecord);
    const static QString TABLE_NAME;
    const static QString COL_ID;
    const static QString COL_FIO;
    const static QString COL_DR;
    const static QString COL_PARENTS;
    const static QString COL_M_ADDR;
    const static QString COL_A_ADDR;
    const static QString COL_INFO;
    const static QString COL_D_DOLTEN;
    const static QString COL_DOLTEN;
    const static QString COL_D_NEXTDATE;
    const static QString COL_NEXTDATE;
    const static QString COL_D_LASTDATE;
    const static QString COL_LASTDATE;
    const static QString COL_STATUS;
    const static QString COL_DAYS;
    const static QStringList FIELDS;
    const static QString CREATE_TABLE;
    // Fields corresponding to database columns
    long id;
    QString fio;
    long dr;
    QString parents;
    QString m_addr;
    QString a_addr;
    QString info;
    long d_dolten;
    QString dolten;
    long d_nextdate;
    QString nextdate;
    long d_lastdate;
    QString lastdate;
    int status;
};

#endif // PERSON_H
