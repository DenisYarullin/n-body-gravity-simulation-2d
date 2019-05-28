#ifndef BALLOONMOVEMENT_H
#define BALLOONMOVEMENT_H

#include <vector>
#include <memory>
#include <cmath>

const double maxDistance = 1e-5;

struct Point
{
    double x;
    double y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    friend bool operator== (const Point& lhs, const Point& rhs)
    {
        return fabs(lhs.x - rhs.x) < maxDistance && fabs(lhs.y - rhs.y) < maxDistance;
    }
};

class Balloon
{
public:
    Balloon(Point location);
    Balloon(double xLocation, double yLocation);
    ~Balloon() = default;

    int id() const;
    Point force() const;
    Point velocity() const;
    Point location() const;

    void setForce(Point force);
    void setVelocity(Point velocity);
    void setLocation(Point location);
    void setId(int id);

private:
    int id_;
    Point location_;
    Point force_;
    Point velocity_;
};

class SimulationMovement
{
public:
    SimulationMovement() = default;
    explicit SimulationMovement(std::vector<std::shared_ptr<Balloon>>& balloons);
    void step();
    void setBalloons(std::vector<std::shared_ptr<Balloon>>& balloons);
    std::vector<std::shared_ptr<Balloon>>& balloons();
    void setBeginTime(double time);
    void setTimeStep(double timeStep);

private:
    double time_ = 0.0;
    double timeStep_ = 1e-5;

    void updateForce(Balloon& balloon1, Balloon& balloon2);
    double calculateForce(double distance) const;
    double calculateDistance(const Balloon& balloon1, const Balloon& balloon2) const;

private:
    std::vector<std::shared_ptr<Balloon>> balloons_;
};

#endif // BALLOONMOVEMENT_H
