#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "common.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>

class SearchDialog : public QDialog
{
    Q_OBJECT
private:
    QPlainTextEdit *dlgSearch;

public:
    explicit SearchDialog(QWidget *parent = 0, QString curStatus = "");

signals:

public slots:
    void onOkClicked();
};

#endif // SEARCHDIALOG_H
