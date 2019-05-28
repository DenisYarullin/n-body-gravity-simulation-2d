#include "balloonmodel.h"
#include "balloonview.h"

BalloonModel::BalloonModel(): stopped_(false), updated_(false), simulation_(new SimulationMovement()), view_(nullptr)
{
}

BalloonModel::~BalloonModel()
{
    stopped_ = true;
    cv_.notify_one();
    if (th_.joinable())
        th_.join();
}

void BalloonModel::addObserver(BalloonView &view)
{
    view_ = &view;
}

void BalloonModel::simulation()
{
    auto func = [this]()
    {
        for(;;)
        {
            updated_ = false;
            simulation_->step();

            notifyObserver();

            std::unique_lock<std::mutex> lk(mu_);
            cv_.wait(lk, [this]() { return updated_ || stopped_; });

            if (stopped_) return;
        }
    };
    th_ = std::thread(func);
}

void BalloonModel::notifyObserver()
{
    if (view_ != nullptr)
        view_->modelIsChanged();
}

void BalloonModel::setBalloons(std::vector<std::shared_ptr<Balloon>>& balloons)
{
    simulation_->setBalloons(balloons);
}

void BalloonModel::setUpdateFlag(bool flag)
{
    updated_ = flag;
    cv_.notify_one();
}
