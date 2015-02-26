#include "searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent, QString curStatus) :
    QDialog(parent)
{
    setWindowTitle(STRINGS["dlgSearchTitle"]);

    QPushButton *okButton = new QPushButton(STRINGS["ok"]);

    QPushButton *cancelButton = new QPushButton(STRINGS["cancel"]);

    QLabel *image = new QLabel();
    image->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    image->setPixmap(QPixmap(":icons/ic_mode_active_small"));
    QLabel *dlgTip = new QLabel(STRINGS["dlgTipActive"]);

    if (curStatus == ""){
        dlgTip->setText(STRINGS["dlgTipAll"]);
        image->setPixmap(QPixmap(":icons/ic_mode_all_small"));
    }

    if (curStatus == "0"){
        dlgTip->setText(STRINGS["dlgTipArchive"]);
        image->setPixmap(QPixmap(":icons/ic_mode_deactive_small"));
    }

    dlgSearch = new QPlainTextEdit();
    dlgSearch->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum);
    dlgSearch->setMaximumHeight(50);
    dlgSearch->setMinimumWidth(300);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(image);
    iconLayout->addWidget(dlgTip);
    QHBoxLayout *editLayout = new QHBoxLayout;
    editLayout->addWidget(dlgSearch);
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    //buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(iconLayout);
    mainLayout->addLayout(editLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(onOkClicked()));
}

void SearchDialog::onOkClicked(){
    MainWindow::setSearchStr(dlgSearch->toPlainText());
    accept();
}
