#include "form.h"
#include "ui_form.h"
#include "wind.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(slot_send()));
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));

}

Form::~Form()
{
    delete ui;
}
void Form::slot_send()
{
    if(ui->lineEdit->text() != "" && ui->lineEdit_2->text() != "")
    {
    emit sendData(ui->lineEdit->text(), ui->lineEdit_2->text());
    }else{
        QMessageBox::information(NULL, "Внимание", "Заполните все поля!");
    }
}
