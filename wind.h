#ifndef WIND_H
#define WIND_H
//#include <QMenuBar>
#include <QWidget>
#include <QtWidgets>
#include "logic.h"
#include "form.h"
#include "form1.h"
class wind : public QWidget
{
    Q_OBJECT
public:

    explicit wind(QWidget *parent = 0);

    void ac_list_add(QString text);
private:
    Form *dlg;
    Form1 *dlg2;
    Logic *my_logic;
    QString course = "28";
    QString plus_dol = "40";
    void parse_csv(QString file);
    QMenuBar *menu;
    QListWidget *ac_list;
    QLabel *label1;
    QLabel *picture;
    QLineEdit *edit1;
    QLabel *label2;
    QLineEdit *edit2;
    QLabel *label3;
    QLineEdit *edit3;
    QPushButton *go_btn;
    QLCDNumber *lcd;
    QComboBox *steklo;
    QLabel *label4;
    QCheckBox *check1;
    QCheckBox *check2;
    QCheckBox *check2_1;
    QCheckBox *check2_2;
    QSpinBox *kruchi;
    QLabel *label5;
    QGroupBox *gr1;
    QString get_code_edit();
    QString get_stekl();
    QString get_width_edit();
    QString get_height_edit();
    QString get_kruch();
    QGroupBox *group();
    QStatusBar *bar;
    QLabel *bar_label;
    QFileDialog *file_dialog;
public slots:

    void slot_btn_press();
    void slot_autocomplete_code(QString text);
    void slot_check_width(QString width);
    void slot_check_height(QString height);
    void slot_ac_click(QModelIndex index);
    void slot_change_file();
    void slot_receiveListItem(QString str)
    {
        this->ac_list_add(str);
    }

    void slot_receiveData(QString str1, QString str2)
    {
        course = str1;
        plus_dol = str2;
    }
    void slot_receiveData1(QString str3, QString str4, QString str5, QString str6)
    {

        this->my_logic->setMakeListParams(str6, str3, str5, str4);
        this->my_logic->make_list_code();
    }

};

#endif // WIND_H

