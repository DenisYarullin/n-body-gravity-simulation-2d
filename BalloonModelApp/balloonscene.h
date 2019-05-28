#ifndef BALLOONSCENE_H
#define BALLOONSCENE_H

#include <QGraphicsScene>
#include <memory>

QT_BEGIN_NAMESPACE
class BalloonItem;
class Balloon;
QT_END_NAMESPACE

class BalloonScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit BalloonScene(QObject *parent = nullptr);
    std::vector<std::shared_ptr<Balloon>>& balloons();
    std::shared_ptr<Balloon> movedBalloon();
    std::vector<std::shared_ptr<Balloon>>& deletedBalloons();
    void setInitialState(int numberBalloons);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void addBalloon(QPointF);
    void removeBalloon(int id);

signals:
    void addClicked(QPointF);
    void removeClicked(int id);

private:
    int id_ = 0;
    std::shared_ptr<Balloon> balloon_;
    BalloonItem* item_;
    std::shared_ptr<Balloon> movedBalloon_;
    std::vector<std::shared_ptr<Balloon> > deletedBalloons_;
    std::vector<std::shared_ptr<Balloon> > balloons_;
};

#endif // BALLOONSCENE_H
