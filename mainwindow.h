#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSettings>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QToolButton>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include "databasehandler.h"
#include "person.h"
#include "detaildelegate.h"
#include "common.h"
#include "searchdialog.h"
#include "toexcel.h"


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
    int position;
    int prevPos;
    DatabaseHandler d;
    QString filter;
    QString curStatus;
    //QDialog *searchDialog;
    static void setSearchStr(QString str);
    static QString getSearchStr();

private:
    Ui::MainWindow *ui;
    QDataWidgetMapper *mapper;
    QSqlTableModel *model;
    QLabel *labelCounter;
    QToolButton *activeButton;
    QAction *activeAction;
    QAction *searchAction;
    QAction *newAction;
    QAction *delAction;
    QAction *closeSearchAction;
    Person person;
    Person updatePersonFromUI();
    bool isDiffPerson(Person item1, Person item2);
    int getCount();
    void closeEvent(QCloseEvent *event);
    void readSettings();
    void enableUI(bool show);
    void showAllExceptCancelSearch(bool show);
    void setIconActiveBtn(QString curStatus);
    void updateModel(QString curStatus);
    void saveDB();

private:
    QPlainTextEdit *teFIO;
    QPlainTextEdit *teParents;
    QPlainTextEdit *teAddress;
    QPlainTextEdit *teInfo;
    QCheckBox *cbActive;
    QPlainTextEdit *teDolTen;
    QPlainTextEdit *teNextDate;
    QPushButton *btnUpdate;
    QPlainTextEdit *teLastDate;

private slots:
  void addContactClicked();
  void delContactClicked();
  void searchClicked();
  void closeSearchClicked();
  void leftContactClicked();
  void rightContactClicked();
  void onRowChanged(int);
  void showOnlyActive();
  void showOnlyAll();
  void showOnlyArchive();
  void cbActiveStateChanged(int);
  void cbActiveStateClicked();
  void btnUpdateClicked();
  void btnSaveClicked();
  void btnImportClicked();
  void btnExportClicked();
};


#endif // MAINWINDOW_H
