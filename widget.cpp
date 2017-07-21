#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMaximumSize(450,300);
    setMinimumSize(450,300);
    setWindowTitle(QString("FReader"));
    //ui->tab->setReadOnly(true);
    connect(ui->open,&QPushButton::clicked,this,&Widget::upd);

    NP();
}
void Widget::NP()
{
    ui->stat->setText(QString("No Problems"));
}
void Widget::upd()
{
    /*QString FN=QFileDialog::getOpenFileName(this,"open","",tr("Text files(*.txt)"));
    QFile f(FN);
    char buf[128];
    if(f.open(QIODevice::ReadOnly))
    {
        while(!f.atEnd())
        {
            f.readLine(buf,128);
        }
        NP();
    }
    f.close(); */
}

Widget::~Widget()
{
    delete ui;
}
