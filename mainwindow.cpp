#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    d.openDB();

    model = new QSqlTableModel();
    model->setTable(Person::TABLE_NAME);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();


    //listView
    QListView *listView = new QListView();
    listView->setItemDelegate(new MyCustomListViewItemDelegate());
    listView->setModel(model);
    listView->setModelColumn(model->fieldIndex(Person::COL_FIO));
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
    QHBoxLayout * leftHalfPanel6 = new QHBoxLayout();
    leftHalfPanel->addLayout(leftHalfPanel6);

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
    teFIO = new QPlainTextEdit();
    //setTEHeight(teFIO,6);
    //teFIO->setMaximumBlockCount(5);
    leftHalfPanel1->addWidget(labelFIO);
    //leftHalfPanel1->setAlignment(labelFIO,Qt::AlignVCenter);
    leftHalfPanel1->addWidget(teFIO);
    //leftHalfPanel1->setAlignment(teFIO,Qt::AlignTop);

    //Дата рождения
    QLabel *labelDR = new QLabel("Дата\nрождения");
    teDR = new QLineEdit();
    teDR->setInputMask("00.00.0000");
    leftHalfPanel2->addWidget(labelDR);
    //leftHalfPanel2->setAlignment(labelDR,Qt::AlignVCenter);
    leftHalfPanel2->addWidget(teDR);
    //leftHalfPanel2->setAlignment(teDR,Qt::AlignTop);

    //Родители
    QLabel *labelParents = new QLabel("Родители");
    teParents = new QPlainTextEdit();
    leftHalfPanel3->addWidget(labelParents);
    //leftHalfPanel3->setAlignment(labelParents,Qt::AlignVCenter);
    leftHalfPanel3->addWidget(teParents);
    //leftHalfPanel3->setAlignment(teParents,Qt::AlignTop);

    //Адрес
    QLabel *labelAddress = new QLabel("Адрес");
    teAddress = new QPlainTextEdit();
    leftHalfPanel4->addWidget(labelAddress);
    //leftHalfPanel4->setAlignment(labelAddress,Qt::AlignVCenter);
    leftHalfPanel4->addWidget(teAddress);
    //leftHalfPanel4->setAlignment(teAddress,Qt::AlignTop);

    //Дополнительная информация
    QLabel *labelInfo = new QLabel("Дополнительная\nинформация");
    teInfo = new QPlainTextEdit();
    leftHalfPanel5->addWidget(labelInfo);
    //leftHalfPanel5->setAlignment(labelInfo,Qt::AlignVCenter);
    leftHalfPanel5->addWidget(teInfo);
    //leftHalfPanel5->setAlignment(teInfo,Qt::AlignTop);

    //CheckBox
    QCheckBox *cbActive = new QCheckBox("Архивный контакт");
    leftHalfPanel6->addWidget(cbActive);

    //Дата долг. тен.
    QLabel *labelDDolTen = new QLabel("Дата\nдолгосроч. тенд.");
    teDDolTen = new QLineEdit();
    teDDolTen->setInputMask("00.00.0000");
    rightHalfPanel1->addWidget(labelDDolTen);
    //rightHalfPanel1->setAlignment(labelDDolTen,Qt::AlignVCenter);
    rightHalfPanel1->addWidget(teDDolTen);
    //rightHalfPanel1->setAlignment(teDDolTen,Qt::AlignTop);

    //Долгосрочная тенденция
    QLabel *labelDolTen = new QLabel("Долгосрочная\nтенденция");
    teDolTen = new QPlainTextEdit();
    rightHalfPanel2->addWidget(labelDolTen);
    //rightHalfPanel2->setAlignment(labelDolTen,Qt::AlignVCenter);
    rightHalfPanel2->addWidget(teDolTen);
    //rightHalfPanel2->setAlignment(teDolTen,Qt::AlignTop);

    //Дата следующей встречи
    QLabel *labelDNextDate = new QLabel("Дата следующей\nвстречи");
    teDNextDate = new QLineEdit();
    teDNextDate->setInputMask("00.00.0000");
    rightHalfPanel3->addWidget(labelDNextDate);
    //rightHalfPanel3->setAlignment(labelDNextDate,Qt::AlignVCenter);
    rightHalfPanel3->addWidget(teDNextDate);
    //rightHalfPanel3->setAlignment(teDNextDate,Qt::AlignTop);

    //Следующий визит
    QLabel *labelNextDate = new QLabel("Следующий\nвизит");
    teNextDate = new QPlainTextEdit();
    rightHalfPanel4->addWidget(labelNextDate);
    //rightHalfPanel4->setAlignment(labelNextDate,Qt::AlignVCenter);
    rightHalfPanel4->addWidget(teNextDate);
    //rightHalfPanel4->setAlignment(teNextDate,Qt::AlignTop);

    //Последние визиты
    QLabel *labelLastDate = new QLabel("Последние\nвизиты");
    teLastDate = new QPlainTextEdit();
    rightHalfPanel5->addWidget(labelLastDate);
    //rightHalfPanel5->setAlignment(labelLastDate,Qt::AlignVCenter);
    rightHalfPanel5->addWidget(teLastDate);
    //rightHalfPanel5->setAlignment(teLastDate,Qt::AlignTop);




    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new DetailDelegate(this));
    mapper->addMapping(teFIO, model->fieldIndex(Person::COL_FIO));
    mapper->addMapping(teDR, model->fieldIndex(Person::COL_DR));
    mapper->addMapping(teParents, model->fieldIndex(Person::COL_PARENTS));
    mapper->addMapping(teAddress, model->fieldIndex(Person::COL_A_ADDR));
    mapper->addMapping(teInfo, model->fieldIndex(Person::COL_INFO));
    mapper->addMapping(cbActive, model->fieldIndex(Person::COL_STATUS));
    mapper->addMapping(teDDolTen, model->fieldIndex(Person::COL_D_DOLTEN));
    mapper->addMapping(teDolTen, model->fieldIndex(Person::COL_DOLTEN));
    mapper->addMapping(teDNextDate, model->fieldIndex(Person::COL_D_NEXTDATE));
    mapper->addMapping(teNextDate, model->fieldIndex(Person::COL_NEXTDATE));
    mapper->addMapping(teLastDate, model->fieldIndex(Person::COL_LASTDATE));
    mapper->toFirst();

    //При смене item в listView меняется позиция в mapper
    connect(listView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
              mapper, SLOT(setCurrentModelIndex(QModelIndex)));


    //ToolBar
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->mainToolBar->addWidget(empty);
    ui->mainToolBar->addAction(QPixmap(":icons/ic_add"), "Создать новый контакт", this, SLOT(addContactClicked()));
    QAction *activeAction = new QAction(QPixmap(":icons/ic_mode_active"),"Активные", this);
    ui->mainToolBar->addAction(activeAction);
    QToolButton *activeButton = dynamic_cast<QToolButton*>(ui->mainToolBar->widgetForAction(activeAction));
    activeButton->setPopupMode(QToolButton::InstantPopup);
    activeButton->addAction(new QAction(QPixmap(":icons/ic_mode_all"), "Все", this));
    activeButton->addAction(new QAction(QPixmap(":icons/ic_mode_deactive"), "Архивные", this));
    ui->mainToolBar->addAction(QPixmap(":icons/ic_search"), "Поиск контакта", this, SLOT(slotNoImpl()));

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

void MainWindow::addContactClicked()
{
    Person p = Person();
    d.putPerson(p);

    model->select();

    mapper->toLast();
}

//void MainWindow::refreshUI()
//{
//    QSqlQueryModel *oneModel = d.queryOneRow(id);

//    teFIO->setPlainText(oneModel->record(0).value(Person::COL_FIO).toString());
//    teDR->setText(oneModel->record(0).value(Person::COL_DR).toString());
//    teParents->setPlainText(oneModel->record(0).value(Person::COL_PARENTS).toString());
//    teAddress->setPlainText(oneModel->record(0).value(Person::COL_M_ADDR).toString());
//    teInfo->setPlainText(oneModel->record(0).value(Person::COL_INFO).toString());
//    teDDolTen->setText(oneModel->record(0).value(Person::COL_D_DOLTEN).toString());
//    teDolTen->setPlainText(oneModel->record(0).value(Person::COL_DOLTEN).toString());
//    teDNextDate->setText(oneModel->record(0).value(Person::COL_D_NEXTDATE).toString());
//    teNextDate->setPlainText(oneModel->record(0).value(Person::COL_NEXTDATE).toString());
//    teLastDate->setPlainText(oneModel->record(0).value(Person::COL_LASTDATE).toString());

//    delete(oneModel);
//}

//void MainWindow::listViewItemClicked(QModelIndex index )
//{
//    //id = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt();
//    //refreshUI();
//    mapper->setCurrentIndex(index.row());

//    //qDebug() <<"id=";
//}
