#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>


class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);

    QGraphicsScene* scene();

signals:
    void fileLoaded();

public slots:
    void loadFile(QString filename);

    void onShowCircle();
    void onHideCircle();
    void onCirclePosChanged(QPointF point);

    void onEnlargeCircle();
    void onShrinkCircle();

    void onAddCircle(QPointF point);
    void onRemoveCircle(QPointF point);

private:
    QGraphicsScene scene_;
    QGraphicsPixmapItem*  imagePixmapItem_;
    QGraphicsPixmapItem*  drawingPixmapItem_;
    QGraphicsEllipseItem* circleItem_;

private:
    QPixmap drawingPixmap_;
    QPointF circleCenter_;
    qreal circleRadius_ = 100;

};

#endif // ENGINE_H
