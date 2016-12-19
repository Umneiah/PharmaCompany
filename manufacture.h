#ifndef MANUFACTURE_H
#define MANUFACTURE_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include<QStandardItemModel>

namespace Ui {
class Manufacture;
}

class Manufacture : public QWidget
{
    Q_OBJECT

public:
    explicit Manufacture(QWidget *parent = 0);
    ~Manufacture();
    QSqlDatabase * mydatabase;
    QSqlQuery *l;

private:
    Ui::Manufacture *ui;
};

#endif // MANUFACTURE_H
