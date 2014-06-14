#include "person.h"

const QString Person::TABLE_NAME = "Persons";
const QString Person::COL_ID = "_id";
const QString Person::COL_FIO = "fio";
const QString Person::COL_DR = "dr";
const QString Person::COL_PARENTS = "parents";
const QString Person::COL_M_ADDR = "m_addr";
const QString Person::COL_A_ADDR = "a_addr";
const QString Person::COL_INFO = "info";
const QString Person::COL_D_DOLTEN = "d_dolten";
const QString Person::COL_DOLTEN = "dolten";
const QString Person::COL_D_NEXTDATE = "d_nextdate";
const QString Person::COL_NEXTDATE = "nextdate";
const QString Person::COL_D_LASTDATE = "d_lastdate";
const QString Person::COL_LASTDATE = "lastdate";
const QString Person::COL_STATUS = "status";
const QString Person::COL_DAYS = "case when (d_lastdate > 0) then (strftime('%s', 'now','localtime')*1000 - d_lastdate)/86400000 else 'no' end as day";
const QStringList Person::FIELDS = QStringList() << "COL_ID"
                                                 << "COL_FIO"
                                                 << "COL_DR"
                                                 << "COL_PARENTS"
                                                 << "COL_M_ADDR"
                                                 << "COL_A_ADDR"
                                                 << "COL_INFO"
                                                 << "COL_D_DOLTEN"
                                                 << "COL_DOLTEN"
                                                 << "COL_D_NEXTDATE"
                                                 << "COL_NEXTDATE"
                                                 << "COL_D_LASTDATE"
                                                 << "COL_LASTDATE"
                                                 << "COL_STATUS"
                                                 << "COL_DAYS";
const QString Person::CREATE_TABLE =
            "CREATE TABLE " + Person::TABLE_NAME + "("
                    + Person::COL_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + Person::COL_FIO + " TEXT NOT NULL DEFAULT '',"
                    + Person::COL_DR + " INTEGER DEFAULT '',"
                    + Person::COL_PARENTS + " TEXT DEFAULT '',"
                    + Person::COL_M_ADDR + " TEXT DEFAULT '',"
                    + Person::COL_A_ADDR + " TEXT DEFAULT '',"
                    + Person::COL_INFO + " TEXT DEFAULT '',"
                    + Person::COL_D_DOLTEN + " INTEGER DEFAULT '',"
                    + Person::COL_DOLTEN + " TEXT DEFAULT '',"
                    + Person::COL_D_NEXTDATE + " INTEGER DEFAULT '',"
                    + Person::COL_NEXTDATE + " TEXT DEFAULT '',"
                    + Person::COL_D_LASTDATE + " INTEGER DEFAULT '',"
                    + Person::COL_LASTDATE + " TEXT DEFAULT '',"
                    + Person::COL_STATUS + " INTEGER DEFAULT '1'"
                    + ")";

Person::Person()
{
    this->id = -1;
    this->fio = "";
    this->dr = 0L;
    this->parents = "";
    this->m_addr = "";
    this->a_addr = "";
    this->d_dolten = 0L;
    this->dolten = "";
    this->d_nextdate = 0L;
    this->nextdate = "";
    this->d_lastdate = 0L;
    this->lastdate = "";
    this->status = 1;
}

Person::Person(QSqlQueryModel &model)
{
    this->id = model.record(0).value(COL_ID).toInt();
    this->fio = model.record(0).value(COL_FIO).toString();
    this->dr = model.record(0).value(COL_DR).toInt();
    this->parents = model.record(0).value(COL_PARENTS).toString();
    this->m_addr = model.record(0).value(COL_M_ADDR).toString();
    this->a_addr = model.record(0).value(COL_A_ADDR).toString();
    this->info = model.record(0).value(COL_INFO).toString();
    this->d_dolten = model.record(0).value(COL_D_DOLTEN).toInt();
    this->dolten = model.record(0).value(COL_DOLTEN).toString();
    this->d_nextdate = model.record(0).value(COL_D_NEXTDATE).toInt();
    this->nextdate = model.record(0).value(COL_NEXTDATE).toString();
    this->d_lastdate = model.record(0).value(COL_D_LASTDATE).toInt();
    this->lastdate = model.record(0).value(COL_LASTDATE).toString();
    this->status = model.record(0).value(COL_STATUS).toInt();
}

QSqlRecord Person::getContent(QSqlRecord origRecord) {
    QSqlRecord values = origRecord;
    // Note that ID is NOT included here
    values.setValue(COL_FIO, fio);
    values.setValue(COL_DR, (qlonglong)dr);
    values.setValue(COL_PARENTS, parents);
    values.setValue(COL_M_ADDR, m_addr);
    values.setValue(COL_A_ADDR, a_addr);
    values.setValue(COL_INFO, info);
    values.setValue(COL_D_DOLTEN, (qlonglong)d_dolten);
    values.setValue(COL_DOLTEN, dolten);
    values.setValue(COL_D_NEXTDATE, (qlonglong)d_nextdate);
    values.setValue(COL_NEXTDATE, nextdate);
    values.setValue(COL_D_LASTDATE, (qlonglong)d_lastdate);
    values.setValue(COL_LASTDATE, lastdate);
    values.setValue(COL_STATUS, status);

    return values;
    }

