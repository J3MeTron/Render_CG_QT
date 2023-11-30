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



void Render::rline(int x0, int y0, int x1, int y1, QColor color, QPainter *painter)
{
    bool steep = std::abs(x0 - x1) < std::abs(y0 - y1);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        int actualX = steep ? y : x;
        int actualY = steep ? x : y;

        painter->setPen(color);
        painter->drawPoint(actualX, actualY);

        error2 += derror2;

        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void Render::triangle(Vec2i t0, Vec2i t1, Vec2i t2, QColor color, QPainter *painter) {
    if (t0.y == t1.y && t0.y == t2.y) return; // I don't care about degenerate triangles
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);
    int total_height = t2.y - t0.y;
    for (int i = 0; i < total_height; i++) {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        float alpha = (float)i / total_height;
        float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height;
        Vec2i A = t0 + (t2 - t0) * alpha;
        Vec2i B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++) {
            painter->setPen(color);
            painter->drawPoint(j, t0.y + i); // Attention, due to int casts t0.y + i != A.y
        }
    }
}

float modelScale = 2.0;

void Render::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
            triangle(screen_coords[0], screen_coords[1], screen_coords[2], QColor(intensity * 255, intensity * 255, intensity * 255), painter);
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

void Render::drawCoordinateSystem(QPainter *painter) {
    // Отрисовка оси X
    rline(-absX, 0, absX, 0, QColor(0, 0, 255), painter);
    // Отрисовка оси Y
    rline(0, -absY, 0, absY, QColor(0, 255, 0), painter);
    // Отрисовка стрелок оси X
    rline(absX - 10, -5, absX, 0, QColor(0, 0, 255), painter);
    rline(absX - 10, 5, absX, 0, QColor(0, 0, 255), painter);
    // Отрисовка стрелок оси Y
    rline(-5, absY - 10, 0, absY, QColor(0, 255, 0), painter);
    rline(5, absY - 10, 0, absY, QColor(0, 255, 0), painter);
}
