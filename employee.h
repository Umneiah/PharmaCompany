#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class employee;
}

class employee : public QWidget
{
    Q_OBJECT

public:
    explicit employee(QWidget *parent = 0);
    ~employee();
    QSqlDatabase * mydatabase;
    QSqlQuery * l;
    bool insert;
    bool fullT;

private slots:
    void on_radioButton_clicked();

    void on_UpdateRB_clicked();

    void on_Perform_clicked();

private:
    Ui::employee *ui;
};

#endif // EMPLOYEE_H
