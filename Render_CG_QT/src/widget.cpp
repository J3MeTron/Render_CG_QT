#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    const int absX = 800;
    const int absY = 800;

    ui->setupUi(this);
    this->resize(absX, absY);          // Задаем размеры виджета, то есть окна
    this->setFixedSize(absX, absY);    // Фиксируем размеры виджета

    scene = new QGraphicsScene();

    line = new Line(0, 0, 200, 200, QColor (255, 0, 0));

    model = new Model("obj/african_head.obj");

    QPainter painter(this);


    render = new Render(absX, absY, model);

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500); // Устанавливаем область графической сцены


    scene->addItem(render);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::addObj(const std::shared_ptr<QGraphicsItem> &obj)
{
    m_objs.push_back(obj);
}
