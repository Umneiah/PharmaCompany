#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <mainwindow.h>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStandardItemModel>
#include <QStandardItem>

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

    int option;
    int option2;
    QString query2;

private slots:


    void on_InsertDep_clicked();

    void on_UpdateDep_clicked();

    void on_DeleteDep_clicked();

    void on_GoButton_clicked();

    void on_Search_textChanged();

    void on_Return_clicked();

    void on_SName_clicked();

    void on_SNumber_clicked();

    void on_SMgrssn_clicked();

private:
    Ui::department *ui;
};

#endif // DEPARTMENT_H
