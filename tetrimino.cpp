#include "tetrimino.h"

tetrimino::tetrimino(int tile_size, int colour)
    : tile_size{tile_size}
    , colour{colour}
{
    drawBlocks();

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    int time = 1000;
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveDown()));

    timer->start(time);
}

void
tetrimino::drawBlocks()
{
    QPixmap image(":/Pictures/images/tiles.png");

    QRect recto(colour * tile_size, 0, tile_size, tile_size);
    QPixmap clipped;
    clipped = image.copy(recto);

    for (int i = 0; i < 4; ++i) {
        quad[i].x = figures[colour][i] % 2;
        quad[i].y = figures[colour][i] / 2;
    }

    for (int i = 0; i < 4; ++i) {
        QGraphicsPixmapItem* tet = new QGraphicsPixmapItem();

        tet->setPixmap(clipped);
        tet->setPos(quad[i].x * tile_size, quad[i].y * tile_size);
        this->addToGroup(tet);

        if (1 == i) {
            this->setTransformOriginPoint(quad[i].x * tile_size, quad[i].y * tile_size);
        }
    }

    this->setPos((5 * tile_size) + 9, (0 * tile_size) - 6);

}

void
tetrimino::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        setX(x() - tile_size);
        if (collisionCheck()) {
            this->setX(x() + tile_size);
            return;
        }
    } else if (event->key() == Qt::Key_Right) {
        setX(x() + tile_size);
        if (collisionCheck()) {
            this->setX(x() - tile_size);
            return;
        }
    } else if (event->key() == Qt::Key_Up) {
        setRotation(rotation() + 90);
        if (collisionCheck()) {
            this->setRotation(rotation() - 90);
            return;
        }
    } else if (event->key() == Qt::Key_Down) {
        setY(y() + tile_size);
        if (collisionCheck()) {
            this->setY(y() - tile_size);
            return;
        }
    }
}

bool
tetrimino::collisionCheck()
{
    if (!(sceneBoundingRect().left() > tile_size) ||
        !(sceneBoundingRect().right() < 12 * tile_size) ||
        !(sceneBoundingRect().bottom() < 22 * tile_size))
    {
        qDebug() << "Collision";
        return true;
    } else {
        return false;
    }
}

void
tetrimino::moveDown()
{
    setY(y() + tile_size);
    if (collisionCheck()) {
        this->setY(y() - tile_size);
        return;
    }
}
