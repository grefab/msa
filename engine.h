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

    void loadFile(const QString& filename);

public slots:
    void onShowCircle();
    void onHideCircle();
    void onCirclePosChanged(QPointF point);

    void onEnlargeCircle();
    void onShrinkCircle();

private:
    QGraphicsScene scene_;
    QGraphicsPixmapItem*  pixmap_;
    QGraphicsEllipseItem* circle_;

private:
    qreal circleDiameter_ = 100;
};

#endif // ENGINE_H
