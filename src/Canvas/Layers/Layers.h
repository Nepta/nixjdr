#ifndef LAYERS_H
#define LAYERS_H

#include <QHash>
#include "Canvas/CanvasScene.h"
#include "Canvas/Layers/AbstractLayer.h"

enum class LayerCodes : quint16 {
    LAYER_BACKGROUND,
    LAYER_DRAW,
    LAYER_FOW,
    LAYER_MAP
};
inline uint qHash(const LayerCodes &key) { return qHash((quint16) key); }

class Layers : public QObject
{
    Q_OBJECT

public:
    const static QHash<QString, LayerCodes> s_ButtonCodesMap;

    Layers(QString filename, int penSize, int eraserSize, QColor color, int step, QString spritePath);
    ~Layers();

    AbstractLayer *getLayer(LayerCodes code);
    QList<AbstractLayer *> getLayersList();

    AbstractLayer *getCurrentLayer();
    void setCurrentLayerCode(QString key);

private:
    QHash<LayerCodes, AbstractLayer *> m_LayersMap;
    LayerCodes m_CurrentLayerCode;
    CanvasScene *m_Scene;

public slots:
};

#endif // TOOLS_H
