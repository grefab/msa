#include "engine.h"
#include <QPainter>

#include <QDebug>

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    {
        imagePixmapItem_ = scene_.addPixmap(QPixmap());
    }

    {
        drawingPixmapItem_ = scene_.addPixmap(QPixmap());
        drawingPixmapItem_->setOpacity(0.5);
    }

    {
        QPen pen = QPen(Qt::NoPen);
        QColor brushColor = QColor(255, 0, 0, 128);
        QBrush brush = QBrush(brushColor);
        circleItem_ = scene_.addEllipse(0, 0, circleDiameter_, circleDiameter_, pen, brush);
        circleItem_->hide();
    }
}

QGraphicsScene*  Engine::scene()
{
    return &scene_;
}

void Engine::loadFile(const QString& filename)
{
    QPixmap pxm = QPixmap(filename);
    imagePixmapItem_->setPixmap(pxm);

    drawingPixmap_ = QPixmap(pxm.size());
    drawingPixmap_.fill(Qt::transparent);
    drawingPixmapItem_->setPixmap(drawingPixmap_);
}

void Engine::onShowCircle()
{
    circleItem_->show();
}

void Engine::onHideCircle()
{
    circleItem_->hide();
}

void Engine::onCirclePosChanged(QPointF point)
{
    circleCenter_ = point;
    circleItem_->setPos(point - QPointF(circleDiameter_/2, circleDiameter_/2));
}

void Engine::onEnlargeCircle()
{
    QPointF mid = circleItem_->pos() + QPointF(circleDiameter_/2, circleDiameter_/2);

    circleDiameter_ *= 1.15;

    circleItem_->setRect(0, 0, circleDiameter_, circleDiameter_);
    circleItem_->setPos(mid - QPointF(circleDiameter_/2, circleDiameter_/2));
}

void Engine::onShrinkCircle()
{
    QPointF mid = circleItem_->pos() + QPointF(circleDiameter_/2, circleDiameter_/2);

    circleDiameter_ /= 1.15;
    circleDiameter_ = qMax<qreal>(1, circleDiameter_);

    circleItem_->setRect(0, 0, circleDiameter_, circleDiameter_);
    circleItem_->setPos(mid - QPointF(circleDiameter_/2, circleDiameter_/2));
}

void Engine::onAddCircle(QPointF point)
{
    QPen pen = QPen(Qt::NoPen);
    QColor brushColor = QColor(255, 255, 0, 255);
    QBrush brush = QBrush(brushColor);

    QPainter p(&drawingPixmap_);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawEllipse(point, circleDiameter_/2, circleDiameter_/2);

    drawingPixmapItem_->setPixmap(drawingPixmap_);
}

void Engine::onRemoveCircle(QPointF point)
{
    QPen pen = QPen(Qt::NoPen);
    QColor brushColor = Qt::transparent;
    QBrush brush = QBrush(brushColor);

    QPainter p(&drawingPixmap_);
    p.setPen(pen);
    p.setBrush(brush);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawEllipse(point, circleDiameter_/2, circleDiameter_/2);

    drawingPixmapItem_->setPixmap(drawingPixmap_);
}
