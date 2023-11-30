#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <cmath>
#include "src/drawable.h"
#include "src/model.h"
#include <QPainter>
#include <src/line.h>


class Render : public Drawable
{
public:
    Render(const int absX, const int absY, Model *model);
    ~Render();

    void rline(int x0, int y0, int x1, int y1, QColor color, QPainter *painter);
    void rotateLeft();
    void drawCoordinateSystem(QPainter *painter);

private:
    const int absX;
    const int absY;
    Model     &model;
    Line      *line;
    std::vector<std::shared_ptr<Drawable>> m_objs;




protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // RENDER_H
