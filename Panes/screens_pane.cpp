#include "screens_pane.h"
#include "ui_screens_pane.h"
#include <QLayout>
#include <QPushButton>
#include <QString>
#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QStyleHints>>

screens_pane::screens_pane(QWidget *parent)
    : generic_pane(parent)
    , ui(new Ui::screens_pane)
{
    ui->setupUi(this);
    connect(ui->refreshButton, &QPushButton::clicked, this, &screens_pane::refresh);
    connect(&screenButtonGroup, &QButtonGroup::idClicked, this, &screens_pane::buttonClicked);
    screenButtonGroup.setExclusive(true);
    refresh();
}

screens_pane::~screens_pane()
{
    delete ui;
}

void screens_pane::enable(){
    refresh();
}
void screens_pane::disable(){
    qDebug() << "disable screens pane";
}

void screens_pane::updateSettings(VRSettings * vrsettings){

}

void screens_pane::refresh(){
    qDebug() << "enable screens pane";

    bool darkmode = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;

    QColor edgeCol = Qt::lightGray;
    QColor fillCol = QColor(50,50,50);
    QColor textCol = Qt::white;

    screens = QApplication::screens();

    QLayoutItem *child;
    while ((child = ui->buttonLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }

    int minX = 0, minY = 0, maxX = 0, maxY = 0;

    qDebug() << "=================================";

    QGraphicsScene * scene = new QGraphicsScene;
    int lineW = 50;
    int i = 1;
    for (QScreen * screen : screens){
        QRect geometry = screen->geometry();
        geometry.setSize(screen->devicePixelRatio() * geometry.size());
        minX = std::min(minX, geometry.left());
        minY = std::min(minY, geometry.top());
        maxX = std::max(maxX, geometry.right()+1);
        maxY = std::max(maxY, geometry.bottom()+1);
        qDebug() << "FPS:" << screen->refreshRate();
        qDebug() << "Name:" << screen->name();
        qDebug() << "Manufacturer:" << screen->manufacturer();
        qDebug() << "Model:" << screen->model();
        qDebug() << "Size:" << screen->size();
        // This is ridiculous. Resolution reported by Geometry() is scaled down by the scaling ratio and rounded. That means we can have rounding errors, which will cause SteamVR to fail, so a warning popup is needed
        qDebug() << "Geometry:" << geometry;
        qDebug() << "Ratio:" << screen->devicePixelRatio();
        qDebug() << "=================================";

        QRectF rect(geometry.left() + lineW, geometry.top() - lineW, geometry.width() - 2*lineW, geometry.height()-2*lineW);
        QPen pen(edgeCol);           // Blue border
        pen.setWidth(lineW);              // Border width
        QBrush brush(fillCol);     // Yellow fill
        scene->addRect(rect, pen, brush);

        QFont font("Arial", 160);
        QGraphicsTextItem * textItem = scene->addText(QString::number(i), font);
        textItem->setDefaultTextColor(textCol);
        textItem->setPos(geometry.center() - QPoint(textItem->boundingRect().width()/2, textItem->boundingRect().height()));

        QPushButton * currBtn = new QPushButton();
        currBtn->setText(QString::number(i));
        currBtn->setCheckable(true);
        ui->buttonLayout->addWidget(currBtn);
        screenButtonGroup.addButton(currBtn);
        screenButtonGroup.setId(currBtn, i);

        i++;
        // Add the text item to the scene
    }

    qDebug() << "Screen count: " << screens.count();
    qDebug() << "MinX = " << minX;
    qDebug() << "MaxX = " << maxX;
    qDebug() << "MinY = " << minY;
    qDebug() << "MaxY = " << maxY;
    qDebug() << "=================================";



    ui->screensGraphicsView->setScene(scene);
    ui->screensGraphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void screens_pane::buttonClicked(int id)
{
    qDebug() << id;
    qDebug() << screens[id-1]->geometry();
}
