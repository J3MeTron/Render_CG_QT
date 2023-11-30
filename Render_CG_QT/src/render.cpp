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

void Render::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QTransform originalTransform = painter->transform();
    QTransform transform = originalTransform;
    transform.rotate(-180);  // Поворот на 90 градусов влево
    painter->setTransform(transform);

    drawCoordinateSystem(painter);

    for (int i = 0; i < model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model.vert(face[j]);
            Vec3f v1 = model.vert(face[(j+1)%3]);

            std::cout << "Before Rotation: v0(" << v0.x << ", " << v0.y << "), v1(" << v1.x << ", " << v1.y << ")" << std::endl;

            int x0 = static_cast<int>(v0.x * absX / 2.0);
            int y0 = static_cast<int>(v0.y * absY / 2.0);
            int x1 = static_cast<int>(v1.x * absX / 2.0);
            int y1 = static_cast<int>(v1.y * absY / 2.0);

            // Выводим координаты вершин перед отрисовкой
            std::cout << "Before Line Drawing: v0(" << v0.x << ", " << v0.y << "), v1(" << v1.x << ", " << v1.y << ")" << std::endl;

            // Отрисовка линии
            rline(x0, y0, x1, y1, QColor(250, 0, 0), painter);

            // Выводим координаты вершин после отрисовки
            std::cout << "After Line Drawing: x0(" << x0 << ", " << y0 << "), x1(" << x1 << ", " << y1 << ")" << std::endl;
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
    rline(absX - 10,  5, absX, 0, QColor(0, 0, 255), painter);
    // Отрисовка стрелок оси Y
    rline(-5, absY - 10, 0, absY, QColor(0, 255, 0), painter);
    rline( 5, absY - 10, 0, absY, QColor(0, 255, 0), painter);
}
