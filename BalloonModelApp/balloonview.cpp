#include "balloonview.h"
#include "balloonitem.h"
#include "balloonscene.h"
#include "balloonmovement.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QTimer>

BalloonView::BalloonView(BalloonController &controller, BalloonModel &model, QWidget *parent)
    : QWidget(parent), updated_(false), controller_(&controller), model_(&model)
{
    QLabel* numberBalloonsLbl = new QLabel(tr("Number of balloons: "), this);
    numberBalloonsLE = new QLineEdit(this);
    numberBalloonsLE->setValidator(new QIntValidator);
    numberBalloonsLE->setText(QString("4"));
    goBtn = new QPushButton(tr("Go"), this);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(numberBalloonsLbl);
    hLayout->addWidget(numberBalloonsLE);
    hLayout->addWidget(goBtn);

    model_->addObserver(*this);

    scene_ = new BalloonScene(this);
    view_ = new QGraphicsView(this);
    view_->setScene(scene_);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(view_);
    setLayout(vLayout);

    resize(QApplication::desktop()->screenGeometry().width() / 2, QApplication::desktop()->screenGeometry().height() / 2);

    connect(goBtn, &QPushButton::clicked, this, &BalloonView::run);

    QTimer* updateTimer = new QTimer(this);
    updateTimer->start(1);
    connect(updateTimer, &QTimer::timeout, this, &BalloonView::update);
}

BalloonView::~BalloonView()
{
}

void BalloonView::run()
{
    setInitialState();
    goBtn->setEnabled(false);
    controller_->run();
}

std::vector<std::shared_ptr<Balloon> > &BalloonView::balloons()
{
    return scene_->balloons();
}

void BalloonView::setInitialState()
{
    scene_->setInitialState(numberBalloonsLE->text().toInt());
}

void BalloonView::update()
{
    if (updated_)
    {
        auto& deletedBallons = scene_->deletedBalloons();
        auto& balloons = scene_->balloons();
        auto movedBalloon = scene_->movedBalloon();

        auto items = scene_->items();

        if (movedBalloon != nullptr)
        {
            auto iter = std::find_if(items.begin(), items.end(), [&](auto& item)
            {
                return item->data(0) == (*movedBalloon).id();
            });

            if (iter != items.end())
            {
                (*movedBalloon).setForce(Point(0.0, 0.0));
                (*movedBalloon).setVelocity(Point(0.0, 0.0));
                (*movedBalloon).setLocation(Point((*iter)->pos().x(), (*iter)->pos().y()));
            }
        }

        if (!deletedBallons.empty())
        {
            for (auto& deletedBalloon: deletedBallons)
            {
                auto iter = std::find_if(balloons.begin(), balloons.end(), [&](auto& balloon)
                {
                    return balloon->id() == (*deletedBalloon).id();
                });
                if (iter != balloons.end())
                {
                    balloons.erase(iter);
                }
            }
            deletedBallons.clear();
        }

        auto iter = scene_->balloons().end();
        for (auto& item: items)
        {
            --iter;
            (*item).setPos((*iter)->location().x, (*iter)->location().y);
        }

        updated_ = false;
        controller_->nextStep();
    }
}

void BalloonView::modelIsChanged()
{
    updated_ = true;
}
