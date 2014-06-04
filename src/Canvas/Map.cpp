#include "Database/Repository/RepositoryManager.h"
#include <algorithm>
#include "Map.h"
#include "ui_Map.h"
#include "ui_DrawingMenu.h"

Map::Map(QString bgFilename, TokenItem *tokenItem, int tileStep, QWidget *parent) :
    QWidget(parent),
    DBItem(),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    m_Layers = new Layers(bgFilename, 2, 2, Qt::black, tileStep, tokenItem);
    setWindowTitle(tr("Carte"));

    initScene(tileStep);
    initLayers();
    initDisplay();
    initTooltip();
}

Map::~Map() {
    delete ui;
    delete m_Scene;
}

void Map::initScene(int tileStep) {
    BackgroundLayer *bgLayer = dynamic_cast<BackgroundLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_BACKGROUND)
    );

    int sceneHeight = bgLayer->getBackground()->rect().height()
            + BG_OFFSET * tileStep;
    int sceneWidth = bgLayer->getBackground()->rect().width()
            + BG_OFFSET * tileStep;

    m_Scene = new CanvasScene(sceneWidth, sceneHeight);
    ui->m_View->setScene(m_Scene);
}

void Map::initLayers() {
    initBgLayer();
    initMapLayer();
    initFoWLayer();
    initDrawingLayer();
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

void Map::initMapTools() {
    connect(ui->m_MapScaler, SIGNAL(valueChanged(int)),
            ui->m_View, SLOT(zoom(int)));
}

void Map::initFoWTools(){
    FoWLayer *fowLayer = dynamic_cast<FoWLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_FOW)
    );

    connect(ui->m_FillFoW, SIGNAL(clicked(bool)),
            fowLayer, SLOT(fillFoW()));
    connect(ui->m_RemoveFoW, SIGNAL(clicked(bool)),
            fowLayer, SLOT(removeFoW()));
}

void Map::setupSenderClient(SenderClient *senderClient) {
    SenderHandler::setupSenderClient(senderClient);

    for (AbstractLayer *layer : m_Layers->getLayersList()) {
        layer->setSenderClient(senderClient);
    }
}

void Map::initBgLayer() {
    BackgroundLayer *bgLayer = dynamic_cast<BackgroundLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_BACKGROUND)
    );

    m_Scene->addLayer(bgLayer);
    bgLayer->setEnabled(false);

    // Add BackgroundLayer to the database
    RepositoryManager::s_BgLayerRepository.insertBgLayer(bgLayer, db_);
}

void Map::initMapLayer() {
    MapLayer *mapLayer = dynamic_cast<MapLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_MAP)
    );

    m_Scene->addLayer(mapLayer);
    mapLayer->setEnabled(true);
    mapLayer->setDatabase(db_);
    m_SelectedLayer = mapLayer;

    // Add MapLayer to the database
    RepositoryManager::s_MapLayerRepository.insertMapLayer(mapLayer, db_);

    // Map tools
    initMapTools();
}

/**
 * @brief Map::initFoWLayer Initializes the Fog of War Layer. If the tilestep is equal to 1, the
 * layer will be an instance of DrawingLayer, else it will be an instance of FoWLayer.
 * @param tileStep
 */
void Map::initFoWLayer() {
    FoWLayer *fowLayer = dynamic_cast<FoWLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_FOW)
    );

    m_Scene->addLayer(fowLayer);
    fowLayer->setEnabled(false);
    fowLayer->setDatabase(db_);

    // Add FoWLayer to the database
    RepositoryManager::s_FoWLayerRepository.insertFoWLayer(fowLayer, db_);

    // FoW tools
    initFoWTools();
}

/**
 * @brief Map::initDrawingLayer Initialize the specified layer as a DrawingLayer. Adds the layer to
 * the scene, initializes its drawing zone (transparent pixmap on which drawings are made) and connect
 * the signals and slots.
 * @param layer
 */
void Map::initDrawingLayer() {
    Ui::DrawingMenu *drawingUi = ui->m_PageDrawingTools->getUi();
    DrawingLayer *drawingLayer = static_cast<DrawingLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_DRAW)
    );

    m_Scene->addLayer(drawingLayer);
    drawingLayer->initDrawingZone();
    drawingLayer->setEnabled(false);

    connect(drawingUi->m_PenSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setPenSize(int)));
    connect(drawingUi->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setEraserSize(int)));
    connect(drawingUi->m_EraseButton, SIGNAL(clicked(bool)),
            drawingLayer, SLOT(erasePixmapContent()));

    for(int i=0; i < drawingUi->m_ToolLayout->count(); i++){
        QPushButton *currentButton = dynamic_cast<QPushButton*>(
                    drawingUi->m_ToolLayout->itemAt(i)->widget());
        connect(currentButton, SIGNAL(clicked()),
                drawingLayer->getTools(), SLOT(setCurrentToolCode()));
    }

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

/*Ui::Map *Map::getUi() {
    return ui;
}*/

MapLayer *Map::getMapLayer() {
    return dynamic_cast<MapLayer *>(m_Layers->getLayer(LayerCodes::LAYER_MAP));
}

int Map::getSceneHeight() {
    return m_Scene->height();
}

int Map::getSceneWidth() {
    return m_Scene->width();
}

BackgroundLayer *Map::getBgLayer() {
    return dynamic_cast<BackgroundLayer *>(m_Layers->getLayer(LayerCodes::LAYER_BACKGROUND));
}

FoWLayer *Map::getFoWLayer() {
    return dynamic_cast<FoWLayer *>(m_Layers->getLayer(LayerCodes::LAYER_FOW));
}

DrawingLayer *Map::getDrawingLayer() {
    return dynamic_cast<DrawingLayer *>(m_Layers->getLayer(LayerCodes::LAYER_DRAW));
}
