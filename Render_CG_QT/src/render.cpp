#include "render.h"

Render::Render(const int absX, const int absY, Model *model): absX(absX),
                                                            absY(absY),
                                                            model(*model)
{

}

Render::~Render()
{

}

QRectF Render::boundingRect() const
{
    return QRectF(-25,-40,50,80);
}


void Render::rline(int x0, int y0, int x1, int y1, QColor color, QPainter *painter)
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

}


void Render::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for (int i=0; i<model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model.vert(face[j]);
            Vec3f v1 = model.vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*absX/2.;
            int y0 = (v0.y+1.)*absY/2.;
            int x1 = (v1.x+1.)*absX/2.;
            int y1 = (v1.y+1.)*absY/2.;
            rline(x0, y0, x1, y1, QColor(250, 0, 0), painter);
        }
    }

    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

