#include "DrawingLayerRepository.h"

const QString DrawingLayerRepository::getTableName() {
    return "drawinglayer";
}

int DrawingLayerRepository::insertDrawingLayer(DrawingLayer *drawingLayer) {
    QHash<QString, QVariant> args {
        {"pixmap", drawingLayer->getPixmapData()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(drawingLayer, qb, args);

    return id;
}
