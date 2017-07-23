#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void open();//реакция на кнопку "open"
    ~Widget();

private:
    void NP();//обновление статуса "no problems"
    void upd(QString FN);//записать в таблицу из нового файла
    vector<QString> slist;//вектор строк для чтения из нового файла
    Ui::Widget *ui;
};

#endif //WIDGET_H
