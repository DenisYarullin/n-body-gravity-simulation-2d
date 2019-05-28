#include "ballooncontroller.h"
#include "balloonview.h"
#include "balloonmodel.h"

BalloonController::BalloonController(BalloonModel& model): model_(&model)
{
    view_ = new BalloonView(*this, model);
    view_->show();
}

void BalloonController::run()
{
    model_->setBalloons(view_->balloons());
    model_->simulation();
}

void BalloonController::nextStep()
{
    model_->setBalloons(view_->balloons());
    model_->setUpdateFlag(true);
}
