#include "gtest/gtest.h"
#include <memory>
#include "../BalloonModelApp/balloonmovement.h"

TEST(Point, Point_test)
{
    Point p(0.0, 0.0);
    EXPECT_NEAR(p.x, 0.0, 1e-5);
    EXPECT_NEAR(p.y, 0.0, 1e-5);
    p.x = -100.5;
    p.y = 125.43;
    EXPECT_NEAR(p.x, -100.5, 1e-5);
    EXPECT_NEAR(p.y, 125.43, 1e-5);
}

TEST(Balloon, Balloon_test)
{
    Balloon balloon(0.0, 0.0);
    EXPECT_NEAR(balloon.location().x, 0.0, 1e-5);
    EXPECT_NEAR(balloon.location().y, 0.0, 1e-5);
    balloon.setLocation(Point(-100.5, 125.43));
    balloon.setForce(Point(0.3, 0.7));
    balloon.setVelocity(Point(25.0, 35.0));
    EXPECT_TRUE(balloon.location() == Point(-100.5, 125.43));
    EXPECT_TRUE(balloon.force() == Point(0.3, 0.7));
    EXPECT_TRUE(balloon.velocity() == Point(25.0, 35.0));
}


class MovementTest : public ::testing::Test
{
protected:

    virtual void SetUp()
    {
        balloons_.push_back(std::make_shared<Balloon>(100.0, 100.0));
        balloons_.push_back(std::make_shared<Balloon>(200.0, 200.0));
        simulation_.setBalloons(balloons_);
    }

    virtual void TearDown() {}

    std::vector<std::shared_ptr<Balloon> > balloons_;
    SimulationMovement simulation_;
};

TEST_F(MovementTest, time0)
{
    simulation_.step();
    auto& balloons = simulation_.balloons();

    EXPECT_TRUE(balloons[0]->location() == Point(100.0, 100.0));
    EXPECT_TRUE(balloons[0]->velocity() == Point(0.0, 0.0));
    EXPECT_TRUE(balloons[0]->force() == Point(0.00496464, 0.00496464));

    EXPECT_TRUE(balloons[1]->location() == Point(200.0, 200.0));
    EXPECT_TRUE(balloons[1]->velocity() == Point(0.0, 0.0));
    EXPECT_TRUE(balloons[1]->force() == Point(-0.00496464, -0.00496464));
}


TEST_F(MovementTest, time10)
{
    simulation_.setTimeStep(100.0);
    simulation_.step(); // time = 0.0;
    simulation_.step(); // time = 100.0;

    auto& balloons = simulation_.balloons();

    EXPECT_TRUE(balloons[0]->location() == Point(149.6464466094, 149.6464466094));
    EXPECT_TRUE(balloons[0]->velocity() == Point(0.992929, 0.992929));
    EXPECT_TRUE(balloons[0]->force() == Point(0.00992929, 0.00992929));

    EXPECT_TRUE(balloons[1]->location() == Point(150.353553390, 150.353553390));
    EXPECT_TRUE(balloons[1]->velocity() == Point(-0.992929, -0.992929));
    EXPECT_TRUE(balloons[1]->force() == Point(-0.00992929, -0.00992929));
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
