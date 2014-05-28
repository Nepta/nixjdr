#include <algorithm>
#include "Map.h"
#include "ui_Map.h"

Map::Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map),
    m_BgLayer(bgFilename),
    m_MapLayer(tokenPath, tileStep),
    m_DrawingLayer(2, 2, QColor(0, 0, 0))
{
    ui->setupUi(this);

    int sceneHeight = m_BgLayer.getBackground()->rect().height()
            +2*4*m_MapLayer.getStep();
    int sceneWidth = m_BgLayer.getBackground()->rect().width()
            +2*4*m_MapLayer.getStep();

    m_Scene = new CanvasScene(sceneWidth, sceneHeight); // TODO pass those value through a dialog box

    m_Scene->addLayer(&m_BgLayer);
    m_BgLayer.setEnabled(false);

    m_Scene->addLayer(&m_MapLayer);
    m_MapLayer.setEnabled(true);
    m_SelectedLayer = &m_MapLayer;

    initFoWLayer(tileStep);

    initDrawingLayer(&m_DrawingLayer);

    ui->m_View->setScene(m_Scene);
    setWindowTitle(tr("Carte"));

    // Hide toolboxes
    ui->m_StackedTools->show();

    // display & edition
    connect(ui->m_EditGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedEditionLayer(QAbstractButton*, bool)));
    connect(ui->m_DisplayGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedDisplayLayer(QAbstractButton*, bool)));

    // Map tools
    connect(ui->m_MapScaler, SIGNAL(valueChanged(int)),
            ui->m_View, SLOT(zoom(int)));

    // FoW tools
    if (m_IsGridFoWLayer) {
        connect(ui->m_FillFoW, SIGNAL(clicked(bool)),
                m_FoWLayer, SLOT(fillFoW()));
        connect(ui->m_RemoveFoW, SIGNAL(clicked(bool)),
                m_FoWLayer, SLOT(removeFoW()));
    }

    initTooltip();
}

Map::~Map() {
    delete ui;
    delete m_FoWLayer;
}

void Map::initFoWLayer(int tileStep) {
    if (tileStep > 1) {
        m_FoWLayer = new FoWLayer(tileStep);
        m_IsGridFoWLayer = true;
    }
    else {
        m_FoWLayer = new DrawingLayer(2, 2, QColor(50, 50, 50));
        m_IsGridFoWLayer = false;
        initDrawingLayer(m_FoWLayer);
    }
    m_Scene->addLayer(m_FoWLayer);
    m_FoWLayer->setEnabled(false);
}

void Map::initDrawingLayer(Layer *layer) {
    DrawingLayer *drawingLayer = dynamic_cast<DrawingLayer*>(layer);

    m_Scene->addLayer(drawingLayer);
    drawingLayer->initDrawingZone();
    drawingLayer->setEnabled(false);

    connect(ui->m_PenSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setPenSize(int)));
    connect(ui->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setEraserSize(int)));
    connect(ui->m_EraseButton, SIGNAL(clicked(bool)),
            drawingLayer, SLOT(erasePixmapContent()));
}

void Map::initTooltip() {
    m_MapTooltip.setParent(this);
    m_MapTooltip.hide();

    connect(&m_MapLayer, SIGNAL(showSpriteInfo(Sprite*)),
            this, SLOT(showMapSpriteTooltip(Sprite*)));

    connect(&m_MapLayer, SIGNAL(showMoveInfo(int, int, int, int)),
            this, SLOT(showMapMoveTooltip(int, int, int, int)));

    connect(&m_MapLayer, SIGNAL(hideInfo()),
            this, SLOT(hideMapTooltip()));

}

void Map::selectedEditionLayer(QAbstractButton *button, bool checked) {

    if (button->objectName() == QString("m_MapEdit")) {
        m_SelectedLayer = &m_MapLayer;

//        ui->m_StackedTools->hide();
        ui->m_StackedTools->show();
        ui->m_StackedTools->setCurrentWidget(ui->m_PageMapTools);
    }
    else if (button->objectName() == QString("m_FowEdit")) {
        m_SelectedLayer = m_FoWLayer;

        ui->m_StackedTools->show();
        if (m_IsGridFoWLayer) {
            ui->m_StackedTools->setCurrentWidget(ui->m_PageFoWTools);
        }
        else {
            ui->m_StackedTools->setCurrentWidget(ui->m_PageDrawingTools);
        }
    }
    else if (button->objectName() == QString("m_DrawingEdit")) {
        m_SelectedLayer = &m_DrawingLayer;

        ui->m_StackedTools->show();
        ui->m_StackedTools->setCurrentWidget(ui->m_PageDrawingTools);
    }
    else {
        m_SelectedLayer = NULL;
        ui->m_StackedTools->hide();
    }

    if (m_SelectedLayer != NULL) {
        m_SelectedLayer->setEnabled(checked);
    }
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
        selectedLayer = m_FoWLayer;
    }
    else if (button->objectName() == QString("m_DrawingDisplay")) {
        selectedLayer = &m_DrawingLayer;
    }
    else {
        selectedLayer = NULL;
    }

    if (selectedLayer != NULL) {
        selectedLayer->setVisible(checked);
        ui->m_View->scene()->update(); // update the background part of the Scene
    }
}

void Map::showMapTooltip(QString tooltip) {

    m_MapTooltip.setTooltipText(tooltip);

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

void Map::showMapSpriteTooltip(Sprite* sprite){
    QString spriteInfo = tr("Pile de jetons : %1 jeton(s).")
        .arg(sprite->getStackNumber());
    showMapTooltip(spriteInfo);
}

void Map::showMapMoveTooltip(int oldPosX, int oldPosY, int currentPosX, int currentPosY){

    int diffX = qAbs(oldPosX - currentPosX);
    int diffY = qAbs(oldPosY - currentPosY);
    int shorterDistance = std::max(diffX, diffY) + std::min(diffX,diffY)/2;

    QString tooltip = QString(tr("Distance la plus courte: %1")).arg(shorterDistance);

    showMapTooltip(tooltip);
}

Ui::Map *Map::getUi() {
    return ui;
}

MapLayer *Map::getMapLayer() {
    return &m_MapLayer;
}

void Map::on_collapseButton_clicked(bool checked) {
    ui->scrollArea->setVisible(checked);
}


void Map::keyPressEvent(QKeyEvent *keyEvent){
    m_Scene->sendEvent(m_SelectedLayer, keyEvent);
}

void Map::keyReleaseEvent(QKeyEvent *keyEvent){
    m_Scene->sendEvent(m_SelectedLayer, keyEvent);
}
