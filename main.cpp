#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QTimer>

#include "ball.h"
#include "enemy.h"
#include "player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTimer *timer = new QTimer();

    // game scene
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView();

    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0, 255)));

    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // game objects
    Ball *ball = new Ball(scene, timer);
    Enemy *enemy = new Enemy(scene, ball, timer, 25);
    Player *player = new Player(scene, ball, timer, 25);

    // pause screen
    QGraphicsRectItem *pauseScreen = new QGraphicsRectItem();
    pauseScreen->setRect(0, 0, 200, 200);
    pauseScreen->setPos(300, 200);
    pauseScreen->setBrush(QBrush(QColor(255, 255, 255, 255)));

    QGraphicsTextItem *instructions = new QGraphicsTextItem(pauseScreen);
    instructions->setPlainText("move [up] and [down], \npause [space], \nquit game [esc]. \n\ncomputer - left side, \nplayer - right side. \n\nmade by verunka");

    scene->addItem(pauseScreen);
    player->addPauseScreen(pauseScreen);

    // set focus on player's paddle
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // play
    view->setScene(scene);
    view->show();

    return a.exec();
}
