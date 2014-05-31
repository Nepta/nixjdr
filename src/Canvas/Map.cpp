#include "Map.h"
#include "ui_Map.h"
#include "ui_DrawingMenu.h"

Map::Map(QString bgFilename, TokenItem *tokenItem, int tileStep, QWidget *parent) :
    QWidget(parent),
    DBItem("map"),
    ui(new Ui::Map),
    m_Scene()
{
    ui->setupUi(this);

    construct(bgFilename, tokenItem, tileStep);
}

void Map::construct(int id, QString bgFilename, TokenItem *tokenItem, int tileStep) {
    id_ = id;
    construct(bgFilename, tokenItem, tileStep);
}

void Map::construct(QString bgFilename, TokenItem *tokenItem, int tileStep) {
    setWindowTitle(tr("Carte"));

    initBgLayer(bgFilename);
    initScene(tileStep);
    initMapLayer(tokenItem, tileStep);
    initFoWLayer(tileStep);
    initDrawingLayer();

    // Hide toolboxes
    ui->m_StackedTools->show();

    // display & edition
    connect(ui->m_EditGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedEditionLayer(QAbstractButton*, bool)));
    connect(ui->m_DisplayGroup, SIGNAL(buttonToggled(QAbstractButton*, bool)),
            this, SLOT(selectedDisplayLayer(QAbstractButton*, bool)));

    initTooltip();
}

Map::~Map() {
    delete ui;
    delete m_BgLayer;
    delete m_MapLayer;
    delete m_FoWLayer;
    delete m_DrawingLayer;
}

void Map::initBgLayer(QString bgFilename) {
    m_BgLayer = new BackgroundLayer(bgFilename);
    m_Scene.addLayer(m_BgLayer);
    m_BgLayer->setEnabled(false);
}

void Map::initMapLayer(TokenItem *tokenItem, int tileStep) {
    m_MapLayer = new MapLayer(db_, tokenItem, tileStep);
    m_Scene.addLayer(m_MapLayer);
    m_MapLayer->setEnabled(true);
}

/**
 * @brief Map::initFoWLayer Initializes the Fog of War Layer. If the tilestep is equal to 1, the
 * layer will be an instance of DrawingLayer, else it will be an instance of FoWLayer.
 * @param tileStep
 */
void Map::initFoWLayer(int tileStep) {
    if (tileStep > 1) {
        m_FoWLayer = new FoWLayer(db_, tileStep);
        m_IsGridFoWLayer = true;
        m_Scene.addLayer(m_FoWLayer);
        m_FoWLayer->setEnabled(false);

        // FoW tools
        connect(ui->m_FillFoW, SIGNAL(clicked(bool)),
                m_FoWLayer, SLOT(fillFoW()));
        connect(ui->m_RemoveFoW, SIGNAL(clicked(bool)),
                m_FoWLayer, SLOT(removeFoW()));
    }
    else {
        m_FoWLayer = new DrawingLayer(2, 2, QColor(50, 50, 50));
        m_IsGridFoWLayer = false;
        initDrawingLayer(m_FoWLayer);
    }
}

void Map::initDrawingLayer() {
    m_DrawingLayer = new DrawingLayer(2, 2, QColor(0, 0, 0));
    initDrawingLayer(m_DrawingLayer);
}

/**
 * @brief Map::initDrawingLayer Initialize the specified layer as a DrawingLayer. Adds the layer to
 * the scene, initializes its drawing zone (transparent pixmap on which drawings are made) and connect
 * the signals and slots.
 * @param layer
 */
void Map::initDrawingLayer(Layer *layer) {
    DrawingLayer *drawingLayer = dynamic_cast<DrawingLayer*>(layer);

    m_Scene.addLayer(drawingLayer);
    drawingLayer->initDrawingZone();
    drawingLayer->setEnabled(false);

    Ui::DrawingMenu *drawingUi = ui->m_PageDrawingTools->getUi();

    connect(drawingUi->m_PenSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setPenSize(int)));
    connect(drawingUi->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setEraserSize(int)));
    connect(drawingUi->m_EraseButton, SIGNAL(clicked(bool)),
            drawingLayer, SLOT(erasePixmapContent()));
}

void Map::initScene(int tileStep) {
    int sceneHeight = m_BgLayer->getBackground()->rect().height()
            + 2*4 * tileStep;
    int sceneWidth = m_BgLayer->getBackground()->rect().width()
            + 2*4 * tileStep;

    m_Scene.setSceneRect(0, 0, sceneWidth, sceneHeight); // TODO pass those value through a dialog box
    ui->m_View->setScene(&m_Scene);
}

void Map::initTooltip() {
    m_Tooltip.setParent(this);
    m_Tooltip.hide();

    connect(m_MapLayer, SIGNAL(pushInfoTooltip(QString)),
            &m_Tooltip, SLOT(pushInfo(QString)));
    connect(m_MapLayer, SIGNAL(showMapTooltip()),
            this, SLOT(showMapTooltip()));
    connect(m_MapLayer, SIGNAL(hideMapTooltip()),
            &m_Tooltip, SLOT(hide()));
}

void Map::selectedEditionLayer(QAbstractButton *button, bool checked) {
    if (button->objectName() == QString("m_MapEdit")) {
        m_SelectedLayer = m_MapLayer;

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
        m_SelectedLayer = m_DrawingLayer;

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
        selectedLayer = m_BgLayer;
    }
    else if (button->objectName() == QString("m_MapDisplay")) {
        selectedLayer = m_MapLayer;
    }
    else if (button->objectName() == QString("m_FowDisplay")) {
        selectedLayer = m_FoWLayer;
    }
    else if (button->objectName() == QString("m_DrawingDisplay")) {
        selectedLayer = m_DrawingLayer;
    }
    else {
        selectedLayer = NULL;
    }

    if (selectedLayer != NULL) {
        selectedLayer->setVisible(checked);
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
    return m_MapLayer;
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
    m_Scene.sendEvent(m_SelectedLayer, keyEvent);
}

/**
 * @brief Map::keyPressEvent Reimplemented from QWidget to dispatch key release events to the selected
 * layer.
 * @param keyEvent
 */
void Map::keyReleaseEvent(QKeyEvent *keyEvent){
    m_Scene.sendEvent(m_SelectedLayer, keyEvent);
}
