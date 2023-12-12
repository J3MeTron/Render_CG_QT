#include "render.h"
#include <cstdlib>

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
    return QRectF(-25, -40, 50, 80);
}


float modelScale = 2.0;

void Render::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    class triangle triangleRenderer;
    QTransform originalTransform = painter->transform();
    QTransform transform = originalTransform;
    transform.rotate(-180);  // Поворот на 90 градусов влево
    painter->setTransform(transform);

    // Находим центр экрана
    int centerX = 0;
    int centerY = 0;


    zbuffer = new int[absX*absY];
    for (int i=0; i<absX*absY; i++) {
        zbuffer[i] = std::numeric_limits<int>::min();
    }

    Vec3f light_dir(0, 0, -1);
    for (int i = 0; i < model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model.vert(face[j]);
            // Учитываем масштаб при вычислении экранных координат и центрируем модель
            screen_coords[j] = Vec2i((v.x + 1.) * absX / 2. * modelScale - (centerX + 150*modelScale) ,
                                     (v.y + 1.) * absY / 2. * modelScale - (centerY + 150*modelScale));
            world_coords[j] = v;
        }
        Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0) {
            triangleRenderer.drawTriangle(screen_coords[0], screen_coords[1], screen_coords[2], QColor(intensity * 255, intensity * 255, intensity * 255), painter);
        }
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Render::rotateLeft() {
    QTransform transform;
    transform.rotate(-90);  // Поворот на 90 градусов влево
    setTransform(transform);
}
