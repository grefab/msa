#include "zoompangraphicsview.h"
#include <QWheelEvent>

#include <QGuiApplication>
#include <QDebug>

ZoomPanGraphicsView::ZoomPanGraphicsView(QWidget* parent) :
    QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
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
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
}

void ZoomPanGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if( mouseMode_ == MouseMode::Move ) {
        QGraphicsView::mousePressEvent(event);
    } else {
        lastMousePosition_ = event->pos();
    }
}

void ZoomPanGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if( mouseMode_ == MouseMode::Move ) {
        QGraphicsView::mouseMoveEvent(event);
    } else {
        lastMousePosition_ = event->pos();
    }
}

void ZoomPanGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    if( mouseMode_ == MouseMode::Move ) {
        QGraphicsView::mouseReleaseEvent(event);
    } else {
        lastMousePosition_ = event->pos();
    }
}

void ZoomPanGraphicsView::updateMouseMode(Qt::KeyboardModifiers modifiers)
{
if( modifiers && Qt::ControlModifier ) {
        mouseMode_ = MouseMode::Interact;
    } else {
        mouseMode_ = MouseMode::Move;
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
