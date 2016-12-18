#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <mainwindow.h>

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
    int insert;
    bool fullT;
    bool eng;

private slots:
    void on_radioButton_clicked();

    void on_UpdateRB_clicked();

    void on_Perform_clicked();

    void on_DeleteRB_clicked();

    void on_radioButton_pressed();

    void on_EngRB_clicked();

    void on_PhyRB_clicked();

    void on_Back_clicked();

private:
    void UpdateComboBoxes();
    Ui::employee *ui;
};

#endif // EMPLOYEE_H
