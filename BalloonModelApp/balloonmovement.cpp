#include "balloonmovement.h"

SimulationMovement::SimulationMovement(std::vector<std::shared_ptr<Balloon> >& balloons)
    : balloons_(balloons) { }

void SimulationMovement::step()
{
    if (balloons_.size() >= 2)
    {
        for (auto i = balloons_.begin(); i != balloons_.end() - 1; ++i)
        {
            for (auto j = i + 1; j !=  balloons_.end(); ++j)
                updateForce(*(*i), *(*j));
        }

        for (auto& balloon: balloons_)
        {
            double x = balloon->location().x + balloon->velocity().x * time_ + balloon->force().x * time_ * time_ * 0.5;
            double y = balloon->location().y + balloon->velocity().y * time_ + balloon->force().y * time_ * time_ * 0.5;

            balloon->setVelocity(Point(balloon->velocity().x + balloon->force().x * time_,
                                       balloon->velocity().y + balloon->force().y * time_));
            balloon->setLocation(Point(x, y));
        }

        time_ += timeStep_;
    }
    else if (balloons_.size() == 1)
    {
        balloons_[0]->setVelocity(Point(0.0, 0.0));
        time_ = 0.0;
    }
}

void SimulationMovement::updateForce(Balloon& balloon1, Balloon& balloon2)
{
    auto distance = calculateDistance(balloon1, balloon2);

    //if (distance < 1e-3) distance = 1e-3;

    auto force = calculateForce(distance);

    if (fabs(force) > 10.0)
        force = (force > 10.0) ? 10.0 : -10.0; // need sgn function

    double sinAlfa = fabs(balloon2.location().y - balloon1.location().y) / distance;
    double cosAlfa = fabs(balloon2.location().x - balloon1.location().x) / distance;

    auto forceX = force * cosAlfa;
    auto forceY = force * sinAlfa;

    if (balloon2.location().x < balloon1.location().x)
        forceX = -forceX;
    if (balloon2.location().y < balloon1.location().y)
        forceY = -forceY;

    balloon1.setForce(Point(balloon1.force().x + forceX, balloon1.force().y + forceY));
    balloon2.setForce(Point(balloon2.force().x - forceX, balloon2.force().y - forceY));
}

void SimulationMovement::setBalloons(std::vector<std::shared_ptr<Balloon> > &balloons)
{
    for (auto& balloon: balloons)
        balloon->setForce(Point(0.0, 0.0));

    balloons_ = balloons;
}

double SimulationMovement::calculateForce(double distance) const
{
    return 1.0 / distance - 1.0 / (distance * distance);
}

double SimulationMovement::calculateDistance(const Balloon &ballon1, const Balloon &ballon2) const
{
    return sqrt(pow(ballon2.location().x - ballon1.location().x, 2.0) + pow(ballon2.location().y - ballon1.location().y, 2.0));
}

std::vector<std::shared_ptr<Balloon>>& SimulationMovement::balloons()
{
    return balloons_;
}

void SimulationMovement::setBeginTime(double time)
{
    time_ = time;
}

void SimulationMovement::setTimeStep(double timeStep)
{
    timeStep_ = timeStep;
}

Balloon::Balloon(Point location) : location_(location) {}

Balloon::Balloon(double xLocation, double yLocation) : location_(xLocation, yLocation) {}

Point Balloon::force() const
{
    return force_;
}

Point Balloon::velocity() const
{
    return velocity_;
}

void Balloon::setForce(Point force)
{
    force_ = force;
}

void Balloon::setVelocity(Point velocity)
{
    velocity_ = velocity;
}

Point Balloon::location() const
{
    return location_;
}

void Balloon::setLocation(Point location)
{
    location_ = location;
}

int Balloon::id() const
{
    return id_;
}

void Balloon::setId(int id)
{
    id_ = id;
}
