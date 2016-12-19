#ifndef BUYS_H
#define BUYS_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStandardItemModel>
#include <mainwindow.h>
namespace Ui {
class Buys;
}

class Buys : public QWidget
{
    Q_OBJECT

public:
    explicit Buys(QWidget *parent = 0);
    ~Buys();
    QSqlDatabase * mydatabase;
    QSqlQuery * l;

private slots:

    void on_Return_clicked();

private:
    Ui::Buys *ui;
};

#endif // BUYS_H
