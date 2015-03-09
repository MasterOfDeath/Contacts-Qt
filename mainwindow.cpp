#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(STRINGS["appName"]);

    //Init
    curStatus = "1";
    filter = Person::COL_STATUS+" MATCH "+curStatus;
    position = 0;
    ///////////

    d.openDB();

    model = new QSqlTableModel();
    model->setTable(Person::TABLE_NAME);
    //model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    //Отображаем статус
    QSqlTableModel *modelSettings = new QSqlTableModel();
    modelSettings->setTable("settings");
    modelSettings->select();
    QLabel *labelStatus = new QLabel(this);
    labelStatus->setText("Выгружена: "+modelSettings->data(modelSettings->index(0,3)).toString());
    ui->statusBar->addPermanentWidget(labelStatus, 200);
    delete modelSettings;

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

    //ФИО
    QLabel *labelFIO = new QLabel(STRINGS["labelFIO"]);
    teFIO = new QPlainTextEdit();
    leftHalfPanel1->addWidget(labelFIO);
    leftHalfPanel1->addWidget(teFIO);

    //Родители
    QLabel *labelParents = new QLabel(STRINGS["labelParents"]);
    teParents = new QPlainTextEdit();
    leftHalfPanel2->addWidget(labelParents);
    leftHalfPanel2->addWidget(teParents);

    //Адрес
    QLabel *labelAddress = new QLabel(STRINGS["labelAddress"]);
    teAddress = new QPlainTextEdit();
    leftHalfPanel3->addWidget(labelAddress);
    leftHalfPanel3->addWidget(teAddress);

    //Дополнительная информация
    QLabel *labelInfo = new QLabel(STRINGS["labelInfo"]);
    teInfo = new QPlainTextEdit();
    leftHalfPanel4->addWidget(labelInfo);
    leftHalfPanel4->addWidget(teInfo);

    //CheckBox
    cbActive = new QCheckBox(STRINGS["chBoxStatusTextActive"]);
    leftHalfPanel5->addWidget(cbActive);

    //Долгосрочная тенденция
    QLabel *labelDolTen = new QLabel(STRINGS["labelDolTen"]);
    teDolTen = new QPlainTextEdit();
    teDolTen->setMaximumHeight(100);
    rightHalfPanel1->addWidget(labelDolTen);
    rightHalfPanel1->addWidget(teDolTen);

    //Следующий визит
    QLabel *labelNextDate = new QLabel(STRINGS["labelNextDate"]);
    teNextDate = new QPlainTextEdit();
    teNextDate->setMaximumHeight(100);
    rightHalfPanel2->addWidget(labelNextDate);
    rightHalfPanel2->addWidget(teNextDate);

    //Кнопка "Обновить поле"
    btnUpdate = new QPushButton(STRINGS["strbtnUpdate"]);
    btnUpdate->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    btnUpdate->setIcon(QPixmap(":icons/ic_btnupdate_dark"));
    rightHalfPanel3->addWidget(btnUpdate);

    //Последние визиты
    QLabel *labelLastDate = new QLabel(STRINGS["labelLastDate"]);
    labelLastDate->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    teLastDate = new QPlainTextEdit();
    teLastDate->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    rightHalfPanel4->addWidget(labelLastDate);
    rightHalfPanel4->addWidget(teLastDate);


    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new DetailDelegate(this));
    mapper->addMapping(teFIO, model->fieldIndex(Person::COL_FIO));
    mapper->addMapping(teParents, model->fieldIndex(Person::COL_PARENTS));
    mapper->addMapping(teAddress, model->fieldIndex(Person::COL_M_ADDR));
    mapper->addMapping(teInfo, model->fieldIndex(Person::COL_INFO));
    mapper->addMapping(cbActive, model->fieldIndex(Person::COL_STATUS));
    mapper->addMapping(teDolTen, model->fieldIndex(Person::COL_DOLTEN));
    mapper->addMapping(teNextDate, model->fieldIndex(Person::COL_NEXTDATE));
    mapper->addMapping(teLastDate, model->fieldIndex(Person::COL_LASTDATE));
    mapper->toFirst();


    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(onRowChanged(int)));


    //ToolBar
    //Пустой виджет
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->mainToolBar->addWidget(empty);

    //Навигация
    ui->mainToolBar->addAction(QPixmap(":icons/c_action_left"), "Влево", this, SLOT(leftContactClicked()));
    labelCounter = new QLabel(" 1 / 1 ");
    ui->mainToolBar->addWidget(labelCounter);
    ui->mainToolBar->addAction(QPixmap(":icons/c_action_right"), "Вправо", this, SLOT(rightContactClicked()));

    //Пустой виджет
    QWidget* empty2 = new QWidget();
    empty2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->mainToolBar->addWidget(empty2);

    //Режимы просмотра
    activeAction = new QAction(QPixmap(":icons/ic_mode_active"),STRINGS["activeAction"], this);
    ui->mainToolBar->addAction(activeAction);
    activeButton = dynamic_cast<QToolButton*>(ui->mainToolBar->widgetForAction(activeAction));
    activeButton->setPopupMode(QToolButton::InstantPopup);
    activeButton->addAction(new QAction(QPixmap(":icons/ic_mode_all"), STRINGS["allAction"], this));
    activeButton->addAction(new QAction(QPixmap(":icons/ic_mode_deactive"), STRINGS["archiveAction"], this));
    //Поиск
    searchAction = new QAction(QPixmap(":icons/ic_search"), STRINGS["searchAction"], this);
    //Новый контакт
    newAction = new QAction(QPixmap(":icons/ic_add"), STRINGS["newAction"], this);
    //Удалить
    delAction = new QAction(QPixmap(":icons/ic_del"), STRINGS["delAction"], this);
    //Закрытие поиска
    closeSearchAction = new QAction(QPixmap(":icons/ic_close_search"), STRINGS["closeSearchAction"], this);
    closeSearchAction->setVisible(false);
    ui->mainToolBar->addActions(QList<QAction*>() <<searchAction <<newAction
                                <<delAction <<closeSearchAction);
    QToolButton *closeSearchBtn = dynamic_cast<QToolButton*>(ui->mainToolBar->widgetForAction(closeSearchAction));
    closeSearchBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //Меню
    QToolButton *menuButton = new QToolButton();
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setIcon(QPixmap(":icons/ic_menu"));
    menuButton->setToolTip(STRINGS["menuAction"]);
    ui->mainToolBar->addWidget(menuButton);
    //Сохранить
    menuButton->addAction(new QAction(QPixmap(":icons/ic_save"), STRINGS["saveAction"], this));
    //Импорт-Экспорт
    menuButton->addAction(new QAction(QPixmap(":icons/ic_import"), STRINGS["importAction"], this));
    menuButton->addAction(new QAction(QPixmap(":icons/ic_export"), STRINGS["exportAction"], this));


    connect(activeButton->actions().at(0), SIGNAL(triggered()), this, SLOT(showOnlyActive()));
    connect(activeButton->actions().at(1), SIGNAL(triggered()), this, SLOT(showOnlyAll()));
    connect(activeButton->actions().at(2), SIGNAL(triggered()), this, SLOT(showOnlyArchive()));
    connect(delAction, SIGNAL(triggered()), this, SLOT(delContactClicked()));
    connect(newAction, SIGNAL(triggered()), this, SLOT(addContactClicked()));
    connect(searchAction, SIGNAL(triggered()), this, SLOT(searchClicked()));
    connect(closeSearchAction, SIGNAL(triggered()), this, SLOT(closeSearchClicked()));
    connect(menuButton->actions().at(0), SIGNAL(triggered()), this, SLOT(btnSaveClicked()));
    connect(menuButton->actions().at(1), SIGNAL(triggered()), this, SLOT(btnImportClicked()));
    connect(menuButton->actions().at(2), SIGNAL(triggered()), this, SLOT(btnExportClicked()));


    connect(cbActive,SIGNAL(stateChanged(int)),this,SLOT(cbActiveStateChanged(int)));
    connect(cbActive,SIGNAL(clicked()),this,SLOT(cbActiveStateClicked()));

    connect(btnUpdate,SIGNAL(clicked()),this,SLOT(btnUpdateClicked()));

    person = updatePersonFromUI(); //Заполняем переменную person

    showOnlyActive(); //Заставляем labelCounter отрисоваться

    readSettings(); //Восстанавливаем последние настройки, в том числе position и curStatus

    updateModel(curStatus); //Восстанавливем model в соответсвие со старыми настройками

    mapper->setCurrentIndex(position); //Восстанавливаем позицию.
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addContactClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, STRINGS["dlgAddTitle"], STRINGS["dlgAddVopr"],
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        saveDB();
        //Добавляем новую запись
        Person p = Person();
        d.putPerson(p);

        model->submitAll();
        model->select();
        while (model->canFetchMore())
                  model->fetchMore();
        mapper->toLast();

        enableUI(true);
        /////////////////
    }
}


void MainWindow::delContactClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, STRINGS["dlgDelTitle"], STRINGS["dlgDelVopr"],
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        //Удаляем запись
        model->removeRow(position);
        model->submitAll();
        model->select();
        mapper->setModel(model);

        if (getCount() == position){
            mapper->setCurrentIndex(position-1);
        }
        else {
            mapper->setCurrentIndex(position);
        }

        enableUI((getCount() != 0));
        /////////////////
    }
}


//Поиск
void MainWindow::searchClicked()
{
    SearchDialog *dialog = new SearchDialog(this,curStatus);
    if (dialog->exec() == QDialog::Accepted){
        if (searchStr != ""){
            saveDB();
            showAllExceptCancelSearch(false);
            prevPos = position;

            if (curStatus == ""){
                filter = Person::TABLE_NAME+" MATCH '"+searchStr+"*'";
            }
            else {
                filter = Person::TABLE_NAME+" MATCH '"+searchStr+"*' AND "+Person::COL_STATUS+" = "+curStatus;
            }

            model->submitAll();
            model->setFilter(filter);
            model->select();
            mapper->setModel(model);
            mapper->toFirst();

            enableUI((getCount() != 0));
        }
    }
    else {
        setSearchStr("");
    }

}


//Выход из поиска
void MainWindow::closeSearchClicked()
{
    setSearchStr("");

    showAllExceptCancelSearch(true);

    updateModel(curStatus);

    if (prevPos < getCount()){
        mapper->setCurrentIndex(prevPos);
    }
    else {
        mapper->setCurrentIndex(getCount()-1);
    }

}


//Вправо
void MainWindow::rightContactClicked()
{
    saveDB();
    mapper->toNext();
    person = updatePersonFromUI();
}


//Влево
void MainWindow::leftContactClicked()
{
    saveDB();
    mapper->toPrevious();
    person = updatePersonFromUI();
}


//Событие по смене текущей записи
void MainWindow::onRowChanged(int index){
    //labelCounter->setText(" "+QString::number(index+1)+" / "+QString::number(mapper->model()->rowCount())+" ");
    labelCounter->setText(" "+QString::number(index+1)+" / "+QString::number(getCount())+" ");
    position = index;

    enableUI(true);
}


//Показывать только активные записи
void MainWindow::showOnlyActive()
{
    curStatus = "1";

    updateModel(curStatus);

    mapper->toFirst();
    person = updatePersonFromUI();

    enableUI((getCount() != 0));
}


//Показывать все записи
void MainWindow::showOnlyAll()
{
    curStatus = "";

    updateModel(curStatus);

    mapper->toFirst();
    person = updatePersonFromUI();

    enableUI((getCount() != 0));
}


//Только архивные
void MainWindow::showOnlyArchive()
{
    curStatus = "0";

    updateModel(curStatus);

    mapper->toFirst();
    person = updatePersonFromUI();

    enableUI((getCount() != 0));
}


void MainWindow::updateModel(QString curStatus)
{
    saveDB();

    if (curStatus == ""){
        filter = "";
    }
    else {
        filter = Person::COL_STATUS + " MATCH "+curStatus;
    }

    setIconActiveBtn(curStatus);

    model->submitAll();
    model->setFilter(filter);
    model->select();
    mapper->setModel(model);
}


void MainWindow::cbActiveStateChanged(int state)
{
    if (state == Qt::Unchecked){
        cbActive->setText(STRINGS["chBoxStatusTextDeactive"]);
    }

    if (state == Qt::Checked){
        cbActive->setText(STRINGS["chBoxStatusTextActive"]);
    }
}


void MainWindow::cbActiveStateClicked()
{
    QString str = STRINGS["dlgStatusDeactive"];
    if (cbActive->isChecked()){
        str = STRINGS["dlgStatusActive"];
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, STRINGS["dlgStatusTitle"], str,
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        saveDB();
        model->submitAll();
        model->select();
        mapper->setModel(model);

        if (getCount() == position){
            mapper->setCurrentIndex(position-1);
        }
        else {
            mapper->setCurrentIndex(position);
        }

        enableUI((getCount() != 0));
    }

    if (reply == QMessageBox::No) {
        cbActive->setChecked(!cbActive->isChecked());
    }

}

//Закрытие приложения
void MainWindow::closeEvent(QCloseEvent *event)
{
    saveDB();

    QSettings settings("Contacts", "contacts");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);

    d.setLastPos(position,curStatus); //Ложим в БД position и curStatus

    model->submitAll();
}


//Восстанавливаем параметры окна
void MainWindow::readSettings()
{
    QSettings settings("Contacts", "contacts");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    d.getLastPos(position,curStatus); //Достаем из БД position и curStatus
}


int MainWindow::getCount(){
    while (model->canFetchMore())
              model->fetchMore();
    return model->rowCount();
}

void MainWindow::enableUI(bool show){
    teFIO->setEnabled(show);
    teParents->setEnabled(show);
    teAddress->setEnabled(show);
    teInfo->setEnabled(show);
    teDolTen->setEnabled(show);
    teNextDate->setEnabled(show);
    teLastDate->setEnabled(show);
    cbActive->setEnabled(show);
    btnUpdate->setEnabled(show);
    if(!show){
        labelCounter->setText(" 0 / 0 ");
    }
}

void MainWindow::showAllExceptCancelSearch(bool show){
    activeAction->setVisible(show);
    searchAction->setVisible(show);
    newAction->setVisible(show);
    delAction->setVisible(show);

    closeSearchAction->setVisible(!show);

    setIconActiveBtn(curStatus);
}

void MainWindow::btnUpdateClicked(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, STRINGS["strbtnUpdate"], STRINGS["dlgDragAsk"],
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (!teNextDate->toPlainText().isEmpty()) {
            QString div = (!teLastDate->toPlainText().isEmpty())
                    ? "\n--------\n" : "";

            model->setData(model->index(position,11),teLastDate->toPlainText().insert(0,teNextDate->toPlainText() + div));

            teNextDate->setPlainText("");
        }
    }
}

void MainWindow::setSearchStr(QString str){
    searchStr = str;
}

QString MainWindow::getSearchStr(){
    return searchStr;
}

void MainWindow::setIconActiveBtn(QString curStatus){
    if (curStatus == "1"){
        activeButton->setIcon(QPixmap(":icons/ic_mode_active"));
    }
    if (curStatus == "0"){
        activeButton->setIcon(QPixmap(":icons/ic_mode_deactive"));
    }
    if (curStatus == ""){
        activeButton->setIcon(QPixmap(":icons/ic_mode_all"));
    }
}

void MainWindow::btnSaveClicked(){

    QString filePath = QFileDialog::getSaveFileName(0, "Сохранить в файл", QDir::homePath()+"/Контакты.xlsx", "*.xlsx");
    if (!filePath.isEmpty()){
        if(!filePath.contains(".xlsx",Qt::CaseInsensitive)){
            filePath.append(".xlsx");
        }

        ToExcel *doc = new ToExcel(model,filePath);

        delete doc;
    }

}


void MainWindow::btnImportClicked(){
    QString filePath = QFileDialog::getOpenFileName(0, "Открыть файл",QDir::homePath(), "*.db");
    if (!filePath.isEmpty()){
        QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE",filePath);
        db2.setDatabaseName(filePath);
        db2.open();
        if (db2.isOpen()){
            db2.close();
            d.closeDB();
            QFile::remove("database/contacts.db");
            QFile::copy(filePath,"database/contacts.db");
            QMessageBox msgBox;
            msgBox.setText("Программа будет закрыта, откройте её снова самостоятельно.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Ok){
                QApplication::exit();
            }
        }
    }
}


void MainWindow::btnExportClicked(){
    QString filePath = QFileDialog::getSaveFileName(0,
                            "Сохранить файл",QDir::homePath()+"/contacts "+QDateTime::currentDateTime().toString("dd.MM.yyyy HH-mm")+".db", "*.db");
    if (!filePath.isEmpty()){
        saveDB();
        model->submitAll();
        mapper->setCurrentIndex(position);
        if (QFile(filePath).exists()){
            QFile::remove(filePath);
        }
        QFile::copy("database/contacts.db",filePath);
        QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE",filePath);
        db2.setDatabaseName(filePath);
        db2.open();
        if (db2.isOpen()){
            db2.exec("UPDATE settings SET import='"+QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm")+"' WHERE id=0");
            db2.removeDatabase(filePath);
            db2.close();
        }
    }
}


Person MainWindow::updatePersonFromUI(){
    Person item;
    item.fio = teFIO->toPlainText();
    item.parents = teParents->toPlainText();
    item.m_addr = teAddress->toPlainText();
    item.info = teInfo->toPlainText();
    item.dolten = teDolTen->toPlainText();
    item.nextdate = teNextDate->toPlainText();
    item.lastdate = teLastDate->toPlainText();
    if (cbActive->isChecked())
        item.status = 1;
    else
        item.status = 0;

    return item;
}

bool MainWindow::isDiffPerson(Person item1, Person item2){
    bool res = false;
    if (item1.fio != item2.fio) res =true;
    if (item1.parents != item2.parents) res =true;
    if (item1.m_addr != item2.m_addr) res =true;
    if (item1.info != item2.info) res =true;
    if (item1.dolten != item2.dolten) res =true;
    if (item1.nextdate != item2.nextdate) res =true;
    if (item1.lastdate != item2.lastdate) res =true;
    if (item1.status != item2.status) res =true;

    return res;
}

void MainWindow::saveDB(){
    if (isDiffPerson(person,updatePersonFromUI())){
        model->setData(model->index(position,4),QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
        mapper->submit();
    }
    person = updatePersonFromUI();
}


