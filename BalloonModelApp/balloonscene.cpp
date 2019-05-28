#include "balloonscene.h"
#include "balloonitem.h"
#include "balloonmovement.h"
#include <QGraphicsSceneMouseEvent>
#include <QTransform>
#include <algorithm>

BalloonScene::BalloonScene(QObject *parent)
    : QGraphicsScene(parent)
{
    connect(this, &BalloonScene::addClicked, this, &BalloonScene::addBalloon);
    connect(this, &BalloonScene::removeClicked, this, &BalloonScene::removeBalloon);
}

void BalloonScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        auto pos =  event->scenePos();
        auto item = itemAt(pos, QTransform());
        if (item != nullptr)
        {
            auto id = item->data(0);
            emit removeBalloon(id.toInt());
            removeItem(item);
        }
        else
        {
            item_ = new BalloonItem;
            item_->setData(0, ++id_);
            addItem(item_);
            item_->setPos(pos);
            emit addBalloon(pos);
        }
    }
    else if (event->button() == Qt::LeftButton)
    {
        auto pos =  event->scenePos();
        auto item = itemAt(pos, QTransform());
        if (item != nullptr)
        {
            auto id = item->data(0);
            auto iter = std::find_if(balloons_.begin(), balloons_.end(), [id](auto& balloon)
            {
                return id == balloon->id();
            });
            if (iter != balloons_.end())
                 movedBalloon_ = *iter;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void BalloonScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void BalloonScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    movedBalloon_ = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

void BalloonScene::addBalloon(QPointF pos)
{
    balloon_= std::make_shared<Balloon>(pos.x(), pos.y());
    balloon_->setId(id_);
    balloons_.push_back(balloon_);
}

void BalloonScene::removeBalloon(int id)
{
    auto iter = std::find_if(balloons_.begin(), balloons_.end(), [id](auto& balloon)
    {
        return id == balloon->id();
    });
    if (iter != balloons_.end())
        deletedBalloons_.push_back(*iter);
}

std::vector<std::shared_ptr<Balloon> > &BalloonScene::balloons()
{
    return balloons_;
}

std::shared_ptr<Balloon> BalloonScene::movedBalloon()
{
    return movedBalloon_;
}

std::vector<std::shared_ptr<Balloon> > &BalloonScene::deletedBalloons()
{
    return deletedBalloons_;
}

void BalloonScene::setInitialState(int numberBalloons)
{
    for (auto i = 0; i < numberBalloons; ++i)
    {
        item_ = new BalloonItem;
        item_->setData(0, ++id_);
        addItem(item_);
        auto x = sceneRect().x() + qrand() % static_cast<int>(sceneRect().width());
        auto y = sceneRect().y() + qrand() % static_cast<int>(sceneRect().height());
        item_->setPos(x, y);
        balloon_ = std::make_shared<Balloon>(x, y);
        balloon_->setId(id_);
        balloons_.push_back(balloon_);
    }
}
