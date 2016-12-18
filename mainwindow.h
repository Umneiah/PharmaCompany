#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <department.h>
#include <client.h>
#include <employee.h>
#include <product.h>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int choice;
    QSqlDatabase * mydatabase;
    QSqlQuery * l;

private slots:
    void on_employeeRB_clicked();

    void on_DepartmentRB_clicked();

    void on_ClientsRB_clicked();

    void on_ProductsRB_clicked();

    void on_pushButton_clicked();

    void on_connect_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
