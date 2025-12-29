#include "mainwindow.h"
#include "tetrimino.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QPixmap>
#include <QGraphicsPixmapItem>

const int window_width = 320;
const int window_height = 480;
const int tile = 18;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();

    QGraphicsView* view = new QGraphicsView(scene);

    QPixmap image(":/Pictures/images/background.png");
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem();
    background->setPixmap(image);
    background->setScale(1);
    scene->addItem(background);

    tetrimino* tetrisPiece = new tetrimino(tile, 3);
    scene->addItem(tetrisPiece);

    view->show();
    view->setFixedSize(window_width, window_height);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    return a.exec();
}
