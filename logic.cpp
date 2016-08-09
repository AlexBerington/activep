#include "logic.h"
#include <QFile>
#include <QTextStream>
#include <QObject>
Logic::Logic()
{
}
void Logic::parse_csv(QString file)
{
    if(QFile::exists(file))
    {
        QFile pricex;
        pricex.setFileName(file);
        pricex.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream out(&pricex);
        QString p_parse = out.readAll();

        p_parse.replace("\n", ";");
        p_parse.replace(",", ".");
        this->price.clear();
        this->price = p_parse.split(';');

        pricex.close();


      }else{
        QMessageBox::warning(NULL,"Внимание!","Файл не найден!");

    }

}
void Logic::make_list_code()
{
    code_list.clear();
    dcode_list.clear();
    cost_list.clear();
    for(int i1=0; i1 < price.length() - s_all.toInt(); i1 += s_all.toInt() )
    {
        code_list.append(price[i1+s_code.toInt()-1]);
        dcode_list.append(price[i1+s_dCode.toInt()-1]);
        cost_list.append(price[i1+s_cost.toInt()-1]);

    }

}
void Logic::setMakeListParams(QString all, QString code,
                        QString dCode, QString cost)
{
    this->s_all = all;
    this->s_code = code;
    this->s_dCode = dCode;
    this->s_cost = cost;
}
void Logic::auto_complete(QString text)
{

        if(s_dCode.isEmpty())
        {
            for(int h=0; h < code_list.length(); h++)
            {

                if(code_list[h].contains(text,Qt::CaseInsensitive))
                {
                    ac_result = code_list[h] +" | "+ cost_list[h]+
                            "$";
                    emit newListItem(ac_result);
                }
            }
        }
        else
        {
            for(int h=0; h < code_list.length(); h++)
            {

                if(code_list[h].contains(text,Qt::CaseInsensitive) || dcode_list[h].contains(text,Qt::CaseInsensitive))
                {

                        if(code_list[h] != dcode_list[h])
                        {

                            ac_result = code_list[h] +
                                         " / " +
                                         dcode_list[h] +
                                " | " +
                                cost_list[h]+
                                    "$";

                           emit newListItem(ac_result);
                        }else{

                            ac_result = code_list[h] +
                                    " | "+
                                    cost_list[h]+
                                    "$";

                emit newListItem(ac_result);
                        }

                }
            }
        }
}


