#include "engine.h"
#include <qDebug>

#include <QPolygonF>
#include "boost/polygon/gtl.hpp"
#include "boost/polygon/voronoi.hpp"

#include <QGraphicsPolygonItem>

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
        points.push_back(Point(0, 0));
        points.push_back(Point(1, 6));
        std::vector<Segment> segments;
        segments.push_back(Segment(Point(-4, 5), Point(5, -1)));
        segments.push_back(Segment(Point(3, -11), Point(13, -1)));

        boost::polygon::construct_voronoi(points.begin(), points.end(), segments.begin(), segments.end(), &vd);
    }

    {
        qDebug() << "iterating...";
        for( VoronoiDiagram::const_edge_iterator it = vd.edges().begin();
             it != vd.edges().end(); ++it ) {
            if( it->is_primary() ) {
                qDebug() << "Primary edge found!";
            } else {
                qDebug() << "Secondary edge found!";
            }
        }
        qDebug() << "done.";
    }
}
