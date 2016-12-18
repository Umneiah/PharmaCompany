#ifndef PRODUCT_H
#define PRODUCT_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class product;
}

class product : public QWidget
{
    Q_OBJECT

public:
    explicit product(QWidget *parent = 0);
    ~product();
    QSqlDatabase * mydatabase;
    QSqlQuery * l;

private:
    Ui::product *ui;
};

#endif // PRODUCT_H
