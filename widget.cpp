#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMaximumSize(600,400);
    setWindowTitle(QString("FReader"));
}

Widget::~Widget()
{
    delete ui;
}
