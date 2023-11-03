#ifndef LINE_H
#define LINE_H

#include "src/drawable.h"
#include <QPainter>

class Line : public Drawable
{
public:
    Line(QPoint p1, QPoint p2, QColor color);
    ~Line();
private:
    QPoint p1;
    QPoint p2;
    QColor color;

protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // LINE_H
