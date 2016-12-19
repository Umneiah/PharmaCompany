#ifndef CLIENT_H
#define CLIENT_H
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include<QStandardItemModel>

namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = 0);
    ~client();
    QSqlDatabase * mydatabase;
    QSqlQuery *l;
    int action;
    int type;
    int search ;
    QStandardItemModel* model ;

private slots:
    void combobox();
    QString get_id();
    void on_insertRB_clicked();
    void on_updateRB_clicked();
    void on_deleteRB_clicked();
    void on_go_clicked();
    void on_ClinicRB_clicked();
    void on_PharmacyRB_clicked();
    void on_HospitalRB_clicked();
    void on_Return_clicked();
    void on_nameRB_clicked();
    void on_phoneRB_clicked();
    void on_addressRB_clicked();
    void on_doctor_name_RB_clicked();
    void on_bransh_num_RB_clicked();
    void on_hospital_owner_RB_clicked();

    void on_searchText_textChanged();

private:
    Ui::client *ui;
};

#endif // CLIENT_H
