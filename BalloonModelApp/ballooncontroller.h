#ifndef BALLOONCONTROLLER_H
#define BALLOONCONTROLLER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class BalloonModel;
class BalloonView;
QT_END_NAMESPACE

class BalloonController : public QObject
{
    Q_OBJECT

public:
    BalloonController(BalloonModel& model);
    void run();
    void nextStep();

private:
    BalloonModel* model_;
    BalloonView* view_;
};

#endif // BALLOONCONTROLLER_H
