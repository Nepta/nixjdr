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

    m_Scene = new CanvasScene(1280, 1024); // TODO pass those value through a dialog box

    m_Scene->addLayer(&m_BgLayer);
    m_BgLayer.setEnabled(false);

    m_Scene->addLayer(&m_MapLayer);
    m_MapLayer.setEnabled(true);

    m_Scene->addLayer(&m_FoWLayer);
    m_FoWLayer.setEnabled(false);

    initDrawingLayer();

    ui->m_View->setScene(m_Scene);
    setWindowTitle(tr("Carte"));

    // display & edition
    connect(ui->m_EditGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedEditionLayer(QAbstractButton*, bool)));
    connect(ui->m_DisplayGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedDisplayLayer(QAbstractButton*, bool)));

    initTooltip();
}

Map::~Map() {
    delete ui;
}

void Map::initDrawingLayer() {
    m_Scene->addLayer(&m_DrawingLayer);
    m_DrawingLayer.initDrawingZone();
    m_DrawingLayer.setEnabled(false);

    connect(ui->m_PenSpinBox, SIGNAL(valueChanged(int)),
            &m_DrawingLayer, SLOT(setPenSize(int)));
    connect(ui->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            &m_DrawingLayer, SLOT(setEraserSize(int)));
    connect(ui->m_EraseButton, SIGNAL(clicked(bool)),
            &m_DrawingLayer, SLOT(erasePixmapContent()));
}

void Map::initTooltip() {
    m_MapTooltip.setParent(this);
    m_MapTooltip.hide();

    connect(&m_MapLayer, SIGNAL(showSpriteInfo(Sprite*)),
            this, SLOT(showMapTooltip(Sprite*)));
    connect(&m_MapLayer, SIGNAL(hideSpriteInfo()),
            this, SLOT(hideMapTooltip()));
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

void Map::showMapTooltip(Sprite* sprite) {
    QString spriteInfo = tr("Pile de jetons : %1 jeton(s).")
        .arg(sprite->getStackNumber());

    m_MapTooltip.setTooltipText(spriteInfo);

    // Move the tooltip at the bottom right of the map
    m_MapTooltip.move(
        ui->m_View->size().width() - m_MapTooltip.size().width() - MapTooltip::MAP_TOOLTIP_OFFSET,
        ui->m_View->size().height() - m_MapTooltip.size().height() - MapTooltip::MAP_TOOLTIP_OFFSET
    );

    m_MapTooltip.show();
}

void Map::hideMapTooltip() {
    m_MapTooltip.hide();
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
