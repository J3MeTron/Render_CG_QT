#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

#include <src/line.h>

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

private:
    Ui::Widget                                  *ui;
    QGraphicsScene                              *scene;

    Line                                        *line;
    QList<std::shared_ptr<QGraphicsItem>>       m_objs;
};

#endif // WIDGET_H
