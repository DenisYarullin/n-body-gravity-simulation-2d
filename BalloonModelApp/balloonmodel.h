#ifndef BALLOONMODEL_H
#define BALLOONMODEL_H

#include <qglobal.h>
#include <memory>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "balloonmovement.h"

QT_BEGIN_NAMESPACE
class BalloonView;
QT_END_NAMESPACE

class BalloonModel
{
public:
    BalloonModel();
    ~BalloonModel();
    void addObserver(BalloonView& view);
    void simulation();
    void setBalloons(std::vector<std::shared_ptr<Balloon>>& balloons);
    void setUpdateFlag(bool flag);

private:
    void notifyObserver();

private:
    std::atomic<bool> stopped_;
    std::atomic<bool> updated_;
    std::unique_ptr<SimulationMovement> simulation_;
    BalloonView* view_;
    std::mutex mu_;
    std::condition_variable cv_;
    std::thread th_;
};

#endif // BALLOONMODEL_H
