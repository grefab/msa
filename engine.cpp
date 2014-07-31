#include "engine.h"
#include <QPainter>
#include <QFileInfo>

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
        circleItem_ = scene_.addEllipse(0, 0, circleRadius_*2, circleRadius_*2, pen, brush);
        circleItem_->hide();
    }
}

QGraphicsScene*  Engine::scene()
{
    return &scene_;
}

void Engine::loadFile(QString filename, QString maskname)
{

    QFileInfo file(filename);
    if( file.exists() ) {
        QPixmap pxm = QPixmap(filename);
        imagePixmapItem_->setPixmap(pxm);

        QFileInfo maskFile(maskname);
        if( maskFile.exists() ) {
            drawingPixmap_ = QPixmap(maskname);
        } else {
            drawingPixmap_ = QPixmap(pxm.size());
            drawingPixmap_.fill(Qt::transparent);
        }
        drawingPixmapItem_->setPixmap(drawingPixmap_);
    }


    emit fileLoaded(filename);
}

void Engine::saveMask(QString filename)
{
    drawingPixmap_.save(filename);
}

void Engine::saveComposite(QString filename)
{
    QImage maskImage = drawingPixmap_.toImage();
    QImage originalImage = imagePixmapItem_->pixmap().toImage();

    {
        QImage alpha = QImage(maskImage.size(), QImage::Format_Indexed8);
        alpha.fill(128);
        maskImage.setAlphaChannel(alpha);
    }

    {
        QPainter p(&originalImage);
        p.drawImage(originalImage.rect(),
                    maskImage,
                    maskImage.rect());
    }

    originalImage.save(filename);
}

void Engine::calculateArea()
{
    QImage maskImage = drawingPixmap_.toImage();

    qreal area = 0;
    for( int y = 0; y < maskImage.height(); y++ ) {
        uchar* line = maskImage.scanLine(y);

        for( int x = 0; x < maskImage.width(); ++x) {
            area += (qreal)line[x*4+3] / 255.0f;
        }
    }

    emit areaCalculated(area);
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
    circleItem_->setPos(point - QPointF(circleRadius_, circleRadius_));
}

void Engine::onEnlargeCircle()
{
    QPointF mid = circleItem_->pos() + QPointF(circleRadius_, circleRadius_);

    circleRadius_ *= 1.15;

    circleItem_->setRect(0, 0, circleRadius_*2, circleRadius_*2);
    circleItem_->setPos(mid - QPointF(circleRadius_, circleRadius_));
}

void Engine::onShrinkCircle()
{
    QPointF mid = circleItem_->pos() + QPointF(circleRadius_, circleRadius_);

    circleRadius_ /= 1.15;
    circleRadius_ = qMax<qreal>(0.5, circleRadius_);

    circleItem_->setRect(0, 0, circleRadius_*2, circleRadius_*2);
    circleItem_->setPos(mid - QPointF(circleRadius_, circleRadius_));
}

void Engine::onAddCircle(QPointF point)
{
    {
        QPen pen = QPen(Qt::NoPen);
        QColor brushColor = QColor(255, 255, 0, 255);
        QBrush brush = QBrush(brushColor);

        QPainter p(&drawingPixmap_);
        p.setPen(pen);
        p.setBrush(brush);
        p.drawEllipse(point, circleRadius_, circleRadius_);
    }

    drawingPixmapItem_->setPixmap(drawingPixmap_);
}

void Engine::onRemoveCircle(QPointF point)
{
    {
        QPen pen = QPen(Qt::NoPen);
        QColor brushColor = Qt::transparent;
        QBrush brush = QBrush(brushColor);

        QPainter p(&drawingPixmap_);
        p.setPen(pen);
        p.setBrush(brush);
        p.setCompositionMode(QPainter::CompositionMode_Source);
        p.drawEllipse(point, circleRadius_, circleRadius_);
    }
    drawingPixmapItem_->setPixmap(drawingPixmap_);
}
