#include "screens_pane.h"
#include "ui_screens_pane.h"
#include "QLayout"
#include "qpushbutton"
#include "QString"

screens_pane::screens_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::screens_pane)
{
    QVBoxLayout * radky = new QVBoxLayout(parent);
    bool color = 0;
    for(int i = 1; i <= 8; i++){
        QHBoxLayout * radek = new QHBoxLayout(parent);
        for(char c = 'A'; c <= 'H'; c++){
            QString label = QString("%1%2").arg(i).arg(c);
            QPushButton * tButton = new QPushButton(label);
            tButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            tButton->setMinimumSize(30, 30);
            radek->addWidget(tButton);
            color = !color;
        }
        radky->addLayout(radek);
    }
    this->setLayout(radky);
    ui->setupUi(this);
}

screens_pane::~screens_pane()
{
    delete ui;
}
