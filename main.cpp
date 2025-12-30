#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

#include "tetrimino.h"

const int window_width = 320;
const int window_height = 480;
const int pix_l = 18;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene * scene = new QGraphicsScene();

    QPixmap image(":/Pictures/images/background.png");
    QGraphicsPixmapItem * back = new QGraphicsPixmapItem();
    back->setPixmap(image);
    back->setScale(1);
    back->setPos(-160, -220);
    scene->addItem(back);

    board *gameBoard = new board(pix_l);
    tetrimino *tetgroup = new tetrimino(pix_l, 6, gameBoard);

    scene->addItem(tetgroup);
    scene->addItem(gameBoard);

    QGraphicsView * view = new QGraphicsView(scene);

    view->show();
    view->setFixedWidth(window_width);
    view->setFixedHeight(window_height);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    return a.exec();
}
