#ifndef DETAILDELEGATE_H
#define DETAILDELEGATE_H

#include <QItemDelegate>
#include <QLineEdit>
#include <QDateTime>
#include <QCheckBox>
#include "mainwindow.h"

class DetailDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DetailDelegate(QObject *parent = 0);
    void setEditorData(QWidget *editor,
                    const QModelIndex &index) const;
    void setModelData(QWidget *editor,
                    QAbstractItemModel *model,
                    const QModelIndex &index) const;
};

#endif // DETAILDELEGATE_H
