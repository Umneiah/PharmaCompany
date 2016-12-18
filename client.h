#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

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

private:
    Ui::client *ui;
};

#endif // CLIENT_H
