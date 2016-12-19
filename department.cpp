#include "department.h"
#include "ui_department.h"

department::department(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::department)
{
    ui->setupUi(this);
    ui->DepartNum->setEnabled(0);
    option = 0;

    mydatabase = new QSqlDatabase();
    l = new QSqlQuery() ;

    QString Q = "SELECT Department_number FROM Department ORDER BY Department_number ASC;";

    l->exec(Q);
    while (l->next())
    {
        int index = l->value(0).toInt();
        ui->DepartNum->addItem(QString::number(index));
    }

    QString Ql = "SELECT SSN FROM Employee ORDER BY SSN ASC;";
    l->exec(Ql);
    while (l->next())
    {
        int index = l->value(0).toInt();
        ui->Mgr_SSN->addItem(QString::number(index));
    }

}

department::~department()
{
    delete ui;
}

void department::on_InsertDep_clicked()
{
    option = 0;
    ui->Mgr_SSN->setEnabled(1);
    ui->DepName->setEnabled(1);
    ui->DepartNum->setEnabled(0);
}

void department::on_UpdateDep_clicked()
{
    option = 1;
    ui->Mgr_SSN->setEnabled(1);
    ui->DepName->setEnabled(1);
    ui->DepartNum->setEnabled(1);
}

void department::on_DeleteDep_clicked()
{
    option = 2;
    ui->Mgr_SSN->setEnabled(0);
    ui->DepName->setEnabled(0);
    ui->DepartNum->setEnabled(1);
}

void department::on_GoButton_clicked()
{
       QString name = ui->DepName->toPlainText();
       QString mgr_ssn = ui->Mgr_SSN->currentText();

       if(option == 0)
       {
           if(name != "")
           {
               QString qur = "INSERT INTO Department(Name,Mgr_SSN) VALUES('"+name+"','"+mgr_ssn+"')";
               l->exec(qur);
               ui->DepName->clear();
           }
           else
           {
               QMessageBox messageBox;
               messageBox.critical(0,"Error","You Must Fill in all of The Fields");
           }

       }
       else if(option == 1)
       {
            QString dep_num = ui->DepartNum->currentText();
            QString qur = "UPDATE Department SET ";
            if(name.size() != 0)
             {
                 qur+= "Name = '"+name+"' , ";
             }
            if(mgr_ssn.size() != 0)
             {
                 qur+= "Mgr_SSN = '"+mgr_ssn+"'";
             }
            qur+=  "WHERE Department_number = '"+dep_num+"'";

            l->exec(qur);
            ui->DepName->clear();
       }
       else if(option == 2)
       {
           QString dep_num = ui->DepartNum->currentText();
           QString qur = "DELETE FROM Department WHERE Department_number = '"+dep_num+"' ";
           l->exec(qur);
       }

       ui->DepartNum->clear();

       QString Q = "SELECT Department_number FROM Department ORDER BY Department_number ASC;";

       l->exec(Q);
       while (l->next())
       {
           int index = l->value(0).toInt();
           ui->DepartNum->addItem(QString::number(index));
       }
}

void department::on_Search_textChanged()
{
    QStandardItemModel *model = new QStandardItemModel(ui->DepartNum->count(),3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Mgr_SSN")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Dep_Number")));

    if(ui->SName->isChecked())
    {
        QString query = "SELECT Name,Mgr_SSN,Department_number FROM Department WHERE Name = '"+ui->Search->toPlainText()+"'";
        l->exec(query);
        model->setRowCount(l->size());

        int index=0;
        while(l->next())
        {
            QStandardItem *name = new QStandardItem(QString(l->value("Name").toString()));
            QStandardItem *mgrssn = new QStandardItem(QString(l->value("Mgr_SSN").toString()));
            QStandardItem *depnumber = new QStandardItem(QString(l->value("Department_number").toString()));
             model->setItem(index,0,name); //row,column,item
             model->setItem(index,1,mgrssn);
             model->setItem(index,2,depnumber);
             index++;
        }
    }

    else if(ui->SNumber->isChecked())
    {
        QString query = "SELECT Name,Mgr_SSN,Department_number FROM Department WHERE Department_number = '"+ui->Search->toPlainText()+"'";
        l->exec(query);
        model->setRowCount(l->size());
        int index=0;
        while(l->next())
        {
            QStandardItem *name = new QStandardItem(QString(l->value("Name").toString()));
            QStandardItem *mgrssn = new QStandardItem(QString(l->value("Mgr_SSN").toString()));
            QStandardItem *depnumber = new QStandardItem(QString(l->value("Department_number").toString()));
            model->setItem(index,0,name);
            model->setItem(index,1,mgrssn);
            model->setItem(index,2,depnumber);
             index++;
        }
    }

    else if(ui->SMgrssn->isChecked())
    {
        QString query = "SELECT Name,Mgr_SSN,Department_number FROM Department WHERE Mgr_SSN = '"+ui->Search->toPlainText()+"'";
        l->exec(query);
        model->setRowCount(l->size());

        int index =0;
        while(l->next())
        {
             QStandardItem *name = new QStandardItem(QString(l->value("Name").toString()));
             QStandardItem *mgrssn = new QStandardItem(QString(l->value("Mgr_SSN").toString()));
             QStandardItem *depnumber = new QStandardItem(QString(l->value("Department_number").toString()));
             model->setItem(index,0,name);
             model->setItem(index,1,mgrssn);
             model->setItem(index,2,depnumber);
             index++;
        }
    }

    ui->SearchTable->setModel(model);

}

void department::on_Return_clicked()
{
    MainWindow * w = new MainWindow();
    this->close();
    w->show();
}
