

#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QPushButton>
#include <QTableWidgetItem>
/*
 * сделать таблицу не редактируемой
 * errortipe4 не ошибка. формат фаила другой. нечитаемых строк нет, юзеры вообще не построкам записаны.
 * есть бракованый фаил. вот с ним надо подумать
 * Дописать ТЗ и ТО
 */
//функция создания виджета
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //задаем параметры окна
    setMaximumSize(450,300);
    setMinimumSize(450,300);
    setWindowTitle(QString("FReader"));
    //коннект кнопки и функции открытия
    ui->tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->open,&QPushButton::clicked,this,&Widget::open);
    //задаем другие начальные параметры (вектора строк дляобновления и строку состояния на экране)
    slist.clear();
    NP();
}
//устанавливает строку статуса на текст "no prioblems"
void Widget::NP()
{
    QString t = QString("No Problems");
    ui->stat->setText(t);
}
//реакция на кнопку "open"
void Widget::open()
{
    //даем пользователю выбрать файл
    QString FN=QFileDialog::getOpenFileName(this,"open","",tr("Text files(*.txt)"));
    //проверяем его выбор и запускаем (не запускаем) обновление таблицы
    if(FN.length()!=0)upd(FN);
    else
    {
        NP();
    }
}
//обновляет содержимое таблицы, читая из заданного файла
void Widget::upd(QString FN)
{

    QFile f(FN);
    char buf[128];
    //открываем файл на чтение
    if(f.open(QIODevice::ReadOnly))
    {
        QString dop;
        slist.clear();
        //выполняем чтение из файла в вектор (чтобы проверить его корректность и не заполнять таблицу из неправильного файла)
        while(!f.atEnd())
        {
            f.readLine(buf,128);
            dop=QString(buf);
            dop=dop.section("\r\n",0,0);
            //пропускаем пустые строки
            if(dop.length()==0)continue;
            //проверяем форму заолнениястрок
            if(dop.count("; ")==2 && dop.count(";")==3)
            {

                slist.push_back(QString(dop));
            }
            else
            {
                //в случае испорченной строки
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
        QString t = QString("file opening error, please try agane");
        ui->stat->setText(t);
        f.close();
        return ;
    }
    f.close();
    int s=slist.size();
    //проверяем данные на пустоту
    if(s==0)
    {
        QString t = QString("empty file, please try agane");
        ui->stat->setText(t);
        return ;
    }
    //задаем новый размер таблицы
    ui->tab->setRowCount(s);
    int i,j;
    QString dop2, dop3;
    QTableWidgetItem* nitem;
    //последовательно добавляем пункты в таблицу
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
    NP();
    ui->fn->setText(FN);
}
//диструктор
Widget::~Widget()
{
    delete ui;
}
