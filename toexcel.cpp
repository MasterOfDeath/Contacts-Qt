#include "toexcel.h"

ToExcel::ToExcel(QSqlTableModel *model, QString filePath)
{
    int position = 3;
    QString status = "Актив";

    Document xlsx;
    xlsx.addSheet("Контакты");

    xlsx.setColumnWidth(1, 2); //Column A
    xlsx.setColumnWidth(2,5);
    xlsx.setColumnWidth(3,25);
    xlsx.setColumnWidth(4,25);
    xlsx.setColumnWidth(5,25);
    xlsx.setColumnWidth(6,25);
    xlsx.setColumnWidth(7,25);
    xlsx.setColumnWidth(8,25);
    xlsx.setColumnWidth(9,30);
    xlsx.setColumnWidth(10,20);
    xlsx.setColumnWidth(11,10);

    //Заголовок таблицы
    writeHeaderCell(xlsx, "B"+QString::number(position), "#", Format::AlignLeft);
    writeHeaderCell(xlsx, "C"+QString::number(position), STRINGS["labelFIO"], Format::AlignLeft);
    writeHeaderCell(xlsx, "D"+QString::number(position), STRINGS["labelParents"], Format::AlignLeft);
    writeHeaderCell(xlsx, "E"+QString::number(position), STRINGS["labelAddress2"], Format::AlignLeft);
    writeHeaderCell(xlsx, "F"+QString::number(position), STRINGS["labelInfo"], Format::AlignLeft);
    writeHeaderCell(xlsx, "G"+QString::number(position), STRINGS["labelDolTen"], Format::AlignLeft);
    writeHeaderCell(xlsx, "H"+QString::number(position), STRINGS["labelNextDate"], Format::AlignLeft);
    writeHeaderCell(xlsx, "I"+QString::number(position), STRINGS["labelLastDate"], Format::AlignLeft);
    writeHeaderCell(xlsx, "J"+QString::number(position), STRINGS["labelLastEdit"], Format::AlignLeft);
    writeHeaderCell(xlsx, "K"+QString::number(position), "Статус", Format::AlignLeft);

    position++;

    for (int i = 0; i < model->rowCount(); i++){

        if (model->data(model->index(i,12)).toInt() == 1){
            status = "Актив";
            writeActiveCell(xlsx, "B"+QString::number(i+position), QString::number(i+1), Format::AlignLeft);
            writeActiveCell(xlsx, "C"+QString::number(i+position), model->data(model->index(i,0)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "D"+QString::number(i+position), model->data(model->index(i,2)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "E"+QString::number(i+position), model->data(model->index(i,3)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "F"+QString::number(i+position), model->data(model->index(i,5)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "G"+QString::number(i+position), model->data(model->index(i,7)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "H"+QString::number(i+position), model->data(model->index(i,9)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "I"+QString::number(i+position), model->data(model->index(i,11)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "J"+QString::number(i+position), model->data(model->index(i,4)).toString(), Format::AlignLeft);
            writeActiveCell(xlsx, "K"+QString::number(i+position), status, Format::AlignLeft);
        }
        else {
            status = "Архив";
            writeArchiveCell(xlsx, "B"+QString::number(i+position), QString::number(i+1), Format::AlignLeft);
            writeArchiveCell(xlsx, "C"+QString::number(i+position), model->data(model->index(i,0)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "D"+QString::number(i+position), model->data(model->index(i,2)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "E"+QString::number(i+position), model->data(model->index(i,3)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "F"+QString::number(i+position), model->data(model->index(i,5)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "G"+QString::number(i+position), model->data(model->index(i,7)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "H"+QString::number(i+position), model->data(model->index(i,9)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "I"+QString::number(i+position), model->data(model->index(i,11)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "J"+QString::number(i+position), model->data(model->index(i,4)).toString(), Format::AlignLeft);
            writeArchiveCell(xlsx, "K"+QString::number(i+position), status, Format::AlignLeft);
        }

    }

    position = position + model->rowCount() + 2;


    writeResultCell(xlsx, "C"+QString::number(position), "Итого: "+QString::number(model->rowCount()), Format::AlignLeft);


    xlsx.saveAs(filePath);

}

void ToExcel::writeActiveCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align)
{
   Format format;
   format.setHorizontalAlignment(align);
   format.setVerticalAlignment(Format::AlignTop);
   format.setBorderStyle(Format::BorderThin);
   format.setTextWarp(true);//Перенос по словам
   xlsx.write(cell, text, format);
}

void ToExcel::writeArchiveCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align)
{
   Format format;
   format.setPatternBackgroundColor(QColor(203,203,203));
   format.setHorizontalAlignment(align);
   format.setVerticalAlignment(Format::AlignTop);
   format.setBorderStyle(Format::BorderThin);
   format.setTextWarp(true);//Перенос по словам
   xlsx.write(cell, text, format);
}

void ToExcel::writeHeaderCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align)
{
   Format format;
   format.setHorizontalAlignment(align);
   format.setVerticalAlignment(Format::AlignTop);
   format.setBorderStyle(Format::BorderThin);
   format.setFontBold(true);
   format.setTextWarp(true);//Перенос по словам
   xlsx.write(cell, text, format);
}


void ToExcel::writeResultCell(Document &xlsx, const QString &cell, const QString &text, Format::HorizontalAlignment align)
{
   Format format;
   format.setHorizontalAlignment(align);
   format.setVerticalAlignment(Format::AlignTop);
   format.setFontBold(true);
   format.setTextWarp(true);//Перенос по словам
   xlsx.write(cell, text, format);
}


