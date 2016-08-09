#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
public slots:
    void slot_send();
signals:
    void sendData(QString fcours, QString fplus);
private:
    Ui::Form *ui;
};

#endif // FORM_H
