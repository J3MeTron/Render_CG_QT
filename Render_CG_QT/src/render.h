#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <cmath>
#include "src/drawable.h"
#include "src/model.h"
#include <QPainter>
#include <src/line.h>
#include <limits>
#include "triangle.h"


class Render : public Drawable
{
public:
    Render(const int absX, const int absY, Model *model);
    ~Render();

    void triangle(Vec2i t0, Vec2i t1, Vec2i t2, QColor color, QPainter *painter);
    void rline(int x0, int y0, int x1, int y1, QColor color, QPainter *painter);
    void rotateLeft();
    void drawCoordinateSystem(QPainter *painter);



private:
    const int absX;
    const int absY;
    int *zbuffer = NULL;
    Model     &model;
    Line      *line;
    std::vector<std::shared_ptr<Drawable>> m_objs;



protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // RENDER_H
