#include "engine.h"
#include <QDebug>

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    {
        pixmap_ = scene_.addPixmap(QPixmap());
    }

    {
        QPen pen = QPen(Qt::NoPen);
        QColor brushColor = QColor(255, 0, 0, 128);
        QBrush brush = QBrush(brushColor);
        circle_ = scene_.addEllipse(0, 0, circleDiameter_, circleDiameter_, pen, brush);
        circle_->hide();
    }
}

QGraphicsScene*  Engine::scene()
{
    return &scene_;
}

void Engine::loadFile(const QString& filename)
{
    pixmap_->setPixmap(QPixmap(filename));
}

void Engine::onShowCircle()
{
    circle_->show();
}

void Engine::onHideCircle()
{
    circle_->hide();
}

void Engine::onCirclePosChanged(QPointF point)
{
    circle_->setPos(point - QPointF(circleDiameter_/2, circleDiameter_/2));
}

void Engine::onEnlargeCircle()
{
    QPointF mid = circle_->pos() + QPointF(circleDiameter_/2, circleDiameter_/2);

    circleDiameter_ *= 1.15;

    circle_->setRect(0, 0, circleDiameter_, circleDiameter_);
    circle_->setPos(mid - QPointF(circleDiameter_/2, circleDiameter_/2));
}

void Engine::onShrinkCircle()
{
    QPointF mid = circle_->pos() + QPointF(circleDiameter_/2, circleDiameter_/2);

    circleDiameter_ /= 1.15;
    circleDiameter_ = qMax<qreal>(1, circleDiameter_);

    circle_->setRect(0, 0, circleDiameter_, circleDiameter_);
    circle_->setPos(mid - QPointF(circleDiameter_/2, circleDiameter_/2));
}
