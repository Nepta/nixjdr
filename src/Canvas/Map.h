#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>

#include "Network/SenderHandler.h"

#include "Layers/BackgroundLayer.h"
#include "Layers/MapLayer.h"
#include "Layers/FoWLayer.h"
#include "Layers/DrawingLayer.h"
#include "Layers/Layers.h"
#include "Layers/AbstractLayer.h"

#include "Database/DBItem.h"

#include "Log/LogClient.h"

#include "MapTooltip.h"
#include "CanvasView.h"
#include "CanvasScene.h"
#include "NotificationStacker.h"

namespace Ui {
    class Map;
}

class Map : public QWidget, public DBItem, public SenderHandler
{
    Q_OBJECT

public:
    static const int BG_OFFSET = 2*4;

    explicit Map(bool isImage, QString mapName, QString bgFilename, int bgWidth, int bgHeight,
                 TokenItem *tokenItem, int tileStep, bool isMj, QWidget *parent = 0);
    Map(DBItem item, BackgroundLayer *bgLayer, MapLayer *mapLayer, FoWLayer *fowLayer,
        DrawingLayer *drawingLayer, bool isMj);
    ~Map();

    void closeEvent(QCloseEvent *closeEvent);

    void setSenderClient(SenderClient *senderClient);

    int getSceneHeight();
    int getSceneWidth();
    BackgroundLayer *getBgLayer();
    MapLayer *getMapLayer();
    FoWLayer *getFoWLayer();
    DrawingLayer *getDrawingLayer();
    bool getIsImage();
    void connectToLogger(LogClient* client);

private slots:
    void selectedEditionLayer(QAbstractButton *button, bool checked);
    void selectedDisplayLayer(QAbstractButton *button, bool checked);

    void on_collapseButton_clicked(bool checked);
    void on_m_DisplayCheckBox_clicked(bool checked);
    void on_m_EditCheckBox_clicked(bool checked);

private:
    Ui::Map *ui;
    CanvasScene *m_Scene;
    AbstractLayer *m_SelectedLayer;
    Layers *m_Layers;
    QHash<LayerCodes, QWidget *> m_EditionMap;
    MapTooltip *m_Tooltip;
    bool m_IsImage;
    bool m_IsMj;

    void initRole(bool isMj);
    void initMj();
    void initPlayer();

    QPixmap createBgPixmap(QString filename, int bgWidth, int bgHeight, int tileStep);

    void initScene(int tileStep);
    void initScene(int sceneWidth, int sceneHeight);
    void initDisplay();
    void initTooltip();

    void initLayers(bool addToDb = true);
    void initMapTools();
    void initFoWTools();
    void initDrawingTools();
    void initBgLayer(bool addToDb);
    void initMapLayer(bool addToDb);
    void initFoWLayer(bool addToDb);
    void initDrawingLayer(bool addToDb);
    void initAsImage();

    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
};

#endif // MAP_H
