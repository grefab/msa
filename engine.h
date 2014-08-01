#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPixmap>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);

    QGraphicsScene* scene();

private:
    QGraphicsScene scene_;
};

#endif // ENGINE_H
