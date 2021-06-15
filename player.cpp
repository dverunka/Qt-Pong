#include <QApplication>
#include <QKeyEvent>
#include <QTimer>

#include "player.h"

Player::Player(QGraphicsScene *scene, Ball *ball, QTimer *timer, int reflect)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(movePlayer()));
    connect(ball, SIGNAL(restartGame()), this, SLOT(pause()));
    connect(ball, SIGNAL(restartGame()), this, SLOT(restart()));

    m_pauseScreen = NULL;
    m_ball = ball;

    m_playerScore = new QGraphicsTextItem();
    m_playerScore->setDefaultTextColor(QColor(255, 255, 255, 255));
    m_playerScore->setPlainText("score: " + QString::number(Player::score));
    m_playerScore->setPos(375, 50);

    scene->addItem(m_playerScore);

    m_reflect = reflect;
    m_timer = timer;

    isPaused = true;

    setBrush(QBrush(QColor(255, 255, 255, 255)));
    setRect(0, 0, 20, 200);

    scene->addItem(this);

    restart();
}

// move with the player's paddle
void Player::movePlayer() {

    // respond to arrow keys
    if (moveUp) {
        velocity = -speed;

    } else if (moveDown) {
        velocity = speed;

    } else velocity = 0;

    // respect screen boundaries
    if (velocity > scene()->height() - (y() + rect().height())) {
        velocity = scene()->height() - (y() + rect().height());

    } else if (velocity < -y()) {
        velocity = -y();
    }

    // move player's paddle
    setPos(x(), y() + velocity);

    // check for collision, and reflect the ball
    if (m_ball->x() + m_ball->rect().width() > x() && m_ball->x() + m_ball->rect().width() < (x() + rect().width())
            && m_ball->y() + m_ball->rect().height() > y() && m_ball->y() < (y() + rect().height())) {

        m_ball->strike(velocity);

        // update score
        score++;
        m_playerScore->setPlainText("score: " + QString::number(Player::score));
    }
}

// restart player position
void Player::restart() {

    double x = scene()->width() - m_reflect - rect().width() / 2;
    double y = scene()->height() / 2 - rect().height() / 2;

    setPos(x, y);

    moveUp = false;
    moveDown = false;

    speed = 20;
    score = 0;
    velocity = 0;

    m_playerScore->setPlainText("score: -");
}

// pause screen
void Player::addPauseScreen(QGraphicsRectItem *screen) {
    m_pauseScreen = screen;
}

// react to player's key press
void Player::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {

        // arrow up -> up
        case Qt::Key_Up: {
            moveUp = true;
            moveDown = !moveUp;
            break;
        }

        // arrow down -> down
        case Qt::Key_Down: {
            moveDown = true;
            moveUp = !moveDown;
            break;
        }

        // esc -> quit
        case Qt::Key_Escape: {
            QApplication::quit();
            break;
        }

        // space -> pause
        case Qt::Key_Space: {
            pause();
            break;
        }

        default: {}
    }
}

// key released
void Player::keyReleaseEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Up && moveUp) {
        moveUp = false;

    } else if (event->key() == Qt::Key_Down && moveDown) {
        moveDown = false;
    }
}

void Player::pause() {

    if (isPaused) {
        // hide pause screen
        if (m_pauseScreen != NULL) {
            m_pauseScreen->setVisible(false);
        }
        isPaused = false;

        // restart global timer
        m_timer->start(50);

    } else {
        // show pause screen
        if (m_pauseScreen != NULL) {
            m_pauseScreen->setVisible(true);
        }
        isPaused = true;

        // stop global timer
        m_timer->stop();
    }
}
