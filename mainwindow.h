#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasehandler.h"
#include "person.h"
#include "customwidget.h"
#include "actionbar.h"
#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>


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
  void listViewItemClicked(QModelIndex index );
};


#endif // MAINWINDOW_H
