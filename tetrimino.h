#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QRect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QList>

#include "board.h"

class tetrimino: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    const int figures[7][4] =
        {
            1,3,5,7, // I
            2,4,5,7, // Z
            3,5,4,6, // S
            3,5,4,7, // T
            2,3,5,7, // L
            3,5,7,6, // J
            2,3,4,5, // O
        };

    struct Point {int x,y;} quad[4];

public:
    int pix_l;
    int colour;
    bool isActive;

public:
    tetrimino(int pix_l, int colour, board *gameboard);
    board *gameboard;
    void drawBlocks();
    void keyPressEvent(QKeyEvent * event);
    void setToBoard();

    bool collisionSide();

public slots:
    void moveDown();
};

#endif // NEWTETROMINO_H
