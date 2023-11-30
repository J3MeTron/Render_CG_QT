#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#include <src/line.h>
#include <src/model.h>
#include <src/render.h>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void addObj(const std::shared_ptr<QGraphicsItem> &obj);
    void rline(int x0, int y0, int x1, int y1, QColor color, QPainter *painter);

private:
    Ui::Widget                                  *ui;
    QGraphicsScene                              *scene;

    Render                                      *render;
    Model                                       *model;
    Line                                        *line;
    QList<std::shared_ptr<QGraphicsItem>>       m_objs;
};

#endif // WIDGET_H
