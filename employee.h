#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStandardItemModel>
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
    int SearchBool;
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

    void on_Search_textChanged();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_ShowAll_clicked();

private:
    void UpdateComboBoxes();
    Ui::employee *ui;
};

#endif // EMPLOYEE_H
