#include "widget.h"
#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
