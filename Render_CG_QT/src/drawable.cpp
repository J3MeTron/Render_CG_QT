#include "drawable.h"

Drawable::Drawable() :
    QGraphicsItem()
{

}

Drawable::~Drawable()
{

}

QRectF Drawable::boundingRect() const
{
    return QRectF(-25,-40,50,80);   // Ограничиваем область, в которой лежит треугольник
}

void Drawable::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
