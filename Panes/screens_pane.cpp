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
    qDebug() << "enable screens pane";
    refresh();
}
void screens_pane::disable(){
    qDebug() << "disable screens pane";
}

void screens_pane::refresh(){
    screens = QApplication::screens();

    QLayoutItem *child;
    while ((child = ui->buttonLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }

    qDebug() << "=================================";

    int i = 1;
    for (QScreen * screen : screens){
        QRect geometry = screen->geometry();
        geometry.setSize(screen->devicePixelRatio() * geometry.size());

        qDebug() << "FPS:" << screen->refreshRate();
        qDebug() << "Name:" << screen->name();
        qDebug() << "Manufacturer:" << screen->manufacturer();
        qDebug() << "Model:" << screen->model();
        qDebug() << "Size:" << screen->size();
        // This is ridiculous. Resolution reported by Geometry() is scaled down by the scaling ratio and rounded. That means we can have rounding errors, which will cause SteamVR to fail, so a warning popup is needed
        qDebug() << "Scalaed geometry:" << geometry;
        qDebug() << "Ratio:" << screen->devicePixelRatio();
        qDebug() << "=================================";

        QPushButton * currBtn = new QPushButton();
        currBtn->setText(QString::number(i));
        currBtn->setCheckable(true);
        ui->buttonLayout->addWidget(currBtn);
        screenButtonGroup.addButton(currBtn);
        screenButtonGroup.setId(currBtn, i);

        i++;
    }

    qDebug() << "Screen count: " << screens.count();
    qDebug() << "=================================";

    drawScreens(-1); // No screen seleced by default
}

void screens_pane::buttonClicked(int id)
{
    qDebug() << id;
    qDebug() << screens[id-1]->geometry();

    QRect geometry = screens[id-1]->geometry();
    geometry.setSize(screens[id-1]->devicePixelRatio() * geometry.size());

    ui->lineEditDispRefreshRate->setText(QString::number(screens[id-1]->refreshRate()));
    ui->lineEditRenderHeight->setText(QString::number(geometry.height()));
    ui->lineEditRenderWidth->setText(QString::number(geometry.width()/2));
    ui->lineEditWindowHeight->setText(QString::number(geometry.height()));
    ui->lineEditWindowWidth->setText(QString::number(geometry.width()));
    ui->lineEditWindowX->setText(QString::number(geometry.x()));
    ui->lineEditWindowY->setText(QString::number(geometry.y()));

    emit changeSettingMemory("Display:displayFrequency", screens[id-1]->refreshRate());
    emit changeSettingMemory("Display:renderWidth", geometry.width()/2);
    emit changeSettingMemory("Display:renderHeight", geometry.height());
    emit changeSettingMemory("Display:windowWidth", geometry.width());
    emit changeSettingMemory("Display:windowHeight", geometry.height());
    emit changeSettingMemory("Display:windowX", geometry.x());
    emit changeSettingMemory("Display:windowY", geometry.y());

    drawScreens(id);
}

void screens_pane::drawScreens(int id){
    bool darkmode = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;

    QColor edgeCol = darkmode ? Qt::lightGray : Qt::lightGray;
    QColor fillCol = darkmode ? QColor(50,50,50) : QColor(50,50,50);
    QColor textCol = darkmode ? Qt::white : Qt::white;

    int minX = 0, minY = 0, maxX = 0, maxY = 0;

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

        QColor FillColor = (i == id) ? QPalette::Highlight : fillCol;

        QRectF rect(geometry.left() + lineW, geometry.top() - lineW, geometry.width() - 2*lineW, geometry.height()-2*lineW);
        QPen pen(edgeCol);           // border
        pen.setWidth(lineW);         // border width
        QBrush brush(FillColor);     // fill
        scene->addRect(rect, pen, brush);

        QFont font("Arial", 160);
        QGraphicsTextItem * textItem = scene->addText(QString::number(i), font);
        textItem->setDefaultTextColor(textCol);
        textItem->setPos(geometry.center() - QPoint(textItem->boundingRect().width()/2, textItem->boundingRect().height()));

        i++;
        // Add the text item to the scene
    }

    ui->screensGraphicsView->setScene(scene);
    ui->screensGraphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

}

void screens_pane::updateSettings(VRSettings * vrsettings){
    qDebug() << "It has been called upon screens_pane";
    ui->lineEditDispRefreshRate->setText(vrsettings->settingsMap["Display:displayFrequency"].toString());
    ui->lineEditRenderHeight->setText(vrsettings->settingsMap["Display:renderHeight"].toString());
    ui->lineEditRenderWidth->setText(vrsettings->settingsMap["Display:renderWidth"].toString());
    ui->lineEditWindowHeight->setText(vrsettings->settingsMap["Display:windowHeight"].toString());
    ui->lineEditWindowWidth->setText(vrsettings->settingsMap["Display:windowWidth"].toString());
    ui->lineEditWindowX->setText(vrsettings->settingsMap["Display:windowX"].toString());
    ui->lineEditWindowY->setText(vrsettings->settingsMap["Display:windowY"].toString());

}

void screens_pane::on_lineEditWindowWidth_textEdited(const QString &arg1)
{
    emit changeSettingMemory("Display:windowWidth", arg1.toInt());
}


void screens_pane::on_lineEditWindowHeight_textEdited(const QString &arg1)
{
    emit changeSettingMemory("Display:windowHeight", arg1.toInt());
}


void screens_pane::on_lineEditRenderWidth_textEdited(const QString &arg1)
{
    emit changeSettingMemory("Display:renderWidth", arg1.toInt());
}


void screens_pane::on_lineEditRenderHeight_textEdited(const QString &arg1)
{
    emit changeSettingMemory("Display:renderHeight", arg1.toInt());
}


void screens_pane::on_lineEditDispRefreshRate_textEdited(const QString &arg1)
{
    emit changeSettingMemory("Display:displayFrequency", arg1.toInt());
}


void screens_pane::on_lineEditWindowX_textEdited(const QString &arg1)
{
    emit changeSettingMemory("Display:windowX", arg1.toInt());
}


void screens_pane::on_lineEditWindowY_textEdited(const QString &arg1)
{
    emit changeSettingMemory("Display:windowY", arg1.toInt());
}

