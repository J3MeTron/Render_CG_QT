#include "line.h"

Line::Line(int x0, int y0, int x1, int y1, QColor color):
                                              x0(x0),
                                              y0(y0),
                                              x1(x1),
                                              y1(y1),
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
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            painter->setPen(color);
            painter->drawPoint(x,y);
        } else {
            painter->setPen(color);
            painter->drawPoint(x,y);
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}



