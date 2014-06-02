#include <algorithm>
#include "Map.h"
#include "ui_Map.h"
#include "ui_DrawingMenu.h"

Map::Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    m_Layers = new Layers(bgFilename, 2, 2, Qt::black, tileStep, tokenPath);
    initScene();
    initLayers();
    setWindowTitle(tr("Carte"));
    ui->m_StackedTools->show(); // Hide toolboxes
    initDisplay();
    initMapTools();
    initFoWTools();
    initDrawingLayer(LayerCodes::LAYER_DRAW);
    initTooltip();
}

Map::~Map() {
    delete ui;
}

void Map::initScene(){
    BackgroundLayer *bgLayer = static_cast<BackgroundLayer *>(m_Layers->getLayer(LayerCodes::LAYER_BACKGROUND));
    MapLayer *mapLayer = static_cast<MapLayer *>(m_Layers->getLayer(LayerCodes::LAYER_MAP));

    int sceneHeight = bgLayer->getBackground()->rect().height()
            + BG_OFFSET * mapLayer->getStep();
    int sceneWidth = bgLayer->getBackground()->rect().width()
            + BG_OFFSET * mapLayer->getStep();

    m_Scene = new CanvasScene(sceneWidth, sceneHeight); // TODO pass those value through a dialog box
    ui->m_View->setScene(m_Scene);
}

void Map::initLayers(){
    BackgroundLayer *bgLayer = static_cast<BackgroundLayer *>(m_Layers->getLayer(LayerCodes::LAYER_BACKGROUND));
    MapLayer *mapLayer =static_cast<MapLayer *>(m_Layers->getLayer(LayerCodes::LAYER_MAP));
    FoWLayer *fowLayer =static_cast<FoWLayer *>(m_Layers->getLayer(LayerCodes::LAYER_FOW));
    DrawingLayer *drawingLayer =static_cast<DrawingLayer *>(m_Layers->getLayer(LayerCodes::LAYER_DRAW));

    m_Scene->addLayer(bgLayer);
    m_Scene->addLayer(mapLayer);
    m_Scene->addLayer(fowLayer);
    m_Scene->addLayer(drawingLayer);

    bgLayer->setEnabled(false);
    mapLayer->setEnabled(true);
    fowLayer->setEnabled(false);
    drawingLayer->setEnabled(false);
}

void Map::initDisplay(){
    connect(ui->m_EditGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedEditionLayer(QAbstractButton*, bool)));
    connect(ui->m_DisplayGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedDisplayLayer(QAbstractButton*, bool)));

    m_EditionMap.insert(LayerCodes::LAYER_MAP, ui->m_PageMapTools);
    m_EditionMap.insert(LayerCodes::LAYER_FOW, ui->m_PageFoWTools);
    m_EditionMap.insert(LayerCodes::LAYER_DRAW, ui->m_PageDrawingTools);
}

void Map::initMapTools(){
    connect(ui->m_MapScaler, SIGNAL(valueChanged(int)),
            ui->m_View, SLOT(zoom(int)));
}

void Map::initFoWTools(){
    if(dynamic_cast<FoWLayer *>(m_Layers->getLayer(LayerCodes::LAYER_FOW)) != NULL){
        FoWLayer *fowLayer = static_cast<FoWLayer *>(m_Layers->getLayer(LayerCodes::LAYER_FOW));
        connect(ui->m_FillFoW, SIGNAL(clicked(bool)),
                fowLayer, SLOT(fillFoW()));
        connect(ui->m_RemoveFoW, SIGNAL(clicked(bool)),
                fowLayer, SLOT(removeFoW()));
    }
    else if(dynamic_cast<DrawingLayer *>(m_Layers->getLayer(LayerCodes::LAYER_FOW)) != NULL){
        initDrawingLayer(LayerCodes::LAYER_FOW);
    }
}

/**
 * @brief Map::initDrawingLayer Initialize the specified layer as a DrawingLayer. Adds the layer to
 * the scene, initializes its drawing zone (transparent pixmap on which drawings are made) and connect
 * the signals and slots.
 * @param layer
 */
void Map::initDrawingLayer(LayerCodes code) {
    Ui::DrawingMenu *drawingUi = ui->m_PageDrawingTools->getUi();
    DrawingLayer *drawingLayer = static_cast<DrawingLayer *>(m_Layers->getLayer(code));

    connect(drawingUi->m_PenSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setPenSize(int)));
    connect(drawingUi->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setEraserSize(int)));
    connect(drawingUi->m_EraseButton, SIGNAL(clicked(bool)),
            drawingLayer, SLOT(erasePixmapContent()));


//    for(int i=0; i < drawingUi->m_ToolLayout->count(); i++){
//        QPushButton *currentButton = dynamic_cast<QPushButton*>(
//                    drawingUi->m_ToolLayout->itemAt(i)->widget());
//        connect(currentButton, SIGNAL(clicked()),
//                drawingLayer->getTools(), SLOT(setCurrentToolCode()));
//    }

    drawingLayer->initDrawingZone();
}

void Map::initTooltip() {
    m_Tooltip.setParent(this);
    m_Tooltip.hide();
    MapLayer *mapLayer = static_cast<MapLayer *>(m_Layers->getLayer(LayerCodes::LAYER_MAP));

    connect(mapLayer, SIGNAL(pushInfoTooltip(QString)),
            &m_Tooltip, SLOT(pushInfo(QString)));
    connect(mapLayer, SIGNAL(showMapTooltip()),
            this, SLOT(showMapTooltip()));
    connect(mapLayer, SIGNAL(hideMapTooltip()),
            &m_Tooltip, SLOT(hide()));

}

void Map::selectedEditionLayer(QAbstractButton *button, bool checked) {
    m_Layers->setCurrentLayerCode(button->objectName());

    LayerCodes buttonCode = m_Layers->s_ButtonCodesMap.value(button->objectName());
    m_SelectedLayer = m_Layers->getLayer(buttonCode);
    ui->m_StackedTools->show();
    m_SelectedLayer->setEnabled(checked);
    ui->m_StackedTools->setCurrentWidget(m_EditionMap.value(buttonCode));
}

void Map::selectedDisplayLayer(QAbstractButton *button, bool checked) {
    AbstractLayer *selectedLayer;
    selectedLayer = m_Layers->getLayer(m_Layers->s_ButtonCodesMap.value(button->objectName()));

    if (selectedLayer != NULL) {
        selectedLayer->setVisible(checked);
        selectedLayer->setEnabled(true);
        ui->m_View->scene()->update(); // update the background part of the Scene
    }
}

/**
 * @brief Map::showMapTooltip Displays the tooltip at the bottom right of the map.
 */
void Map::showMapTooltip() {
    QPoint position(
        ui->m_View->size().width() - m_Tooltip.size().width() - Tooltip::TOOLTIP_OFFSET,
        ui->m_View->size().height() - m_Tooltip.size().height() - Tooltip::TOOLTIP_OFFSET
    );

    m_Tooltip.showTooltip(position);
}

Ui::Map *Map::getUi() {
    return ui;
}

MapLayer *Map::getMapLayer() {
    return static_cast<MapLayer *>(m_Layers->getLayer(LayerCodes::LAYER_MAP));
}

void Map::on_collapseButton_clicked(bool checked) {
    ui->scrollArea->setVisible(checked);
}

/**
 * @brief Map::keyPressEvent Reimplemented from QWidget to dispatch key press events to the selected
 * layer.
 * @param keyEvent
 */
void Map::keyPressEvent(QKeyEvent *keyEvent){
    m_Scene->sendEvent(m_SelectedLayer, keyEvent);
}

/**
 * @brief Map::keyPressEvent Reimplemented from QWidget to dispatch key release events to the selected
 * layer.
 * @param keyEvent
 */
void Map::keyReleaseEvent(QKeyEvent *keyEvent){
    m_Scene->sendEvent(m_SelectedLayer, keyEvent);
}
