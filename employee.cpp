#include "employee.h"
#include "ui_employee.h"

employee::employee(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employee)
{
    ui->setupUi(this);
    insert = 0;
    fullT = true;
    ui->SSN->setEnabled(false);
    ui->comboBox->addItem("Full Time");
    ui->comboBox->addItem("Part Time");
    eng = true;
    mydatabase = new QSqlDatabase();
    l = new QSqlQuery();
    UpdateComboBoxes();
}

employee::~employee()
{
    delete ui;
}

void employee::on_radioButton_clicked()
{
    insert = 0;
    ui->SSN->setEnabled(false);
    ui->Address->setEnabled(1);
    ui->Name->setEnabled(1);
    ui->PhoneNum->setEnabled(1);
    ui->Salary->setEnabled(1);
    ui->DepartNum->setEnabled(1);
    ui->comboBox->setEnabled(1);
    ui->groupBox_3->setEnabled(1);
    ui->JobType->setEnabled(1);

}

void employee::on_UpdateRB_clicked()
{
    UpdateComboBoxes();
    ui->SSN->setEnabled(true);
    ui->Address->setEnabled(1);
    ui->Name->setEnabled(1);
    ui->PhoneNum->setEnabled(1);
    ui->Salary->setEnabled(1);
    ui->DepartNum->setEnabled(1);
    ui->comboBox->setEnabled(1);
    ui->groupBox_3->setEnabled(1);
    ui->JobType->setEnabled(1);

    insert = 1;
}

void employee::on_Perform_clicked()
{
    QString add = ui->Address->toPlainText();
    QString name = ui->Name->toPlainText();
    QString pho = ui->PhoneNum->toPlainText();
    QString salary = ui->Salary->toPlainText();
    QString DepName = ui->DepartNum->currentText();
    QString extra = ui->JobType->toPlainText();
    QString SSSn = ui->SSN->currentText();
    QString query3 = "select Department_number from Department WHERE Name='"+DepName+"';";
    l->exec(query3);
    l->next();
    QString DepNum = l->value(0).toString();
    QString type = ui->comboBox->currentText();
    ui->Address->clear();
    ui->Name->clear();
    ui->PhoneNum->clear();
    ui->Salary->clear();
    ui->JobType->clear();
    if(insert == 0)
    {
        QString qur = "INSERT INTO Employee(Address,Name,Phone,Salary,Job_Type,Dep_number) VALUES('"+add+"','"+name+"','"+pho+"','"+salary+"','"+type+"','"+DepNum+"')";
        l->exec(qur);
        l->exec("select SSN from employee WHERE Address='"+add+"' AND Name='"+name+"' AND Phone='"+pho+"' AND Salary='"+salary+"' AND Job_Type='"+type+"' AND Dep_number ='"+DepNum+"';");
        l->next();
        QString ssn = l->value(0).toString();
        QString qur4;
        if(eng)
        {
            qur4 = "INSERT INTO Engineer(ESSN,Eng_Type) VALUES('"+ssn+"','"+extra+"')";
        }
        else
        {
            qur4 = "INSERT INTO Physician(PSSN,Specialized_in) VALUES('"+ssn+"','"+extra+"')";
        }
        l->exec(qur4);
    }
    else if(insert == 1)
    {
        QString qur6 = "UPDATE Employee SET ";
        if(add.size() != 0)
        {
            qur6+="Address='"+add+"',";
        }
        if(name.size() != 0)
        {
            qur6+="Name='"+name+"',";
        }
        if(pho.size() != 0)
        {
            qur6+="Phone='"+pho+"',";
        }
        if(salary.size() != 0)
        {
            qur6+="Salary='"+salary+"',";
        }
        if(DepNum.size() != 0)
        {
            qur6+="Dep_number='"+DepNum+"',";
        }
        if(type.size() != 0)
        {
            qur6+="Job_Type='"+type+"',";
        }
        qur6 = qur6.left(qur6.length()-1);
        qur6+="WHERE SSN='"+SSSn+"'";
        l->exec(qur6);
        if(extra.size() != 0)
        {
            if(eng) l->exec("UPDATE Engineer SET Eng_Type='"+extra+"' WHERE ESSN='"+SSSn+"'");
            else  l->exec("UPDATE Physician SET Specialized_in='"+extra+"' WHERE PSSN='"+SSSn+"'");
        }
    }
    else if(insert == 2)
    {
        QString qur5 = "DELETE FROM Employee WHERE SSN='"+SSSn+"'";
        l->exec(qur5);
    }
    UpdateComboBoxes();
}

void employee::on_DeleteRB_clicked()
{
    UpdateComboBoxes();
    insert = 2;
    ui->Address->setEnabled(0);
    ui->Name->setEnabled(0);
    ui->PhoneNum->setEnabled(0);
    ui->Salary->setEnabled(0);
    ui->DepartNum->setEnabled(0);
    ui->comboBox->setEnabled(0);
    ui->groupBox_3->setEnabled(0);
    ui->JobType->setEnabled(0);
    ui->SSN->setEnabled(1);


}

void employee::on_radioButton_pressed()
{
    UpdateComboBoxes();
}

void employee::on_EngRB_clicked()
{
    eng = true;
    ui->JobType->setPlaceholderText(" Engineering Type");
}

void employee::on_PhyRB_clicked()
{
    eng = false;
    ui->JobType->setPlaceholderText("    Specialized in");
}

void employee::UpdateComboBoxes()
{
    ui->SSN->clear();
    ui->DepartNum->clear();
    QString query1 = "select SSN from Employee;";
    l->exec(query1);
    while(l->next())
    {
        int item = l->value(0).toInt();
        ui->SSN->addItem(QString::number(item));
    }
    QString query = "select Name from Department;";
    l->exec(query);
    while(l->next())
    {
        QString item = l->value(0).toString();
        ui->DepartNum->addItem(item);
    }
}

void employee::on_Back_clicked()
{
    MainWindow * w = new MainWindow();
    w->show();
    this->close();
}
