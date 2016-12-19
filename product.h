#ifndef PRODUCT_H
#define PRODUCT_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStandardItemModel>
#include <mainwindow.h>
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
    bool Equipment ;
    bool insert;
    bool dele;

private slots:
    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_clicked();

    void on_UpdateRB_clicked();

    void on_Perform_clicked();

    void on_radioButton_4_clicked();

    void on_textEdit_textChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::product *ui;
};

#endif // PRODUCT_H
