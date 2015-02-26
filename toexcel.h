#ifndef TOEXCEL_H
#define TOEXCEL_H

#include <QDebug>
#include <QSqlTableModel>
#include "common.h"
#include "xlsxdocument.h"
//#include "xlsxformat.h"
//#include "xlsxcellrange.h"
//#include "xlsxworksheet.h"

QTXLSX_USE_NAMESPACE

class ToExcel
{
public:
    ToExcel(QSqlTableModel *model, QString filePath);
    void writeActiveCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align);
    void writeArchiveCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align);
    void writeHeaderCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align);
    void writeResultCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align);
};

#endif // TOEXCEL_H
