#ifndef LINE_H
#define LINE_H

#include "src/drawable.h"
#include <QPainter>

class Line : public Drawable
{
public:
    Line(int x0, int y0, int x1, int y1, QColor color);
    ~Line();
private:
    int x0;
    int y0;
    int x1;
    int y1;

    QColor color;

protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // LINE_H
