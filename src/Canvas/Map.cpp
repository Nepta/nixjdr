#include "Map.h"
#include "ui_Map.h"

Map::Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map),
    m_BgLayer(bgFilename),
    m_MapLayer(tokenPath, tileStep),
    m_FoWLayer(tileStep),
    m_DrawingLayer(2, 2)
{
    ui->setupUi(this);

    CanvasScene *scene = new CanvasScene(1280, 1024); // TODO pass those value through a dialog box
    scene->addLayer(&m_BgLayer);
    scene->addLayer(&m_MapLayer);
    scene->addLayer(&m_FoWLayer);
    scene->addLayer(&m_DrawingLayer);

    m_DrawingLayer.initDrawingZone();

    m_BgLayer.setEnabled(false);
    m_MapLayer.setEnabled(true);
    m_FoWLayer.setEnabled(false);
    m_DrawingLayer.setEnabled(false);

    ui->m_View->setScene(scene);
    setWindowTitle(tr("Carte"));

    connect(ui->m_EditGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedEditionLayer(QAbstractButton*, bool)));
    connect(ui->m_DisplayGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedDisplayLayer(QAbstractButton*, bool)));
    connect(ui->m_PenSpinBox, SIGNAL(valueChanged(int)),
            &m_DrawingLayer, SLOT(setPenSize(int)));
    connect(ui->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            &m_DrawingLayer, SLOT(setEraserSize(int)));
    connect(ui->m_EraseButton, SIGNAL(clicked(bool)),
            &m_DrawingLayer, SLOT(erasePixmapContent()));
}

Map::~Map() {
    delete ui;
}

void Map::selectedEditionLayer(QAbstractButton *button, bool checked) {
    Layer *selectedLayer;

    if (button->objectName() == QString("m_MapEdit")) {
        selectedLayer = &m_MapLayer;
    }
    else if (button->objectName() == QString("m_FowEdit")) {
        selectedLayer = &m_FoWLayer;
    }
    else if (button->objectName() == QString("m_DrawingEdit")) {
        selectedLayer = &m_DrawingLayer;
    }

    selectedLayer->setEnabled(checked);
}

void Map::selectedDisplayLayer(QAbstractButton *button, bool checked) {
    Layer *selectedLayer;

    if (button->objectName() == QString("m_BgDisplay")) {
        selectedLayer = &m_BgLayer;
    }
    else if (button->objectName() == QString("m_MapDisplay")) {
        selectedLayer = &m_MapLayer;
    }
    else if (button->objectName() == QString("m_FowDisplay")) {
        selectedLayer = &m_FoWLayer;
    }
    else if (button->objectName() == QString("m_DrawingDisplay")) {
        selectedLayer = &m_DrawingLayer;
    }

    selectedLayer->setVisible(checked);
    ui->m_View->scene()->update(); // update the bakckground part of the Scene
}

Ui::Map *Map::getUi() {
    return ui;
}

MapLayer *Map::getMapLayer() {
    return &m_MapLayer;
}

void Map::on_collapseButton_clicked(bool checked) {
    ui->collapsibleWidget->setVisible(checked);
}
