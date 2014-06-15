#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H
#include "databasehandler.h"
#include <QWidget>
#include <QBoxLayout>
#include <QListView>
#include <QtGui/QPainter>
#include <QItemDelegate>
#include "ui_customlistviewitem.h"

/*
  \class MyCustomListViewItem
*/
class MyCustomListViewItem : public QWidget
{
  Q_OBJECT
public:
  MyCustomListViewItem(QWidget * parent = 0, Qt::WindowFlags f = 0);
  ~MyCustomListViewItem();

public:
  Ui::CustomListViewItemWidgetForm _ui;
};

/*
  \class MyCustomListViewItem
*/
class MyCustomListViewItemDelegate : public QItemDelegate
{
public:
  MyCustomListViewItemDelegate(QObject * parent = 0);
  ~MyCustomListViewItemDelegate();
  virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
  virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

protected:
  MyCustomListViewItem * _itemWidget;
};

/*
  \class MyCustomListViewItem

class MyWidget : public QWidget
{
  Q_OBJECT
private:
    QListView * listView;
public:
    MyWidget(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~MyWidget();
    void setModel(QSqlQueryModel *model);
    void setModelColumn(int column);
};
*/

#endif // CUSTOMWIDGET_H
