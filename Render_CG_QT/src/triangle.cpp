#include "triangle.h"
#include "math.h"

#include <vector>

triangle::triangle(const int absX, const int absY,
                   QPoint p1, QPoint p2,QPoint p3,
                   QColor colorA, QColor colorB, QColor colorC):
    absX(absX),
    absY(absY),
    p1(p1),
    p2(p2),
    p3(p3),
    colorA(colorA),
    colorB(colorB),
    colorC(colorC)
{

}

triangle::~triangle()
{

}

QRectF triangle::boundingRect() const
{
    return QRectF(-25,-40,50,80);
}




QColor ShadeBackgroundPixel(int x, int y,
                            double x1, double y1,
                            double x2, double y2,
                            double x3, double y3,
                            QColor colorA, QColor colorB, QColor colorC)
{
    QColor pixelColor(Qt::white); // Присваиваем цвет фона - белый

    double l1, l2, l3;


    l1 = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) /
        ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));

    l2 = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) /
        ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));

    l3 = 1 - l1 - l2;

        if (l1 >= 0 && l1 <= 1 && l2 >= 0 && l2 <= 1 && l3 >= 0 && l3 <= 1)
        {
            int red = l1 * colorA.red() + l2 * colorB.red() + l3 * colorC.red();
            int green = l1 * colorA.green() + l2 * colorB.green() + l3 * colorC.green();
            int blue = l1 * colorA.blue() + l2 * colorB.blue() + l3 * colorC.blue();

            pixelColor = QColor(red, green, blue);
        }

    return pixelColor;
}


void triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    for (int y = (absY/2)-absY; y < absY; y++){
        for (int x = (absX/2)-absX; x < absX; x++){
            painter->setPen(QColor(ShadeBackgroundPixel(x, y, p1.rx(), p1.ry(), p2.rx(), p2.ry(), p3.rx(), p3.ry(), colorA, colorB, colorC)));
            painter->drawPoint(x, y);

        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


