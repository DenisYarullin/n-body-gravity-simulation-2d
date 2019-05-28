#include "balloonview.h"
#include <QApplication>
#include "balloonmodel.h"
#include "ballooncontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BalloonModel model;
    BalloonController controller(model);

    Q_UNUSED(controller);

    return a.exec();
}
