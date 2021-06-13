#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

#include "ball.h"

class Enemy: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Enemy(QGraphicsScene *scene, Ball *ball, QTimer *timer, int reflect);

public slots:
    void moveEnemy();

private:
    Ball *m_ball;
    int m_reflect;

    double velocity;

    void restart();
};

#endif // ENEMY_H
