#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "src/drawable.h"
#include <QPainter>

class triangle : public Drawable
{
public:
    triangle(const int absX, const int absY, QPoint p1, QPoint p2, QPoint p3,
                                                     QColor colorA, QColor colorB, QColor colorC);
    ~triangle();
private:
    const int absX;
    const int absY;
    QPoint p1;
    QPoint p2;
    QPoint p3;
    QColor colorA;
    QColor colorB;
    QColor colorC;

protected:
    QRectF boundingRect() const;    /* Определяем виртуальный метод,
                                     * который возвращает область, в которой
                                     * находится треугольник
                                     * */
    /* Определяем метод для отрисовки треугольника
     * */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);




};

#endif // TRIANGLE_H

