#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
}

QGraphicsScene*  Engine::scene()
{
    return &scene_;
}
