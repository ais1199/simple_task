
/* Progect:
*  We have one file with users' data, it must be presented, as not editable table.
*  \author ais
*  \version 1.0
*  \date 20.07.2017
*  \date Last Change: 23.07.2017
*/
#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QPushButton>
#include <QTableWidgetItem>
/*
 * errortipe4 не ошибка. формат фаила другой. нечитаемых строк нет, юзеры вообще не построкам записаны.
 * есть бракованый фаил. вот с ним надо подумать
 * Дописать ТЗ и ТО
 */
//криэйтор
//Creator
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //задаем параметры окна
    //set window's characteristics
    setMaximumSize(450,300);
    setMinimumSize(450,300);
    setWindowTitle(QString("FReader"));
    //коннект кнопки и функции открытия
    //connect for file-open button
    ui->tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->open,&QPushButton::clicked,this,&Widget::open);
    //задаем другие начальные параметры (вектора строк дляобновления и строку состояния на экране)
    //set others start parameters
    slist.clear();
    NP();
}
//устанавливает строку статуса на текст "no prioblems"
//set Status label text "no problems"
void Widget::NP()
{
    QString t = QString("No Problems");
    ui->stat->setText(t);
}
//реакция на кнопку "open"
//"open" button clicked reaction
void Widget::open()
{
    //даем пользователю выбрать файл
    //user chooses file to open
    QString FN=QFileDialog::getOpenFileName(this,"open","",tr("Text files(*.txt)"));
    //проверяем его выбор и запускаем (не запускаем) обновление таблицы
    //check his choice
    if(FN.length()!=0)upd(FN);
    else
    {
        NP();
    }
}
//обновляет содержимое таблицы, читая из заданного файла
//reading chosen file to the table
void Widget::upd(QString FN)
{

    QFile f(FN);
    char buf[128];
    //открываем файл на чтение
    //open to read
    if(f.open(QIODevice::ReadOnly))
    {
        QString dop;
        slist.clear();
        //выполняем чтение из файла в вектор (чтобы проверить его корректность и не заполнять таблицу из неправильного файла)
        //reading to vector (to check it's correctness)
        while(!f.atEnd())
        {
            f.readLine(buf,128);
            dop=QString(buf);
            dop=dop.section("\r\n",0,0);
            //пропускаем пустые строки
            //ignore empty strings
            if(dop.length()==0)continue;
            //проверяем форму заолнения строк
            //checking string correctness
            if(dop.count("; ")==2 && dop.count(";")==3)
            {

                slist.push_back(QString(dop));
            }
            else
            {
                //в случае испорченной строки
                //broken string case
                QString t = QString("broken string, file is closed");
                ui->stat->setText(t);
                f.close();
                return ;
            }
        }
    }
    else
    {
        //в случае неудачного открытия файла
        //file opening error case
        QString t = QString("file opening error, please try agane");
        ui->stat->setText(t);
        f.close();
        return ;
    }
    f.close();
    int s=slist.size();
    //проверяем данные на пустоту
    //empty file case
    if(s==0)
    {
        QString t = QString("empty file, please try agane");
        ui->stat->setText(t);
        return ;
    }
    //задаем новый размер таблицы
    //set new table size
    ui->tab->setRowCount(s);
    int i,j;
    QString dop2, dop3;
    QTableWidgetItem* nitem;
    //последовательно добавляем пункты в таблицу
    //sequentially items inserting
    for(i=0;i<s;i++)
    {
        dop2=slist[i];
        for(j=0;j<2;j++)
        {
            dop3=dop2.section("; ",j,j);
            nitem = new QTableWidgetItem(dop3,0);
            ui->tab->setItem(i,j,nitem);
        }
        dop3=dop2.section("; ",2,2);
        dop3=dop3.section(";",0,0);
        nitem = new QTableWidgetItem(dop3,0);
        ui->tab->setItem(i,j,nitem);
    }
    //обновляем поля статуса и файла
    //file and status labels' updating
    NP();
    ui->fn->setText(FN);
}
//диструктор
//destructor
Widget::~Widget()
{
    delete ui;
}
