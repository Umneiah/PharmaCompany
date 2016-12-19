#include "client.h"
#include "ui_client.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QVector>
#include <QTableView>
#include <QtSql>

client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    action = 0 ;
    search = 0 ;
    ui->client_id->setEnabled(false);
    type = 0;
    mydatabase = new QSqlDatabase() ;
    l = new QSqlQuery() ;
    combobox();
}

client::~client()
{
    delete ui;
}

void client::combobox()
{
    QString query = "SELECT ID FROM Client;";
    l->exec(query);
    while(l->next())
    {
       int id = l->value(0).toInt();
       ui->client_id->addItem(QString::number(id));
    }
}
QString client::get_id()
{
    QString query = "SELECT ID FROM Client;";
    l->exec(query);
    int id ;
    while(l->next())
    {
       id = l->value(0).toInt();
    }
    QString q_id = QString::number(id);
    return q_id ;
}

void client::on_insertRB_clicked()
{
    action = 0 ;
    ui->client_id->setEnabled(false);
    ui->client_name->setEnabled(1);
    ui->client_phone->setEnabled(1);
    ui->client_address->setEnabled(1);
    ui->selectTypeText->setEnabled(1);
    ui->client_name->setText("");
    ui->client_phone->setText("");
    ui->client_address->setText("");
    ui->selectTypeText->setText("");
}
void client::on_updateRB_clicked()
{
    action = 1 ;
    ui->client_id->setEnabled(true);
    ui->client_name->setEnabled(1);
    ui->client_phone->setEnabled(1);
    ui->client_address->setEnabled(1);
    ui->selectTypeText->setEnabled(1);
    ui->client_name->setText("");
    ui->client_phone->setText("");
    ui->client_address->setText("");
    ui->selectTypeText->setText("");
}
void client::on_deleteRB_clicked()
{
    action = 2 ;
    ui->client_id->setEnabled(true);
    ui->client_name->setEnabled(0);
    ui->client_phone->setEnabled(0);
    ui->client_address->setEnabled(0);
    ui->selectTypeText->setEnabled(0);
    ui->client_name->setText("");
    ui->client_phone->setText("");
    ui->client_address->setText("");
    ui->selectTypeText->setText("");

}

void client::on_go_clicked()
{
    QString name = ui->client_name->toPlainText();
    QString phone = ui->client_phone->toPlainText();
    QString address = ui->client_address->toPlainText();
    QString type_colomn = ui->selectTypeText->toPlainText();
    if(action == 0)
    {
        if(name!="" && phone!="" && address!="" && type_colomn!="")
        {
            QString query ;
            query = "INSERT INTO Client(Name,Phone,Address) VALUES('"+name+"','"+phone+"','"+address+"')";
            l->exec(query);
            if(type == 0)
            {
                query = "INSERT INTO Clinic(C_ID,Doctor_Name) VALUES('" +get_id()+ "','" +type_colomn+ "')";
                l->exec(query);
            }
            else if(type == 1)
            {
                query = "INSERT INTO Pharmacy(PID,Branch_Number) VALUES('"+get_id()+"','"+type_colomn+"')";
                l->exec(query);
            }
            else if(type == 2)
            {
                query = "INSERT INTO Hospital(HID, Owner) VALUES('"+get_id()+"','"+type_colomn+"')";
                l->exec(query);
            }
            ui->client_name->clear();
            ui->client_phone->clear();
            ui->client_address->clear();
            ui->selectTypeText->clear();
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Missing Details!!");
            messageBox.setFixedSize(0,0);
        }
    }
    else if(action == 1)
    {
        QString id = ui->client_id->currentText();
        QString query ;
        if(name != "")
        {
            query = "UPDATE Client SET Name = '"+name+"' WHERE ID = '"+id+"'";
            l->exec(query);
        }
        if(phone != "" )
        {
            query = "UPDATE Client SET Phone = '"+phone+"' WHERE ID = '"+id+"'";
            l->exec(query);
        }
        if(address != "")
        {
            query = "UPDATE Client SET Address = '"+address+"' WHERE ID = '"+id+"'";
            l->exec(query);
        }
        if(type_colomn != "")
        {
            QString query2 = "SELECT * FROM Clinic WHERE C_ID = '" + id + "'" ;
            l->exec(query2);
            if(l->size() == 1)
            {
                query = "UPDATE Clinic SET  Doctor_Name = '"+type_colomn+"' WHERE C_ID = '"+id+"'";
                l->exec(query);
            }
            query2 = "SELECT * FROM Pharmacy WHERE PID = '" + id + "'" ;
            l->exec(query2);
            if(l->size() == 1)
            {
                query = "UPDATE Pharmacy SET  Branch_Number = '"+type_colomn+"' WHERE PID = '"+id+"'";
                l->exec(query);
            }
            query2 = "SELECT * FROM Hospital WHERE HID = '" + id + "'" ;
            l->exec(query2);
            if(l->size() == 1)
            {
                query = "UPDATE Pharmacy SET  Branch_Number = '"+type_colomn+"' WHERE HID = '"+id+"'";
                l->exec(query);
            }
        }
        ui->client_name->clear();
        ui->client_phone->clear();
        ui->client_address->clear();
        ui->selectTypeText->clear();
    }
    else if(action == 2)
    {
        QString id = ui->client_id->currentText();
        QString query = "DELETE FROM Client WHERE ID = " + id + ";" ;
        l->exec(query);
    }
    ui->client_id->clear();
    combobox();
}

void client::on_ClinicRB_clicked()
{
    type = 0 ;
    ui->selectTypeText->setPlaceholderText("Doctor Name");
}
void client::on_PharmacyRB_clicked()
{
    type = 1 ;
    ui->selectTypeText->setPlaceholderText("Branch Number");
}
void client::on_HospitalRB_clicked()
{
    type = 2 ;
    ui->selectTypeText->setPlaceholderText("Owner Name");
}

void client::on_Return_clicked()
{
    MainWindow * w = new MainWindow();
    w->show();
    this->close();
}

void client::on_nameRB_clicked()
{
        search = 0 ;
}
void client::on_phoneRB_clicked()
{
    search = 1 ;
}
void client::on_addressRB_clicked()
{
    search=2;
}
void client::on_doctor_name_RB_clicked()
{
    search = 3;
}
void client::on_bransh_num_RB_clicked()
{
    search = 4 ;
}
void client::on_hospital_owner_RB_clicked()
{
    search = 5 ;
}

void client::on_searchText_textChanged()
{
    model->clear();
    QString search_input = ui->searchText->toPlainText();
    QString query ;
    QVector<int> ids ;
    int rows ;
    if(search==0)
            {
                rows = 0 ;
                query = "SELECT * FROM Client WHERE Name='"+search_input+"'" ;
                l->exec(query);
                while(l->next())
                {
                    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
                    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
                    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Phone")));
                    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Address")));
                    model->setItem( rows , 0 , new QStandardItem(QString(l->value(0).toString())) );
                    model->setItem( rows , 1 , new QStandardItem(QString(l->value(2).toString())) );
                    model->setItem( rows , 2 , new QStandardItem(QString(l->value(3).toString())) );
                    model->setItem( rows , 3 , new QStandardItem(QString(l->value(1).toString())) );
                    ids.push_back(l->value(0).toInt());
                    rows++;
                }
                for(int i = 0 ; i<ids.size() ; i++)
                {
                    query = "SELECT * FROM Clinic WHERE C_ID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    if(l->size()>=1)
                    {
                        while(l->next())
                        {
                            model->setHorizontalHeaderItem(4, new QStandardItem(QString("ClientType")));
                            model->setItem( i ,4 , new QStandardItem(QString("DoctorName: " + l->value(1).toString())) );
                        }
                    }
                    query = "SELECT * FROM Pharmacy WHERE PID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    if(l->size()>=1)
                    {
                        while(l->next())
                        {
                            model->setHorizontalHeaderItem(4, new QStandardItem(QString("ClientType")));
                            model->setItem( i ,4 , new QStandardItem(QString("BranchNumber: " + l->value(1).toString())) );
                        }
                    }
                    query = "SELECT * FROM Hospital WHERE HID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    if(l->size()>=1)
                    {
                        while(l->next())
                        {
                            model->setHorizontalHeaderItem(4, new QStandardItem(QString("ClientType")));
                            model->setItem( i ,4 , new QStandardItem(QString("HospitalOwner: " + l->value(1).toString())) );
                        }
                    }
                }
            }
    else if(search==1)
            {
                rows = 0 ;
                query = "SELECT * FROM Client WHERE Phone='"+search_input+"'" ;
                l->exec(query);
                while(l->next())
                {
                    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
                    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
                    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Phone")));
                    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Address")));
                    model->setItem( rows , 0 , new QStandardItem(QString(l->value(0).toString())) );
                    model->setItem( rows , 1 , new QStandardItem(QString(l->value(2).toString())) );
                    model->setItem( rows , 2 , new QStandardItem(QString(l->value(3).toString())) );
                    model->setItem( rows , 3 , new QStandardItem(QString(l->value(1).toString())) );
                    ids.push_back(l->value(0).toInt());
                    rows++;
                }
                for(int i = 0 ; i<ids.size() ; i++)
                {
                    query = "SELECT * FROM Clinic WHERE C_ID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    while(l->next())
                    {
                        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Type")));
                        model->setItem( i ,4 , new QStandardItem(QString("DoctorName: " + l->value(1).toString())) );
                    }
                    query = "SELECT * FROM Pharmacy WHERE PID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    while(l->next())
                    {
                        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Type")));
                        model->setItem( i ,4 , new QStandardItem(QString("BranchNumber: " + l->value(1).toString())) );
                    }
                    query = "SELECT * FROM Hospital WHERE HID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    while(l->next())
                    {
                        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Type")));
                        model->setItem( i ,4 , new QStandardItem(QString("HospitalOwner: " + l->value(1).toString())) );
                    }
                }
            }
    else if(search==2)
            {
                rows=0;
                query = "SELECT * FROM Client WHERE Address='"+search_input+"'" ;
                l->exec(query);
                while(l->next())
                {
                    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
                    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
                    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Phone")));
                    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Address")));
                    model->setItem( rows , 0 , new QStandardItem(QString(l->value(0).toString())) );
                    model->setItem( rows , 1 , new QStandardItem(QString(l->value(2).toString())) );
                    model->setItem( rows , 2 , new QStandardItem(QString(l->value(3).toString())) );
                    model->setItem( rows , 3 , new QStandardItem(QString(l->value(1).toString())) );
                    ids.push_back(l->value(0).toInt());
                }
                for(int i = 0 ; i<ids.size() ; i++)
                {
                    query = "SELECT * FROM Clinic WHERE C_ID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    while(l->next())
                    {
                        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Doctor")));
                        model->setItem( i ,4 , new QStandardItem(QString(l->value(1).toString())) );
                    }
                    query = "SELECT * FROM Pharmacy WHERE PID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    while(l->next())
                    {
                        model->setHorizontalHeaderItem(4, new QStandardItem(QString("BranchNumber")));
                        model->setItem( i ,4 , new QStandardItem(QString(l->value(1).toString())) );
                    }
                    query = "SELECT * FROM Hospital WHERE HID='"+QString::number(ids[i])+"'" ;
                    l->exec(query);
                    while(l->next())
                    {
                        model->setHorizontalHeaderItem(4, new QStandardItem(QString("HospitalOwner")));
                        model->setItem( i ,4 , new QStandardItem(QString(l->value(1).toString())) );
                    }
                }

            }
    else if(search==3)
            {
                rows = 0 ;
                query = "SELECT * FROM Clinic WHERE Doctor_Name='" +search_input+"'";
                l->exec(query);
                while(l->next())
                {
                    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
                    model->setHorizontalHeaderItem(1, new QStandardItem(QString("DoctorName")));
                    model->setHorizontalHeaderItem(2, new QStandardItem(QString("ClientName")));
                    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Phone")));
                    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Address")));
                    model->setItem( rows , 0 , new QStandardItem(QString(l->value(0).toString())) );
                    model->setItem( rows , 1 , new QStandardItem(QString(l->value(1).toString())) );
                    ids.push_back(l->value(0).toInt());
                    rows++;
                }
                for(int i = 0 ; i<ids.size() ; i++)
                {
                    query = "SELECT * FROM Client WHERE ID='" +QString::number(ids[i])+"'";
                    l->exec(query);
                    while(l->next())
                    {
                        model->setItem( i , 2 , new QStandardItem(QString(l->value(2).toString())) );
                        model->setItem( i , 3 , new QStandardItem(QString(l->value(3).toString())) );
                        model->setItem( i , 4 , new QStandardItem(QString(l->value(1).toString())) );
                    }
                }
            }
    else if(search==4)
            {
                rows = 0 ;
                query = "SELECT * FROM Pharmacy WHERE Branch_Number='" +search_input+"'";
                l->exec(query);
                while(l->next())
                {
                    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
                    model->setHorizontalHeaderItem(1, new QStandardItem(QString("BranchNumber")));
                    model->setHorizontalHeaderItem(2, new QStandardItem(QString("ClientName")));
                    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Phone")));
                    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Address")));
                    model->setItem( rows , 0 , new QStandardItem(QString(l->value(0).toString())) );
                    model->setItem( rows , 1 , new QStandardItem(QString(l->value(1).toString())) );
                    ids.push_back(l->value(0).toInt());
                    rows++;
                }
                for(int i = 0 ; i<ids.size() ; i++)
                {
                    query = "SELECT * FROM Client WHERE ID='" +QString::number(ids[i])+"'";
                    l->exec(query);
                    while(l->next())
                    {
                        model->setItem( i , 2 , new QStandardItem(QString(l->value(2).toString())) );
                        model->setItem( i , 3 , new QStandardItem(QString(l->value(3).toString())) );
                        model->setItem( i , 4 , new QStandardItem(QString(l->value(1).toString())) );
                    }
                }
            }
    else if(search==5)
            {
                rows = 0 ;
                query = "SELECT * FROM Hospital WHERE Owner='" +search_input+"'";
                l->exec(query);
                while(l->next())
                {
                    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
                    model->setHorizontalHeaderItem(1, new QStandardItem(QString("HospitalOwner")));
                    model->setHorizontalHeaderItem(2, new QStandardItem(QString("ClientName")));
                    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Phone")));
                    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Address")));
                    model->setItem( rows , 0 , new QStandardItem(QString(l->value(0).toString())) );
                    model->setItem( rows , 1 , new QStandardItem(QString(l->value(1).toString())) );
                    ids.push_back(l->value(0).toInt());
                    rows++;
                }
                for(int i = 0 ; i<ids.size() ; i++)
                {
                    query = "SELECT * FROM Client WHERE ID='" +QString::number(ids[i])+"'";
                    l->exec(query);
                    while(l->next())
                    {
                        model->setItem( i , 2 , new QStandardItem(QString(l->value(2).toString())) );
                        model->setItem( i , 3 , new QStandardItem(QString(l->value(3).toString())) );
                        model->setItem( i , 4 , new QStandardItem(QString(l->value(1).toString())) );
                    }
                }
            }
    ui->search_output->setModel(model);
}

void client::on_ShowAll_clicked()
{
    int rows = 0 ;
    QString query = "SELECT * FROM Client" ;
    QVector<int> ids ;
    l->exec(query);
    while(l->next())
    {
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Phone")));
        model->setHorizontalHeaderItem(3, new QStandardItem(QString("Address")));
        model->setItem( rows , 0 , new QStandardItem(QString(l->value(0).toString())) );
        model->setItem( rows , 1 , new QStandardItem(QString(l->value(2).toString())) );
        model->setItem( rows , 2 , new QStandardItem(QString(l->value(3).toString())) );
        model->setItem( rows , 3 , new QStandardItem(QString(l->value(1).toString())) );
        ids.push_back(l->value(0).toInt());
        rows++;
    }
    for(int i = 0 ; i<ids.size() ; i++)
    {
        query = "SELECT * FROM Clinic WHERE C_ID='"+QString::number(ids[i])+"'" ;
        l->exec(query);
        while(l->next())
        {
            model->setHorizontalHeaderItem(4, new QStandardItem(QString("Type")));
            model->setItem( i ,4 , new QStandardItem(QString("DoctorName: " + l->value(1).toString())) );
        }
        query = "SELECT * FROM Pharmacy WHERE PID='"+QString::number(ids[i])+"'" ;
        l->exec(query);
        while(l->next())
        {
            model->setHorizontalHeaderItem(4, new QStandardItem(QString("Type")));
            model->setItem( i ,4 , new QStandardItem(QString("BranchNumber: " + l->value(1).toString())) );
        }
        query = "SELECT * FROM Hospital WHERE HID='"+QString::number(ids[i])+"'" ;
        l->exec(query);
        while(l->next())
        {
            model->setHorizontalHeaderItem(4, new QStandardItem(QString("Type")));
            model->setItem( i ,4 , new QStandardItem(QString("HospitalOwner: " + l->value(1).toString())) );
        }
    }
    ui->search_output->setModel(model);
}
