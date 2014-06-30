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

    if(index.column() == 2 || index.column() == 7 || index.column() == 9) {
        ok = false;
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(lineEdit);
        QDateTime timestamp;
        timestamp.setMSecsSinceEpoch(index.data().toDouble());
        if (timestamp.toTime_t() > 1000)
            lineEdit->setText(timestamp.toString("dd.MM.yyyy"));
        else
            lineEdit->setText("");
    }

    if (ok) {
        QItemDelegate::setEditorData(editor, index);
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

    if(index.column() == 2 || index.column() == 7 || index.column() == 9) {
        ok = false;
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(lineEdit);
        QDateTime timestamp;
        timestamp.setDate(QDate::fromString(lineEdit->text(), "dd.MM.yyyy"));
        model->setData(index,timestamp.toMSecsSinceEpoch());
    }

    if (ok) {
        QItemDelegate::setModelData(editor, model, index);
    }
}
