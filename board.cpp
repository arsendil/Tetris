#include "board.h"



board::board(int pix_l): pix_l {pix_l}
{
    score = 0;
    min = pix_l*(-11);
    max = pix_l*(10);

    drawScore();
}


void
board::checkLines(QGraphicsLineItem *checkLine)
{
    QList<QGraphicsItem *> colliding_items;
    //QList<QGraphicsItem *> items_above;

    if (checkLine->collidingItems().count()==12) {
        for (int i = 0; i < this->childItems().count(); i++) {
            if(this->childItems()[i]->collidesWithItem(checkLine)) {
                colliding_items.append(this->childItems()[i]);
            } else if(this->childItems()[i]->y()<checkLine->boundingRect().y()) {
                //items_above.append(this->childItems()[i]);
                this->childItems()[i]->setY(this->childItems()[i]->y()+pix_l);
            }
        }

        for (int i = 0; i<colliding_items.length();i++) {
            delete colliding_items[i];
        }

        scoreUpdate();
    }
}

void
board::scoreUpdate()
{
    this->score++;
    delete scoretext;
    drawScore();
}

void
board::checkLoop()
{

    for (int i= min; i <= max; i+=pix_l) {
        QGraphicsLineItem *checkLine = new QGraphicsLineItem();
        checkLine->setLine(-160,i,150,i);
        //checkLine->setY(i);
        checkLine->setVisible(false);
        //qDebug()<<"ypos of checkLine"<<checkLine->y();

        scene()->addItem(checkLine);

        this->checkLines(checkLine);

        delete checkLine;
    }
}

bool
board::gameOver()
{
    for (int i = 0; i < this->childItems().count(); i++) {
        //qDebug()<<this->childItems()[i]->type();
        if(this->childItems()[i]->y()<min) {
            delete scoretext;
            drawLoss();
            return true;
        }
    }
    return false;
}

void
board::drawScore()
{
    scoretext = new QGraphicsTextItem();
    scoretext->setFont(QFont("comic",16));
    scoretext->setDefaultTextColor(Qt::black);
    scoretext->setPlainText(QString("Score: ") + QString::number(this->score));
    scoretext->setPos(0,200);
    this->addToGroup(scoretext);
}

void
board::drawLoss()
{
    scoretext = new QGraphicsTextItem();
    scoretext->setFont(QFont("comic",16));
    scoretext->setDefaultTextColor(Qt::black);
    scoretext->setPlainText(QString("You lose!"));
    scoretext->setPos(0,200);
    this->addToGroup(scoretext);
}
