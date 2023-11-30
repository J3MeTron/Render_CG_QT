    #include "widget.h"
    #include "ui_widget.h"
    #include <QPainter>

    Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget)
    {

        QString workingDir = QDir::currentPath();
        qDebug() << "Work dir: " << workingDir;


        const int absX = 900;
        const int absY = 900;

        ui->setupUi(this);
        this->resize(absX, absY);          // Задаем размеры виджета, то есть окна
        this->setFixedSize(absX, absY);    // Фиксируем размеры виджета

        scene = new QGraphicsScene();

        line = new Line(0, 0, 200, 200, QColor (255, 0, 0));

        model = new Model("m1.obj");

        QPainter painter(this);


        render = new Render(absX/3, absY/3, model);

        //render->rotateLeft();

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
