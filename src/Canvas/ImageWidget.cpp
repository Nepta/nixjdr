#include "ImageWidget.h"
#include "ui_Map.h"
#include "ui_DrawingMenu.h"

ImageWidget::ImageWidget(QString bgFilename, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Map),
    m_BgLayer(bgFilename),
    m_DrawingLayer(2, 2, QColor(0, 0, 0))
{
    ui->setupUi(this);

    int sceneHeight = m_BgLayer.getBackground()->rect().height() + BG_OFFSET;
    int sceneWidth = m_BgLayer.getBackground()->rect().width() + BG_OFFSET;

    m_Scene = new CanvasScene(sceneWidth, sceneHeight);

    m_Scene->addLayer(&m_BgLayer);
    m_BgLayer.setEnabled(false);

    initDrawingLayer(&m_DrawingLayer);

    ui->m_View->setScene(m_Scene);
    setWindowTitle(tr("Carte"));

    // Hide toolboxes
    ui->m_StackedTools->show();
    ui->groupBox->hide();
    ui->groupBox_2->hide();
    ui->m_StackedTools->setCurrentWidget(ui->m_PageDrawingTools);
}


void ImageWidget::initDrawingLayer(Layer *layer) {
    DrawingLayer *drawingLayer = dynamic_cast<DrawingLayer*>(layer);

    m_Scene->addLayer(drawingLayer);
    drawingLayer->initDrawingZone();
    drawingLayer->setEnabled(true);

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


void ImageWidget::on_collapseButton_clicked(bool checked) {
    ui->scrollArea->setVisible(checked);
}

/**
 * @brief Map::keyPressEvent Reimplemented from QWidget to dispatch key press events to the drawing
 * layer.
 * @param keyEvent
 */
void ImageWidget::keyPressEvent(QKeyEvent *keyEvent){
    m_Scene->sendEvent(&m_DrawingLayer, keyEvent);
}

/**
 * @brief Map::keyPressEvent Reimplemented from QWidget to dispatch key release events to the drawing
 * layer.
 * @param keyEvent
 */
void ImageWidget::keyReleaseEvent(QKeyEvent *keyEvent){
    m_Scene->sendEvent(&m_DrawingLayer, keyEvent);
}
