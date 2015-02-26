#ifndef COMMON_H
#define COMMON_H
#include <QMap>
#include <QString>

static QMap<QString, QString> myValues() {
    QMap<QString, QString>map;
    map.insert("appName", "Контакты");
    map.insert("labelFIO", "ФИО_др");
    map.insert("labelParents", "Родители");
    map.insert("labelAddress", "Основной\nадрес");
    map.insert("labelAddress2", "Основной адрес");
    map.insert("labelInfo", "Доп");
    map.insert("labelDolTen", "Долг_прогр");
    map.insert("labelNextDate", "След_визит");
    map.insert("labelLastDate", "Посл_визит");
    map.insert("labelLastEdit", "Редактировалось");
    map.insert("activeAction", "Активные");
    map.insert("allAction", "Все");
    map.insert("archiveAction", "Архивные");
    map.insert("searchAction", "Поиск контакта");
    map.insert("menuAction", "Меню");
    map.insert("saveAction", "Сохранить как ...");
    map.insert("importAction", "Загрузить базу");
    map.insert("exportAction", "Выгрузить базу");
    map.insert("newAction", "Создать новый контакт");
    map.insert("delAction", "Удалить контакт");
    map.insert("dlgAddTitle", "Новый контакт");
    map.insert("dlgAddVopr", "Добавить новый контакт?");
    map.insert("dlgDelTitle", "Удаление контакта");
    map.insert("dlgDelVopr", "Удалить контакт?");
    map.insert("chBoxStatusTextActive", "Контакт активен");
    map.insert("chBoxStatusTextDeactive", "Архивный контакт");
    map.insert("dlgStatusTitle", "Изменение статуса");
    map.insert("dlgStatusActive", "Сделать контакт активным?");
    map.insert("dlgStatusDeactive", "Сделать контакт архивным?");
    map.insert("dlgSearchTitle", "Поиск");
    map.insert("dlgTipActive", "Активных контактов");
    map.insert("dlgTipAll", "Во всех контактах");
    map.insert("dlgTipArchive", "Архивных контактов");
    map.insert("strbtnUpdate", "Обновить поле");
    map.insert("closeSearchAction", "Выйти из режима поиска");
    map.insert("dlgDragAsk", "Перенести встречу в Последние визты?");
    map.insert("ok", "Ок");
    map.insert("cancel", "Отмена");
    return map;
}

static const QMap<QString, QString> STRINGS = myValues();

static QString searchStr = "";

#endif // COMMON_H
