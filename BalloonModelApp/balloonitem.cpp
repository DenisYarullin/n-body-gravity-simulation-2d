#include "balloonitem.h"
#include "balloonscene.h"
#include "balloonmovement.h"
#include <QBrush>

BalloonItem::BalloonItem() : QGraphicsEllipseItem(nullptr)
{
    setBrush(Qt::red);
    setRect(-25, -25, 50, 50);
    setFlags(QGraphicsItem::ItemIsMovable);
}
