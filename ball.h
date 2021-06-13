#ifndef BALL_H
#define BALL_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

class Ball: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Ball(QGraphicsScene *scene, QTimer *timer);

    void setVelocity(double, double);
    void strike(double);

public slots:
    void moveBall();

private:
    double xVelocity;
    double yVelocity;
    double paddleVelocity;
    bool isReflected;

    void restart();
};

#endif // BALL_H
