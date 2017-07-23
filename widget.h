#ifndef WIDGET_H
#define WIDGET_H


/* Progect:
*  We have one file with users' data, it must be presented, as not editable table.
*  \author ais
*  \version 1.0
*  \date 20.07.2017
*  \date Last Change: 23.07.2017
*/

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
    //Creator
    explicit Widget(QWidget *parent = 0);

    //"open" button clicked reaction
    void open();//реакция на кнопку "open"

    //destructor
    ~Widget();

private:

    //set Status label text "no problems"
    void NP();//обновление статуса "no problems"

    //reading chosen file to the table
    void upd(QString FN);//записать в таблицу из нового файла

    vector<QString> slist;//вектор строк для чтения из нового файла
    Ui::Widget *ui;
};

#endif //WIDGET_H
