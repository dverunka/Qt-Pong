#include <QObject>
#include <QTimer>

#include "enemy.h"

Enemy::Enemy(QGraphicsScene *scene, Ball *ball, QTimer *timer, int reflect)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveEnemy()));

    m_ball = ball;
    m_reflect = reflect;

    setBrush(QBrush(QColor(255, 255, 255, 255)));
    setRect(0, 0, 20, 200);

    scene->addItem(this);

    restart();
}

void Enemy::moveEnemy() {

    // follow ball's vertical location
    if (m_ball->y() < y()) {
        velocity = m_ball->y() - y();

    } else if (m_ball->y() + m_ball->rect().height() > y() + rect().height()) {
        velocity = m_ball->y() + m_ball->rect().height() - (y() + rect().height());

    } else {
        velocity = 0;
    }

    // max velocity +/-20
    if (velocity > 20) {
        velocity = 20;
    }
    if (velocity < -20) {
        velocity = -20;
    }

    // respect screen boundaries
    if (velocity > scene()->height() - (y() + rect().height())) {
        velocity = scene()->height() - (y() + rect().height());

    } else if (velocity < -y()) {
        velocity = -y();
    }

    // move enemy's paddle
    setPos(x(), y() + velocity);

    // check for collision, and reflect the ball
    if (m_ball->x() > x() && m_ball->x() < x()+rect().width()
            && m_ball->y() + m_ball->rect().height() > y() && m_ball->y() < y()+rect().height()) {

        m_ball->strike(velocity);
    }
}

void Enemy::restart() {

    double x = m_reflect - rect().width() / 2;
    double y = scene()->height() / 2 - rect().height() / 2;
    setPos(x, y);

    velocity = 0;
}
