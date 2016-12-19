#ifndef BUYS_H
#define BUYS_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStandardItemModel>
#include <mainwindow.h>
#include <QDateTime>
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

    void on_insert_clicked();

    void on_BuysSearch_textChanged();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

private:
    Ui::Buys *ui;
    int choice;
    void UpdateComboBoxes();
};

#endif // BUYS_H
