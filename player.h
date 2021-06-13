#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

#include "ball.h"

class Player: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Player(QGraphicsScene *scene, Ball *ball, QTimer *timer, int reflect);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void addPauseScreen(QGraphicsRectItem *screen);

public slots:
    void movePlayer();

private:
    Ball *m_ball;
    QTimer *m_timer;
    QGraphicsRectItem *m_pauseScreen;
    int m_reflect;

    bool moveUp;
    bool moveDown;
    double speed;
    double velocity;

    bool isPaused;

    void restart();
    void pause();
};

#endif // PLAYER_H
