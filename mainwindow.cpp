#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DatabaseHandler d;
    d.openDB();
    QSqlQueryModel *model = d.queryAllData();

    //listView
    QListView *listView = new QListView();
    listView->setItemDelegate(new MyCustomListViewItemDelegate());
    listView->setModel(model);
    listView->setModelColumn(1);
    listView->setMaximumWidth(300);
    listView->setMinimumWidth(200);
    ui->centralWidget->layout()->addWidget(listView);

    //Лейаут для правой панели экрана
    QHBoxLayout * rightPanel = new QHBoxLayout();
    QWidget *widgetRightPanel = new QWidget();
    widgetRightPanel->setLayout(rightPanel);
    ui->centralWidget->layout()->addWidget(widgetRightPanel);

    //Правая и левая половина правой панели
    QVBoxLayout * leftHalfPanel = new QVBoxLayout();
    rightPanel->addLayout(leftHalfPanel);
    QVBoxLayout * rightHalfPanel = new QVBoxLayout();
    rightPanel->addLayout(rightHalfPanel);

    //Лейауты левой половины
    QHBoxLayout * leftHalfPanel1 = new QHBoxLayout();
    leftHalfPanel->addLayout(leftHalfPanel1);
    QHBoxLayout * leftHalfPanel2 = new QHBoxLayout();
    leftHalfPanel->addLayout(leftHalfPanel2);
    QHBoxLayout * leftHalfPanel3 = new QHBoxLayout();
    leftHalfPanel->addLayout(leftHalfPanel3);
    QHBoxLayout * leftHalfPanel4 = new QHBoxLayout();
    leftHalfPanel->addLayout(leftHalfPanel4);
    QHBoxLayout * leftHalfPanel5 = new QHBoxLayout();
    leftHalfPanel->addLayout(leftHalfPanel5);

    //Лейауты правой половины
    QHBoxLayout * rightHalfPanel1 = new QHBoxLayout();
    rightHalfPanel->addLayout(rightHalfPanel1);
    QHBoxLayout * rightHalfPanel2 = new QHBoxLayout();
    rightHalfPanel->addLayout(rightHalfPanel2);
    QHBoxLayout * rightHalfPanel3 = new QHBoxLayout();
    rightHalfPanel->addLayout(rightHalfPanel3);
    QHBoxLayout * rightHalfPanel4 = new QHBoxLayout();
    rightHalfPanel->addLayout(rightHalfPanel4);
    QHBoxLayout * rightHalfPanel5 = new QHBoxLayout();
    rightHalfPanel->addLayout(rightHalfPanel5);

    //ФИО
    QLabel *labelFIO = new QLabel("ФИО");
    QPlainTextEdit *teFIO = new QPlainTextEdit();
    //setTEHeight(teFIO,6);
    //teFIO->setMaximumBlockCount(5);
    leftHalfPanel1->addWidget(labelFIO);
    //leftHalfPanel1->setAlignment(labelFIO,Qt::AlignVCenter);
    leftHalfPanel1->addWidget(teFIO);
    //leftHalfPanel1->setAlignment(teFIO,Qt::AlignTop);

    //Дата рождения
    QLabel *labelDR = new QLabel("Дата\nрождения");
    QLineEdit *teDR = new QLineEdit();
    leftHalfPanel2->addWidget(labelDR);
    //leftHalfPanel2->setAlignment(labelDR,Qt::AlignVCenter);
    leftHalfPanel2->addWidget(teDR);
    //leftHalfPanel2->setAlignment(teDR,Qt::AlignTop);

    //Родители
    QLabel *labelParents = new QLabel("Родители");
    QPlainTextEdit *teParents = new QPlainTextEdit();
    leftHalfPanel3->addWidget(labelParents);
    //leftHalfPanel3->setAlignment(labelParents,Qt::AlignVCenter);
    leftHalfPanel3->addWidget(teParents);
    //leftHalfPanel3->setAlignment(teParents,Qt::AlignTop);

    //Адрес
    QLabel *labelAddress = new QLabel("Адрес");
    QPlainTextEdit *teAddress = new QPlainTextEdit();
    leftHalfPanel4->addWidget(labelAddress);
    //leftHalfPanel4->setAlignment(labelAddress,Qt::AlignVCenter);
    leftHalfPanel4->addWidget(teAddress);
    //leftHalfPanel4->setAlignment(teAddress,Qt::AlignTop);

    //Дополнительная информация
    QLabel *labelInfo = new QLabel("Дополнительная\nинформация");
    QPlainTextEdit *teInfo = new QPlainTextEdit();
    leftHalfPanel5->addWidget(labelInfo);
    //leftHalfPanel5->setAlignment(labelInfo,Qt::AlignVCenter);
    leftHalfPanel5->addWidget(teInfo);
    //leftHalfPanel5->setAlignment(teInfo,Qt::AlignTop);

    //Дата долг. тен.
    QLabel *labelDDolTen = new QLabel("Дата\nдолгосроч. тенд.");
    QLineEdit *teDDolTen = new QLineEdit();
    rightHalfPanel1->addWidget(labelDDolTen);
    //rightHalfPanel1->setAlignment(labelDDolTen,Qt::AlignVCenter);
    rightHalfPanel1->addWidget(teDDolTen);
    //rightHalfPanel1->setAlignment(teDDolTen,Qt::AlignTop);

    //Долгосрочная тенденция
    QLabel *labelDolTen = new QLabel("Долгосрочная\nтенденция");
    QPlainTextEdit *teDolTen = new QPlainTextEdit();
    rightHalfPanel2->addWidget(labelDolTen);
    //rightHalfPanel2->setAlignment(labelDolTen,Qt::AlignVCenter);
    rightHalfPanel2->addWidget(teDolTen);
    //rightHalfPanel2->setAlignment(teDolTen,Qt::AlignTop);

    //Дата следующей встречи
    QLabel *labelDNextDate = new QLabel("Дата следующей\nвстречи");
    QLineEdit *teDNextDate = new QLineEdit();
    rightHalfPanel3->addWidget(labelDNextDate);
    //rightHalfPanel3->setAlignment(labelDNextDate,Qt::AlignVCenter);
    rightHalfPanel3->addWidget(teDNextDate);
    //rightHalfPanel3->setAlignment(teDNextDate,Qt::AlignTop);

    //Следующий визит
    QLabel *labelNextDate = new QLabel("Следующий\nвизит");
    QPlainTextEdit *teNextDate = new QPlainTextEdit();
    rightHalfPanel4->addWidget(labelNextDate);
    //rightHalfPanel4->setAlignment(labelNextDate,Qt::AlignVCenter);
    rightHalfPanel4->addWidget(teNextDate);
    //rightHalfPanel4->setAlignment(teNextDate,Qt::AlignTop);

    //Последние визиты
    QLabel *labelLastDate = new QLabel("Последние\nвизиты");
    QPlainTextEdit *teLastDate = new QPlainTextEdit();
    rightHalfPanel5->addWidget(labelLastDate);
    //rightHalfPanel5->setAlignment(labelLastDate,Qt::AlignVCenter);
    rightHalfPanel5->addWidget(teLastDate);
    //rightHalfPanel5->setAlignment(teLastDate,Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTEHeight (QPlainTextEdit* edit, int nRows)
  {
  QFontMetrics m (edit -> font()) ;
  int RowHeight = m.lineSpacing() ;
  edit -> setFixedHeight  (nRows * RowHeight) ;
  }
