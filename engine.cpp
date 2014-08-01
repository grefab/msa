#include "engine.h"
#include <qDebug>

#include <QPolygonF>
#include "boost/polygon/gtl.hpp"
#include "boost/polygon/voronoi.hpp"

#include <QGraphicsPolygonItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    lab();
}

QGraphicsScene*  Engine::scene()
{
    return &scene_;
}

void Engine::lab()
{
    QPolygonF sourcePolygon;
    {
        sourcePolygon << QPointF( 30,  30);
        sourcePolygon << QPointF(-10,  40);
        sourcePolygon << QPointF(-30,  10);
        sourcePolygon << QPointF(-30, -10);
        sourcePolygon << QPointF(-10, -20);

        scene_.addPolygon(sourcePolygon, QPen(Qt::red), QBrush(Qt::NoBrush));
    }


    typedef boost::polygon::voronoi_diagram<double> VoronoiDiagram;
    VoronoiDiagram vd;
    {
        typedef boost::polygon::point_data<int> Point;
        typedef boost::polygon::segment_data<int> Segment;

        std::vector<Point> points;
        std::vector<Segment> segments;

        for( const QPointF& p : sourcePolygon ) {
            points.push_back(Point(p.x(), p.y()));
        }

        boost::polygon::construct_voronoi(points.begin(), points.end(), segments.begin(), segments.end(), &vd);
    }

    {
        qDebug() << "iterating...";
        for( VoronoiDiagram::const_edge_iterator it = vd.edges().begin(); it != vd.edges().end(); ++it ) {
            const VoronoiDiagram::vertex_type *v0 = it->vertex0();
            const VoronoiDiagram::vertex_type *v1 = it->vertex1();

            if( v0 ) {
                scene_.addEllipse(v0->x() - 5,
                                  v0->y() - 5,
                                  10,
                                  10,
                                  QPen(Qt::blue),
                                  QBrush(Qt::NoBrush));
            }

            if( v1 ) {
                scene_.addEllipse(v1->x() - 5,
                                  v1->y() - 5,
                                  10,
                                  10,
                                  QPen(Qt::blue),
                                  QBrush(Qt::NoBrush));
            }

            if( it->is_primary() ) {
                qDebug() << "Primary edge found!";

                if( v0 && v1 ) {
                    scene_.addLine(v0->x(),
                                   v0->y(),
                                   v1->x(),
                                   v1->y(),
                                   QPen(Qt::black));
                } else {
                    qDebug() << "omitted line";
                }
            } else {
                qDebug() << "Secondary edge found!";
                if( v0 && v1 ) {
                    scene_.addLine(v0->x(),
                                   v0->y(),
                                   v1->x(),
                                   v1->y(),
                                   QPen(Qt::green));
                } else {
                    qDebug() << "omitted line";
                }
            }
        }
        qDebug() << "done.";
    }
}
