#include "wind.h"
#include "logic.h"
#include "form.h"
#include "form1.h"
#include <QtWidgets>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
wind::wind(QWidget *parent)
{

    my_logic = new Logic;
    QGridLayout *grid = new QGridLayout();


    lcd = new QLCDNumber;
    label1 = new QLabel("Код");
    edit1 = new QLineEdit;
    label2 = new QLabel("Ширина (см)");
    edit2 = new QLineEdit;
    label3 = new QLabel("Высота (см)");
    edit3 = new QLineEdit;
    go_btn = new QPushButton("Считать");
    label4 = new QLabel("Стекло");
    steklo = new QComboBox;
    steklo->addItem("Без стекла");
    steklo->addItem("Простое");
    steklo->addItem("Антибликовое");
    check1 = new QCheckBox;
    check1->setText("Подрамник");
    check2 = new QCheckBox;
    check2->setText("Поклейка");
    check2_1 = new QCheckBox;
    check2_2 = new QCheckBox;
    ac_list = new QListWidget;


    file_dialog = new QFileDialog;



        QMenuBar *menubar = new QMenuBar;
    check2_1->setText("До А4");
    check2_2->setText("До А3");
    kruchi = new QSpinBox;
    kruchi->setRange(0, 2);
    label5 = new QLabel("Крючки");
    QMenu *menu1 = new QMenu("Файл");
    QMenu *menu2 = new QMenu("Настройки");
    menu1->addAction("Открыть");
    menu2->addAction("Курс");
    menubar->addMenu(menu1);
    menubar->addMenu(menu2);

    grid->addWidget(lcd, 1, 0, 1, 2);
    grid->addWidget(label1, 2, 0);
    grid->addWidget(edit1, 2, 1);
    grid->addWidget(label2, 3, 0);
    grid->addWidget(edit2, 3, 1);
    grid->addWidget(label3, 4, 0);
    grid->addWidget(edit3, 4, 1);
    grid->addWidget(go_btn, 10, 0, 1, 2);
    grid->addWidget(steklo, 6, 1);
    grid->addWidget(label4, 6, 0);
    grid->addWidget(check1, 7, 0);
    grid->addWidget(menubar, 0,0);
    grid->addWidget(check2_1, 7, 1);
    grid->addWidget(check2_2, 8, 1);
    grid->addWidget(kruchi, 9, 1);
    grid->addWidget(label5, 9, 0);
    grid->addWidget(ac_list,0,3,11,1);

    edit1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    edit2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    edit3->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    go_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lcd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid->setContentsMargins(5,5,5,5);
    setLayout(grid);
   setWindowTitle("Activ Print");
   dlg = new Form;
   dlg2 = new Form1;

   
    connect(go_btn,SIGNAL(clicked(bool)),
            this,SLOT(slot_btn_press()));
    connect(check1, SIGNAL(toggled(bool)),
            check2_1, SLOT(setDisabled(bool)));
    connect(check1, SIGNAL(toggled(bool)), check2_2,
            SLOT(setDisabled(bool)));
    connect(check2_1, SIGNAL(toggled(bool)),
            check1, SLOT(setDisabled(bool)));
    connect(check2_2, SIGNAL(toggled(bool)),
            check1, SLOT(setDisabled(bool)));
    connect(check2_1, SIGNAL(toggled(bool)),
            check2_2, SLOT(setDisabled(bool)));
    connect(check2_2, SIGNAL(toggled(bool)),
            check2_1, SLOT(setDisabled(bool)));
    connect(edit1, SIGNAL(textChanged(QString)),
            this,SLOT(slot_autocomplete_code(QString)));
    connect(edit2,SIGNAL(textEdited(QString)),
            this,SLOT(slot_check_width(QString)));
    connect(edit3,SIGNAL(textEdited(QString)),
            this,SLOT(slot_check_height(QString)));
    connect(ac_list, SIGNAL(clicked(QModelIndex)),
            this, SLOT(slot_ac_click(QModelIndex)));
    connect(edit1, SIGNAL(editingFinished()),
            this, SLOT(slot_btn_press()));
    connect(edit2, SIGNAL(editingFinished()),
            this, SLOT(slot_btn_press()));
    connect(edit3, SIGNAL(editingFinished()),
            this, SLOT(slot_btn_press()));
    connect(check1, SIGNAL(clicked(bool)),
            this, SLOT(slot_btn_press()));
    connect(check2_1, SIGNAL(clicked(bool)),
            this, SLOT(slot_btn_press()));
    connect(check2_2, SIGNAL(clicked(bool)),
            this, SLOT(slot_btn_press()));
    connect(steklo, SIGNAL(currentTextChanged(QString)),
            this, SLOT(slot_btn_press()));
    connect(kruchi, SIGNAL(valueChanged(int))   ,
            this, SLOT(slot_btn_press()));
    connect(menu1, SIGNAL(triggered(QAction*)),
            this, SLOT(slot_change_file()));
    connect(dlg, SIGNAL(sendData(QString,QString)),
            this, SLOT(slot_receiveData(QString,QString)));
    connect(menu2, SIGNAL(triggered(QAction*)),
            dlg, SLOT(show()));
    connect(dlg, SIGNAL(sendData(QString,QString)),
            this, SLOT(slot_btn_press()));
    connect(dlg2, SIGNAL(sendData(QString,QString, QString, QString)),
            this, SLOT(slot_receiveData1(QString,QString,QString, QString)));
    connect(my_logic, SIGNAL(newListItem(QString)),
            this, SLOT(slot_receiveListItem(QString)));

}
void wind::slot_ac_click(QModelIndex index)
{


    QString buff = index.data().toString();
   buff = buff.left(buff.indexOf("/")-1);
   buff = buff.left(buff.indexOf("|")-1);
    edit1->setText(buff);
    ac_list->clear();

}

QString wind::get_code_edit()
{
    return edit1->text();
}

QString wind::get_width_edit()
{
    return edit2->text();
}

QString wind::get_height_edit()
{
    return edit3->text();
}
QString wind::get_kruch()
{
    return kruchi->text();
}

QString wind::get_stekl()
{
    return steklo->currentText();
}

void wind::slot_check_height(QString height)
{
    if(!height.toDouble())
    {
        if(!height.isEmpty())
        {
        QMessageBox::information(NULL,"Внимание!",
                                 "В это поле нужно вводить чисельные данные!");
        QString repeat;
        repeat = wind::edit3->text();
        repeat.chop(1);
        edit3->setText(repeat);
        }
    }
}

void wind::slot_change_file()
{

    \
    QString file_name = file_dialog->getOpenFileName();
    wind::activateWindow();
    this->my_logic->parse_csv(file_name);
    dlg2->show();

}



void wind::slot_check_width(QString width)
{
    if(!width.toDouble())
    {
        if(!width.isEmpty())
        {
        QMessageBox::information(NULL,"Внимание!",
                                 "В это поле нужно вводить чисельные данные!")  ;
        QString repeat;
        repeat = wind::edit2->text();
        repeat.chop(1);
        edit2->setText(repeat);
        }
    }
}
void wind::slot_autocomplete_code(QString text)
{
    if (text.size() != text.toUtf8().size())
    {
        QMessageBox::warning(NULL, "Внимание!" , "Русские символы не допустимы!");
        QString repeat;
        repeat = wind::edit1->text();
        repeat.chop(1);
        edit1->setText(repeat);
    }
    ac_list->clear();
    my_logic->auto_complete(text);
}
void wind::ac_list_add(QString text)
{
    ac_list->addItem(text);
}

void wind::slot_btn_press()
{
    QString bcost ;
    QString code = wind::get_code_edit();
    if(code!="")
    {

        for(int it=0;it < my_logic->code_list.length();it++)
        {
            if(code == my_logic->code_list[it])
            {
                bcost = my_logic->cost_list[it];

                break;
            }

        }
    }

    double width = wind::get_width_edit().toDouble() /100;
    double height = wind::get_height_edit().toDouble() /100;
    int buff = wind::get_kruch().toInt();
    int kruch;
    if(buff==1)
    {
        kruch = 5;
    }else if(buff==2){
        kruch = 10;
    }else{
        kruch = 0;
    }
    QString strBuff = wind::get_stekl();

    float param = 0;
    if(strBuff == "Простое") param = width * height * 280;
    else if(strBuff == "Антибликовое") param = width * height * 520;

    double cost = bcost.toDouble();
    cost = cost*course.toDouble() + ((cost*course.toDouble())/100)*plus_dol.toDouble();
    float param1 = 0;
    if(check2_1->checkState()&&check2_1->isEnabled()) param1 = 50;
    else if(check2_2->checkState()&&check2_2->isEnabled()) param1 = 90;
    else if(check1->checkState()&&check1->isEnabled()) param1 = (width * 2 + height * 2 + 0.2) * 100 ;
    int result = (width *2 + height *2 + 0.4) * cost + kruch + param + param1;
    wind::lcd->display(result);
}
