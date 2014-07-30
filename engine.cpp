#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
}

QGraphicsScene*  Engine::scene()
{
    return &scene_;
}

QPixmap Engine::loadFile(const QString& filename)
{
    QPixmap pxm = QPixmap(filename);
    scene_.addPixmap(pxm);

    return pxm;
}
