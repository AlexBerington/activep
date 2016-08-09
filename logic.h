#ifndef LOGIC_H
#define LOGIC_H
#include <QtWidgets>
#include <QObject>

class Logic : public QObject
{
    Q_OBJECT
public:
    Logic();
     void make_list_code();
     void parse_csv(QString file);
     void setMakeListParams(QString all, QString code,
                       QString dCode, QString cost);
     void auto_complete(QString text);
     QStringList code_list;
     QStringList dcode_list;
     QStringList cost_list;
     int ac_status;
private:
     QStringList price;
     QString s_all;
     QString s_code;
     QString s_dCode;
     QString s_cost;
     QString ac_result;
signals:
          void newListItem(QString);
};

#endif // LOGIC_H
