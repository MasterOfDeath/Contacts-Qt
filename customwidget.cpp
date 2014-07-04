#include "customwidget.h"

const static QColor colors[] = { QColor(244,225,240), //Архивные
                                 QColor(Qt::white) }; //Активные

const static QColor colorsSel[] = { QColor(244,114,114), //Выделенный
                                    QColor(168,241,240) }; //Выделенный и архивный

/*
  \class MyCustomListViewItem
*/
MyCustomListViewItem::MyCustomListViewItem(QWidget * parent, Qt::WindowFlags f)
  :QWidget(parent, f)
{
    _ui.setupUi(this);
    //Пересчитываем высоту пункта
    int height = _ui.firstLine->height()+_ui.line->height()+_ui.secLine->height();
    setGeometry(0,0,401,height);
}

MyCustomListViewItem::~MyCustomListViewItem()
{
}

/*
  \class MyCustomListViewItemDelegate
*/
MyCustomListViewItemDelegate::MyCustomListViewItemDelegate(QObject * parent)
  : QItemDelegate(parent)
    ,_itemWidget(new MyCustomListViewItem())
{
}

MyCustomListViewItemDelegate::~MyCustomListViewItemDelegate()
{
  if (_itemWidget)
  {
    delete _itemWidget;
    _itemWidget = NULL;
  }
}

void MyCustomListViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  _itemWidget->resize(option.rect.size());

  // Update data of widget here.
  const QString s = index.model()->data(index).toString();
  const QString s2 = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toString();
  const int status = index.model()->data(index.model()->index(index.row(), 13), Qt::DisplayRole).toInt();

  _itemWidget->_ui.firstLine->setText(s);
  _itemWidget->_ui.secLine->setText(s2);

  // Change the background color of the widget if it is selected.
  QPalette pal;

  if ((option.state & QStyle::State_Selected) == QStyle::State_Selected) {
      pal.setBrush(QPalette::Window, QBrush(colorsSel[status]));
  }
  else {
      pal.setBrush(QPalette::Window, QBrush(colors[status]));
  }

  _itemWidget->_ui.widget->setPalette(pal);

  // Paint the widget now.
  painter->save();
  painter->translate(option.rect.topLeft());
  _itemWidget->render(painter);
  painter->restore();
}

QSize MyCustomListViewItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  const int width = _itemWidget->minimumWidth();
  const int height = _itemWidget->height();
  return QSize(width, height);
}

/*
  \class MyWidget

MyWidget::MyWidget(QWidget * parent, Qt::WindowFlags f)
  : QWidget(parent, f)
{
  QBoxLayout * l = new QBoxLayout(QBoxLayout::TopToBottom, this);
  l->setContentsMargins(0,0,0,0);

  listView = new QListView(this);
  listView->setItemDelegate(new MyCustomListViewItemDelegate());

  l->addWidget(listView);

  setLayout(l);
  //resize(450, 300);
}

MyWidget::~MyWidget()
{
}

void MyWidget::setModel(QSqlQueryModel *model)
{
    listView->setModel(model);
}

void MyWidget::setModelColumn(int column)
{
    listView->setModelColumn(column);
}
*/
