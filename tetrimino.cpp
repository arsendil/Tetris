#include "tetrimino.h"

tetrimino::tetrimino(const int pix_l, int colour, board *gameboard): pix_l{pix_l}, colour{colour}, gameboard{gameboard}
{
    drawBlocks();

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    int time = 1000 - (gameboard->score*10);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moveDown()));

    timer->start(time);
}

void
tetrimino::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        setX(x()-pix_l);
        if(collisionSide()) {
            this->setX(x()+pix_l);
            return;
        }
    } else if (event->key() == Qt::Key_Right) {
        setX(x()+pix_l);
        if(collisionSide()) {
            this->setX(x()-pix_l);
            return;
        }
    } else if (event->key() == Qt::Key_Up) {
        setRotation(rotation()+90);
        if(collisionSide()) {
            this->setRotation(rotation()-90);
            return;
        }
    } else if (event->key() == Qt::Key_Down) {
        setPos(x(),y()+pix_l);
        if(collisionSide()) {
            setY(y()-pix_l);
            setToBoard();
            return;
        }
    }
}

void
tetrimino::drawBlocks()
{
    QRect recto(pix_l*colour, 0, pix_l, pix_l);
    QPixmap image(":/Pictures/images/tiles.png");
    QPixmap copy ;
    copy = image.copy(recto);
    int n = colour;
    for (int i = 0; i <4; i++) {
        quad[i].x= figures[n][i] % 2;
        quad[i].y= figures[n][i] / 2;
    }
    for (int i=0; i <4; i++) {
        QGraphicsPixmapItem * tet = new QGraphicsPixmapItem();
        tet->setPixmap(copy);
        tet->setPos(quad[i].x*pix_l,quad[i].y*pix_l);
        this->addToGroup(tet);
        if(i==1) {
            this->setTransformOriginPoint(quad[i].x*pix_l,quad[i].y*pix_l);
        }
    }
    this->setPos((-4*pix_l)+12,(-14*pix_l+9));
}

void
tetrimino::moveDown()
{
    if(this->sceneBoundingRect().bottom()<190) {
        setY(this->y()+pix_l);
        if(collisionSide()) {
            setY(this->y()-pix_l);
            setToBoard();
            return;
        }
    } else {
        setToBoard();
        return;
    }
}

void
tetrimino::setToBoard()
{
    this->clearFocus();
    for(int i = 0; i<4; i++) {
        gameboard->addToGroup(this->childItems().first());
    }
    if (!gameboard->gameOver()) {
        int rand_colour = rand() % 6;
        tetrimino *teto = new tetrimino(pix_l,rand_colour,gameboard);
        scene()->addItem(teto);
        delete this;
        gameboard->checkLoop();
    } else {
        delete this;
    }
}

bool
tetrimino::collisionSide()
{
    if(!(sceneBoundingRect().left()>-144) || !(sceneBoundingRect().right()<54) || !(sceneBoundingRect().bottom()<189)) {
        return true;
    }
    for(int i = 0; i<gameboard->childItems().length(); i++) {
        if(gameboard->childItems().isEmpty()) {
            return true;
        } else {
            for(int j = 0; j <4; j++) {
                if(this->childItems()[j]->collidesWithItem(gameboard->childItems()[i])) {
                    return true;
                }
            }
        }
    }
    return false;
}
