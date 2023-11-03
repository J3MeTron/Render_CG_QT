#include "line.h"

Line::Line(QPoint p1,QPoint p2, QColor color):
                                              p1(p1),
                                              p2(p2),
                                              color(color)
{

}

Line::~Line()
{

}

QRectF Line::boundingRect() const
{
    return QRectF(-25,-40,50,80);
}


void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(float t=0.; t<1.; t+=.01){
        int x = p1.rx()*(1.-t) + p1.rx()*t;
        int y = p1.ry()*(1.-t) + p2.ry()*t;
        painter->setPen(color);
        painter->drawPoint(x,y);
    }

}


