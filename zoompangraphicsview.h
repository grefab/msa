#ifndef ZOOMPANGRAPHICSVIEW_H
#define ZOOMPANGRAPHICSVIEW_H

#include <QGraphicsView>

class ZoomPanGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ZoomPanGraphicsView(QWidget *parent = 0);

signals:
    void enlargeCircle();
    void shrinkCircle();
    void addCircle(QPointF point);
    void removeCircle(QPointF point);

    void showCircle();
    void hideCircle();
    void circlePosChanged(QPointF point);

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    enum class MouseMode {
        Move,
        Interact
    };

private:
    void updateMouseMode(Qt::KeyboardModifiers modifiers);
    void updateCursor();

    QPoint lastMousePos_;
    MouseMode mouseMode_ = MouseMode::Move;
};

#endif // ZOOMPANGRAPHICSVIEW_H
