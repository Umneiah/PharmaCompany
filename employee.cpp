#include "employee.h"
#include "ui_employee.h"

employee::employee(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employee)
{
    ui->setupUi(this);
    insert = 0;
    SearchBool =0;
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

void employee::on_Search_textChanged()
{
    QString sear = ui->Search->toPlainText();
    QString qur;
    switch (SearchBool) {
    case 0:
        qur = "SELECT * FROM Employee WHERE SSN = '"+sear+"'";
        break;
    case 1:
        qur = "SELECT * FROM Employee WHERE Name = '"+sear+"'";
        break;
    case 2:
        qur = "SELECT * FROM Employee WHERE Phone = '"+sear+"'";
        break;
    case 3:
        qur = "SELECT * FROM Employee WHERE Salary = '"+sear+"'";
        break;
    case 4:
        qur = "SELECT * FROM Employee WHERE Job_Type = '"+sear+"'";
        break;
    case 5:
        qur = "SELECT * FROM Employee,Department WHERE Dep_number=Department_number AND Department.Name = '"+sear+"'";
        break;
    default:
        break;
    }
    l->exec(qur);
    QStandardItemModel *model = new QStandardItemModel(l->size(),7,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("SSN")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Address")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Phone")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Salary")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Job type")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Department no")));
    int index = 0;
    while(l->next())
    {
        QStandardItem *ssn = new QStandardItem(QString(l->value("SSN").toString()));
        QStandardItem *name = new QStandardItem(QString(l->value("Name").toString()));
        QStandardItem *add = new QStandardItem(QString(l->value("Address").toString()));
        QStandardItem *pho = new QStandardItem(QString(l->value("Phone").toString()));
        QStandardItem *sala = new QStandardItem(QString(l->value("Salary").toString()));
        QStandardItem *type = new QStandardItem(QString(l->value("Job_Type").toString()));
        QStandardItem *Depno = new QStandardItem(QString(l->value("Dep_number").toString()));
        model->setItem(index,0,ssn);
        model->setItem(index,1,name);
        model->setItem(index,2,add);
        model->setItem(index,3,pho);
        model->setItem(index,4,sala);
        model->setItem(index,5,type);
        model->setItem(index,6,Depno);
        index++;
    }
    ui->tableView->setModel(model);
}

void employee::on_radioButton_2_clicked()
{
    SearchBool = 0;
}

void employee::on_radioButton_3_clicked()
{
    SearchBool = 1;
}

void employee::on_radioButton_4_clicked()
{
    SearchBool = 2;
}

void employee::on_radioButton_5_clicked()
{
    SearchBool = 3;
}

void employee::on_radioButton_6_clicked()
{
    SearchBool = 4;
}

void employee::on_radioButton_7_clicked()
{
    SearchBool = 5;
}
