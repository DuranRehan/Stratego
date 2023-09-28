#include "viewfx.h"
#include "controllerFx.h"
#include <QApplication>

using namespace gui;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View v{};
    auto c = ControllerFx(v);
    c.run();
    return a.exec();
}
