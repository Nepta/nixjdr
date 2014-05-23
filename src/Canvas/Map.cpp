#include "Map.h"
#include "ui_Map.h"

Map::Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map),
    m_MapLayer(tokenPath, tileStep),
    m_FoWLayer(tileStep)
{
    ui->setupUi(this);

    CanvasScene *scene = new CanvasScene(bgFilename);
    scene->addLayer(&m_MapLayer);
    scene->addLayer(&m_FoWLayer);

    m_MapLayer.setEnabled(true);
    m_FoWLayer.setEnabled(false);

    ui->m_View->setScene(scene);
    setWindowTitle(tr("Carte"));

    connect(ui->m_EditGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedEditionLayer(QAbstractButton*, bool)));
    connect(ui->m_DisplayGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedDisplayLayer(QAbstractButton*, bool)));
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

    selectedLayer->setEnabled(checked);
}

void Map::selectedDisplayLayer(QAbstractButton *button, bool checked) {
    Layer *selectedLayer;

    if (button->objectName() == QString("m_MapDisplay")) {
        selectedLayer = &m_MapLayer;
    }
    else if (button->objectName() == QString("m_FowDisplay")) {
        selectedLayer = &m_FoWLayer;
    }

    selectedLayer->setVisible(checked);
}

Ui::Map *Map::getUi() {
    return ui;
}

MapLayer *Map::getMapLayer() {
    return &m_MapLayer;
}

