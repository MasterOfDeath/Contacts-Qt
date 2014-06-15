#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasehandler.h"
#include "person.h"
#include "customwidget.h"
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

private:
    Ui::MainWindow *ui;
    void setTEHeight (QPlainTextEdit* edit, int nRows);
};

#endif // MAINWINDOW_H
