#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QGraphicsItem>
#include <QPainter>

class Drawable : public QGraphicsItem
{
public:
    Drawable();
    ~Drawable();

protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // DRAWABLE_H


