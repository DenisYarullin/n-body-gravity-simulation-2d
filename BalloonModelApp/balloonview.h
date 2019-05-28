#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <balloonmodel.h>
#include <ballooncontroller.h>
#include <atomic>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLineEdit;
class BalloonScene;
class QGraphicsView;
QT_END_NAMESPACE

class BalloonView : public QWidget
{
    Q_OBJECT

public:
    explicit BalloonView(BalloonController& controller, BalloonModel& model, QWidget *parent = nullptr);
    ~BalloonView();
    std::vector<std::shared_ptr<Balloon> > &balloons();
    void setInitialState();

public slots:
    void update();
    void run();
    void modelIsChanged();

signals:
    void updated();

private:
    std::atomic_bool updated_;
    BalloonController* controller_;
    BalloonModel* model_;
    BalloonScene* scene_;

    QPushButton* goBtn;
    QLineEdit* numberBalloonsLE;
    QGraphicsView* view_;
};

#endif // WIDGET_H
