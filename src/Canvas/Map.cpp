#include "Database/Repository/RepositoryManager.h"
#include "Network/MapClient.h"
#include "Map.h"
#include "ui_Map.h"
#include "ui_DrawingMenu.h"

Map::Map(bool isImage, QString mapName, QString bgFilename, TokenItem *tokenItem, int tileStep,
         bool isMj, QWidget *parent) :
    QWidget(parent),
    DBItem(),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    this->setWindowTitle(mapName);
    initRole(isMj);

    m_Layers = new Layers(bgFilename, 2, 2, Qt::black, tileStep, tokenItem, isMj);

    initScene(tileStep);
    initLayers();
    initDisplay();
    initTooltip();

    m_IsImage = isImage;
    if(isImage){
        initAsImage();
    }
}

Map::Map(DBItem item, BackgroundLayer *bgLayer, MapLayer *mapLayer, FoWLayer *fowLayer,
         DrawingLayer *drawingLayer, bool isMj) :
    DBItem(),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id = itemHashMap.value("id").toInt();
    QString windowtitle = itemHashMap.value("windowtitle").toString();
    int sceneHeight = itemHashMap.value("sceneheight").toInt();
    int sceneWidth = itemHashMap.value("scenewidth").toInt();
    bool isImage = itemHashMap.value("isimage").toBool();

    id_ = id;
    setWindowTitle(windowtitle);
    initRole(isMj);
    m_Layers = new Layers(bgLayer, mapLayer, fowLayer, drawingLayer);
    initScene(sceneWidth, sceneHeight);
    initLayers(false);
    initDisplay();
    initTooltip();

    m_IsImage = isImage;
    if(isImage){
        initAsImage();
    }
}

Map::~Map() {
    delete ui;
    delete m_Scene;
    delete m_Tooltip;
}

/**
 * @brief Map::closeEvent reimplemented from QWidget. When the map is closed, it is removed from
 * the client's map list
 * @param closeEvent
 */
void Map::closeEvent(QCloseEvent *closeEvent) {
    QWidget::closeEvent(closeEvent);

    if (m_SenderClient != NULL) {
        MapClient *mapClient = dynamic_cast<MapClient*>(m_SenderClient);
        mapClient->removeMapFromList(this);
    }
}

/**
 * @brief Map::initRole calls for the functions needed to initiate a map as Mj or Player
 * @param isMj
 */
void Map::initRole(bool isMj){
    if(isMj){
        initMj();
    }
    else{
        initPlayer();
    }
}

void Map::initMj(){
}

/**
 * @brief Map::initPlayer hides the buttons that the player shouldn't be able to use
 */
void Map::initPlayer(){
    ui->m_FowEdit->hide();
    ui->m_FowDisplay->hide();
}

/**
 * @brief Map::initScene creates the scene with a margin around the background image. Requires
 * BackgroundLayer to be initiated
 * @param tileStep
 */
void Map::initScene(int tileStep) {
    int sceneHeight, sceneWidth;

    BackgroundLayer *bgLayer = dynamic_cast<BackgroundLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_BACKGROUND)
    );

    if (tileStep < 5) {
       tileStep = 5;
    }

    sceneHeight = bgLayer->getBackground()->rect().height()
            + BG_OFFSET * tileStep;
    sceneWidth = bgLayer->getBackground()->rect().width()
            + BG_OFFSET * tileStep;

    initScene(sceneWidth, sceneHeight);
}

/**
 * @brief Map::initScene creates a scene with the specified width and height
 * @param sceneWidth
 * @param sceneHeight
 */
void Map::initScene(int sceneWidth, int sceneHeight) {
    m_Scene = new CanvasScene(sceneWidth, sceneHeight);
    ui->m_View->setScene(m_Scene);
}

/**
 * @brief Map::initLayers calls for every init<Layername> function; the calling order determines
 * the layers' superposition order
 * @param addToDb wether the layer should be added to the Db or not
 */
void Map::initLayers(bool addToDb) {
    initBgLayer(addToDb);
    initMapLayer(addToDb);
    initFoWLayer(addToDb);
    initDrawingLayer(addToDb);
}

/**
 * @brief Map::initDisplay connects the buttons with the layers
 */
void Map::initDisplay(){
    connect(ui->m_EditGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedEditionLayer(QAbstractButton*, bool)));
    connect(ui->m_DisplayGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedDisplayLayer(QAbstractButton*, bool)));

    m_EditionMap.insert(LayerCodes::LAYER_MAP, ui->m_PageMapTools);
    m_EditionMap.insert(LayerCodes::LAYER_FOW, ui->m_PageFoWTools);
    m_EditionMap.insert(LayerCodes::LAYER_DRAW, ui->m_PageDrawingTools);
}

/**
 * @brief Map::initMapTools connects the view tools with the view
 */
void Map::initMapTools() {
    connect(ui->m_MapScaler, SIGNAL(valueChanged(int)),
            ui->m_View, SLOT(zoom(int)));
    connect(ui->m_View, SIGNAL(changeLabelScale(double)), ui->labelScale, SLOT(setNum(double)));
}

/**
 * @brief Map::initFoWTools connects the FoW tools with the FoWLayer
 */
void Map::initFoWTools(){
    FoWLayer *fowLayer = dynamic_cast<FoWLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_FOW)
    );

    connect(ui->m_FillFoW, SIGNAL(clicked(bool)),
            fowLayer, SLOT(fillFoW()));
    connect(ui->m_RemoveFoW, SIGNAL(clicked(bool)),
            fowLayer, SLOT(removeFoW()));
}

/**
 * @brief Map::initDrawingTools connects the drawing Tools with the DrawingLayer
 */
void Map::initDrawingTools() {
    Ui::DrawingMenu *drawingUi = ui->m_PageDrawingTools->getUi();
    DrawingLayer *drawingLayer = dynamic_cast<DrawingLayer*>(
        m_Layers->getLayer(LayerCodes::LAYER_DRAW)
    );

    connect(drawingUi->m_PenSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setPenSize(int)));
    connect(drawingUi->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setEraserSize(int)));
    connect(drawingUi->m_EraseButton, SIGNAL(clicked(bool)),
            drawingLayer, SLOT(erasePixmapContent()));
    connect(drawingUi->m_SendButton, SIGNAL(clicked(bool)),
            drawingLayer, SLOT(updateDisplayRemote()));

    for(int i=0; i < drawingUi->m_ToolLayout->count(); i++){
        QPushButton *currentButton = dynamic_cast<QPushButton*>(
                    drawingUi->m_ToolLayout->itemAt(i)->widget());
        connect(currentButton, SIGNAL(clicked()),
                drawingLayer->getTools(), SLOT(setCurrentToolCode()));
    }
}

/**
 * @brief Map::setSenderClient sets the sender client for every layers
 * @param senderClient
 */
void Map::setSenderClient(SenderClient *senderClient) {
    SenderHandler::setSenderClient(senderClient);

    for (AbstractLayer *layer : m_Layers->getLayersList()) {
        layer->setSenderClient(senderClient);
    }
}

/**
 * @brief Map::initBgLayer adds the bgLayer to the scene, not enabled, and can add it to the Db and
 * connects the signals and slots.
 * @param addToDb
 */
void Map::initBgLayer(bool addToDb) {
    BackgroundLayer *bgLayer = dynamic_cast<BackgroundLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_BACKGROUND)
    );

    m_Scene->addLayer(bgLayer);
    bgLayer->setEnabled(false);

    if (addToDb) {
        // Add BackgroundLayer to the database
        RepositoryManager::s_BgLayerRepository.insertBgLayer(bgLayer);
    }
}

/**
 * @brief Map::initMapLayer adds the mapLayer to the scene, enabled, and can add it to the Db and
 * connects the signals and slots.
 * @param addToDb
 */
void Map::initMapLayer(bool addToDb) {
    MapLayer *mapLayer = dynamic_cast<MapLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_MAP)
    );

    m_Scene->addLayer(mapLayer);
    mapLayer->setEnabled(true);
    m_SelectedLayer = mapLayer;

    // Map tools
    initMapTools();

    if (addToDb) {
        // Add MapLayer to the database
        RepositoryManager::s_MapLayerRepository.insertMapLayer(mapLayer);
    }
}

/**
 * @brief Map::initFoWLayer adds the bgLayer to the scene, not enabled, and can add it to the Db and
 * connects the signals and slots.
 * @param tileStep
 */
void Map::initFoWLayer(bool addToDb) {
    FoWLayer *fowLayer = dynamic_cast<FoWLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_FOW)
    );

    m_Scene->addLayer(fowLayer);
    fowLayer->setEnabled(false);

    // FoW tools
    initFoWTools();

    if (addToDb) {
        // Add FoWLayer to the database
        RepositoryManager::s_FoWLayerRepository.insertFoWLayer(fowLayer);
    }
}

/**
 * @brief Map::initDrawingLayer Initialize the specified layer as a DrawingLayer. Adds the layer to
 * the scene, initializes its drawing zone (transparent pixmap on which drawings are made) and connect
 * the signals and slots.
 * @param layer
 */
void Map::initDrawingLayer(bool addToDb) {
    DrawingLayer *drawingLayer = static_cast<DrawingLayer *>(
        m_Layers->getLayer(LayerCodes::LAYER_DRAW)
    );

    m_Scene->addLayer(drawingLayer);

    // if the drawingLayer has been loaded from the db, the drawing zone is not initialized with a
    // new pixmap.
    drawingLayer->initDrawingZone(addToDb);
    drawingLayer->setEnabled(false);

    initDrawingTools();

    if (addToDb) {
        // Add DrawingLayer to the database
        RepositoryManager::s_DrawingLayerRepository.insertDrawingLayer(drawingLayer);
    }
}

/**
 * @brief Map::initTooltip associates a tooltip with the map and set the tooltip for the layers which
 * need it.
 */
void Map::initTooltip() {
    m_Tooltip = new MapTooltip(ui->m_View, this);
    m_Tooltip->hide();

    MapLayer *mapLayer = static_cast<MapLayer *>(m_Layers->getLayer(LayerCodes::LAYER_MAP));
    mapLayer->setTooltip(m_Tooltip);
}

/**
 * @brief Map::selectedEditionLayer changes the selected layer according to the button selected
 * @param button
 * @param checked
 */
void Map::selectedEditionLayer(QAbstractButton *button, bool checked) {
    m_Layers->setCurrentLayerCode(button->objectName());

    LayerCodes buttonCode = m_Layers->s_ButtonCodesMap.value(button->objectName());
    m_SelectedLayer = m_Layers->getLayer(buttonCode);
    ui->m_StackedTools->show();
    m_SelectedLayer->setEnabled(checked);
    ui->m_StackedTools->setCurrentWidget(m_EditionMap.value(buttonCode));
}

/**
 * @brief Map::selectedDisplayLayer changes the visible layers according to the buttons selected
 * @param button
 * @param checked
 */
void Map::selectedDisplayLayer(QAbstractButton *button, bool checked) {
    AbstractLayer *selectedLayer;
    selectedLayer = m_Layers->getLayer(m_Layers->s_ButtonCodesMap.value(button->objectName()));

    if (selectedLayer != NULL) {
        selectedLayer->setVisible(checked);
        ui->m_View->scene()->update(); // update the background part of the Scene
    }
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

bool Map::getIsImage(){
    return m_IsImage;
}

void Map::connectToLogger(LogClient* client){
	connect(getMapLayer(), SIGNAL(spriteMoved(QString)), client, SLOT(sendMessageToServer(QString)));
	connect(getMapLayer(), SIGNAL(spriteRemoved(QString)), client, SLOT(sendMessageToServer(QString)));
	connect(getMapLayer(), SIGNAL(spriteAdded(QString)), client, SLOT(sendMessageToServer(QString)));
}

/**
 * @brief Map::initAsImage initializes the map but hides the FoWLayer and map Layer as well as the
 * associated buttons
 */
void Map::initAsImage() {
    // Hide toolboxes
    ui->m_StackedTools->show();
    ui->groupBox->hide();
    ui->groupBox_2->hide();
    ui->m_StackedTools->setCurrentWidget(ui->m_PageDrawingTools);

    m_Layers->setCurrentLayerCode("m_DrawingEdit");
    m_Layers->getLayer(LayerCodes::LAYER_DRAW)->setEnabled(true);

    m_Layers->getLayer(LayerCodes::LAYER_MAP)->hide();
    m_Layers->getLayer(LayerCodes::LAYER_FOW)->hide();
}
