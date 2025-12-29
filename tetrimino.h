#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

class tetrimino: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    const int figures[7][4] =
    {
        1, 3, 5, 7,
        2, 4, 5, 7,
        3, 5, 4, 6,
        3, 5, 4, 7,
        2, 3, 5, 7,
        3, 5, 7, 6,
        2, 3, 4, 5,
    };

    struct Point {int x, y;} quad[4];

    int tile_size;
    int colour;

    tetrimino(int tile_size, int colour);

    void drawBlocks();
    void keyPressEvent(QKeyEvent* event);
    bool collisionCheck();

public:
    virtual ~tetrimino() = default;

public slots:
    void moveDown();
};

#endif // TETRIMINO_H
