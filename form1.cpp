#include "form1.h"
#include "ui_form1.h"
#include "wind.h"
Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(slot_send()));
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));


}
Form1::~Form1()
{
    delete ui;
}
void Form1::slot_send()
{
    if(ui->lineEdit->text() != "" && ui->lineEdit_2->text() != ""
            && ui->lineEdit_4->text() != "" && ui->lineEdit->text() != "0"
            && ui->lineEdit_2->text() != "0" && ui->lineEdit_4->text() != "0"
            && ui->lineEdit_3->text() != "0")
    {
    emit sendData(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text());
    }else{
        QMessageBox::information(NULL, "Внимание", "Заполните все поля! \n Значение 0 не допускается !");
    }
}
