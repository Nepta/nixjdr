#include <algorithm>
#include "Map.h"
#include "ui_Map.h"
#include "ui_DrawingMenu.h"

Map::Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map),
    m_BgLayer(bgFilename),
    m_MapLayer(tokenPath, tileStep),
    m_DrawingLayer(2, 2, QColor(0, 0, 0))
{
    ui->setupUi(this);

    int sceneHeight = m_BgLayer.getBackground()->rect().height()
            + BG_OFFSET * m_MapLayer.getStep();
    int sceneWidth = m_BgLayer.getBackground()->rect().width()
            + BG_OFFSET * m_MapLayer.getStep();

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

/**
 * @brief Map::initDrawingLayer Initialize the specified layer as a DrawingLayer. Adds the layer to
 * the scene, initializes its drawing zone (transparent pixmap on which drawings are made) and connect
 * the signals and slots.
 * @param layer
 */
void Map::initDrawingLayer(Layer *layer) {
    DrawingLayer *drawingLayer = dynamic_cast<DrawingLayer*>(layer);

    m_Scene->addLayer(drawingLayer);
    drawingLayer->initDrawingZone();
    drawingLayer->setEnabled(false);

    Ui::DrawingMenu *drawingUi = ui->m_PageDrawingTools->getUi();

    connect(drawingUi->m_PenSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setPenSize(int)));
    connect(drawingUi->m_EraserSpinBox, SIGNAL(valueChanged(int)),
            drawingLayer, SLOT(setEraserSize(int)));
    connect(drawingUi->m_EraseButton, SIGNAL(clicked(bool)),
            drawingLayer, SLOT(erasePixmapContent()));


    for(int i=0; i < drawingUi->m_ToolLayout->count(); i++){
        QPushButton *currentButton = dynamic_cast<QPushButton*>(drawingUi->m_ToolLayout->itemAt(i)
                                                                ->widget());
        connect(currentButton, SIGNAL(clicked()), m_DrawingLayer.getTools(), SLOT(setCurrentToolCode()));
    }
}

void Map::initTooltip() {
    m_Tooltip.setParent(this);
    m_Tooltip.hide();

    connect(&m_MapLayer, SIGNAL(pushInfoTooltip(QString)),
            &m_Tooltip, SLOT(pushInfo(QString)));
    connect(&m_MapLayer, SIGNAL(showMapTooltip()),
            this, SLOT(showMapTooltip()));
    connect(&m_MapLayer, SIGNAL(hideMapTooltip()),
            &m_Tooltip, SLOT(hide()));

}

void Map::selectedEditionLayer(QAbstractButton *button, bool checked) {

    if (button->objectName() == QString("m_MapEdit")) {
        m_SelectedLayer = &m_MapLayer;

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
    return &m_MapLayer;
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
