#include "detaildelegate.h"

DetailDelegate::DetailDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void DetailDelegate::setEditorData(QWidget *editor,
                           const QModelIndex &index) const
    {
    bool ok = true;

    if (index.column() == 13) {
        ok = false;
        QCheckBox *chBox = qobject_cast<QCheckBox*>(editor);
        chBox->setChecked(index.data().toInt() == 0);
    }

//    if(index.column() == 2 || index.column() == 7 || index.column() == 9) {
//        ok = false;
//        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
//        Q_ASSERT(lineEdit);
//        QDateTime timestamp;
//        timestamp.setMSecsSinceEpoch(index.data().toDouble());
//        if (timestamp.toTime_t() > 1000)
//            lineEdit->setText(timestamp.toString("dd.MM.yyyy"));
//        else
//            lineEdit->setText("");
//    }

    if (ok) {
        QItemDelegate::setEditorData(editor, index);
    }

    //Если в режиме поиска, то подсвечиваем найденные слова
    if (MainWindow::getSearchStr() != ""){
        if(index.column() == 0 || index.column() == 2 || index.column() == 3 ||
                index.column() == 5 || index.column() == 7 || index.column() == 9 || index.column() == 11) {
            QPlainTextEdit *lineEdit = qobject_cast<QPlainTextEdit*>(editor);
            Q_ASSERT(lineEdit);

            QString search = MainWindow::getSearchStr();
            int start = lineEdit->toPlainText().indexOf(search,0,Qt::CaseInsensitive);

            if (start > -1){
                QList<QTextEdit::ExtraSelection>  selections;
                QTextEdit::ExtraSelection ex;
                ex.format.setBackground(QBrush(QColor(173,227,247)));
                ex.cursor = lineEdit->textCursor();
                ex.cursor.setPosition(start);
                ex.cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, search.length());
                selections.append(ex);
                lineEdit->setExtraSelections(selections);
            }
        }
    }

}

void DetailDelegate::setModelData(QWidget *editor,
                         QAbstractItemModel *model,
                         const QModelIndex &index) const
    {
    bool ok = true;

    if (index.column() == 13) {
        ok = false;
        QCheckBox *chBox = qobject_cast<QCheckBox*>(editor);
        if (chBox->isChecked())
            model->setData(index,0);
        else
            model->setData(index,1);
    }

//    if(index.column() == 2 || index.column() == 7 || index.column() == 9) {
//        ok = false;
//        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
//        Q_ASSERT(lineEdit);
//        QDateTime timestamp;
//        timestamp.setDate(QDate::fromString(lineEdit->text(), "dd.MM.yyyy"));
//        model->setData(index,timestamp.toMSecsSinceEpoch());
//    }

    if (ok) {
        QItemDelegate::setModelData(editor, model, index);
    }
}
