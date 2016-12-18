#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class department;
}

class department : public QWidget
{
    Q_OBJECT

public:
    explicit department(QWidget *parent = 0);
    ~department();
    QSqlDatabase * mydatabase;
    QSqlQuery * l;

private:
    Ui::department *ui;
};

#endif // DEPARTMENT_H
