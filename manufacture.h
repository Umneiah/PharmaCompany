#ifndef MANUFACTURE_H
#define MANUFACTURE_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include<QStandardItemModel>
#include <mainwindow.h>
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

private slots:
    void on_insert_clicked();

    void on_Back_clicked();


    void on_search_textChanged();

private:
    Ui::Manufacture *ui;
};

#endif // MANUFACTURE_H
