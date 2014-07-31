#include "zoompangraphicsview.h"
#include <QWheelEvent>

#include <QGuiApplication>
#include <QDebug>

ZoomPanGraphicsView::ZoomPanGraphicsView(QWidget* parent) :
    QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setMouseTracking(true);
}

void ZoomPanGraphicsView::keyPressEvent(QKeyEvent* event)
{
    updateMouseMode(event->modifiers());
}

void ZoomPanGraphicsView::keyReleaseEvent(QKeyEvent* event)
{
    updateMouseMode(event->modifiers());
}

void ZoomPanGraphicsView::wheelEvent(QWheelEvent* event)
{
    switch( mouseMode_ ) {
        case MouseMode::Move: {
            setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            double scaleFactor = 1.15;
            if(event->delta() > 0) {
                /* Zoom in. */
                scale(scaleFactor, scaleFactor);
            } else {
                /* Zoom out. */
                scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            }
        } break;
        case MouseMode::Interact: {
            if(event->delta() > 0) {
                emit enlargeCircle();
            } else {
                emit shrinkCircle();
            }
        } break;
    }

}

void ZoomPanGraphicsView::mousePressEvent(QMouseEvent* event)
{
    lastMousePos_ = event->pos();

    if( mouseMode_ == MouseMode::Move ) {
        QGraphicsView::mousePressEvent(event);
    } else {
        const QPointF imagePos = mapToScene(event->pos());
        if(event->buttons() & Qt::LeftButton ) {
            emit addCircle(imagePos);
        } else if(event->buttons() & Qt::RightButton ) {
            emit removeCircle(imagePos);
        }
    }
}

void ZoomPanGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    lastMousePos_ = event->pos();

    if( mouseMode_ == MouseMode::Move ) {
        QGraphicsView::mouseMoveEvent(event);
    } else {
        const QPointF imagePos = mapToScene(event->pos());
        emit circlePosChanged(imagePos);

        if(event->buttons() & Qt::LeftButton ) {
            emit addCircle(imagePos);
        } else if(event->buttons() & Qt::RightButton ) {
            emit removeCircle(imagePos);
        }
    }
}

void ZoomPanGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    if( mouseMode_ == MouseMode::Move ) {
        QGraphicsView::mouseReleaseEvent(event);
    } else {
    }
}

void ZoomPanGraphicsView::updateMouseMode(Qt::KeyboardModifiers modifiers)
{
    if( modifiers & Qt::ControlModifier ) {
        mouseMode_ = MouseMode::Interact;
        emit circlePosChanged(mapToScene(lastMousePos_));
        emit showCircle();
    } else {
        mouseMode_ = MouseMode::Move;
        emit hideCircle();
    }

    updateCursor();
}

void ZoomPanGraphicsView::updateCursor()
{
    switch( mouseMode_ ) {
        case MouseMode::Move: {
            QGuiApplication::restoreOverrideCursor();
        } break;
        case MouseMode::Interact: {
            QGuiApplication::setOverrideCursor(Qt::CrossCursor);
        } break;
    }
}
