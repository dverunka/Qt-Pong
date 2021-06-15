#include <QObject>
#include <QTimer>

#include "ball.h"

Ball::Ball(QGraphicsScene *scene, QTimer *timer)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveBall()));

    setBrush(QBrush(QColor(255, 255, 255, 255)));
    setRect(0, 0, 20, 20);

    scene->addItem(this);

    restart();
}

void Ball::moveBall() {

    // reflect ball from scene boundaries
    if (y() + rect().height() > scene()->height() || y() < 0) {
        yVelocity *= -1;
    }

    // reflect ball from paddle
    if (isReflected) {

        xVelocity *= -1;
        yVelocity += paddleVelocity;
        isReflected = false;
        paddleVelocity = 0;
    }

    setPos(x() + xVelocity, y() + yVelocity);

    // restart position when ball escapes from paddle
    if (x() < 0 || x() + rect().width() > scene()->width()) {
        restart();
    }
}

// add paddle velocity to ball and reflect
void Ball::strike(double yVelocity) {
    isReflected = true;
    paddleVelocity = yVelocity / 2;
}

// restart ball's position and velocity
void Ball::restart() {

    double x = scene()->width() / 2 - rect().width() / 2;
    double y = scene()->height() / 2 - rect().height() / 2;
    setPos(x, y);

    isReflected = false;
    paddleVelocity = 0;
    xVelocity = 10;
    yVelocity = 5;

    emit restartGame();
}
