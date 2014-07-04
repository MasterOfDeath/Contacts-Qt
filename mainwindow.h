#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasehandler.h"
#include "person.h"
#include "detaildelegate.h"
#include "customwidget.h"
#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QToolButton>
#include <QDataWidgetMapper>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    long id;
    DatabaseHandler d;

private:
    Ui::MainWindow *ui;
    QDataWidgetMapper *mapper;
    QSqlTableModel *model;
    void setTEHeight (QPlainTextEdit* edit, int nRows);
    void refreshUI();

private:
    QPlainTextEdit *teFIO;
    QLineEdit *teDR;
    QPlainTextEdit *teParents;
    QPlainTextEdit *teAddress;
    QPlainTextEdit *teInfo;
    QLineEdit *teDDolTen;
    QPlainTextEdit *teDolTen;
    QLineEdit *teDNextDate;
    QPlainTextEdit *teNextDate;
    QPlainTextEdit *teLastDate;

private slots:
  void addContactClicked();
  void delContactClicked();
  void listViewItemClicked(QModelIndex);
};


#endif // MAINWINDOW_H
