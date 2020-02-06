#include "piecesholder.h"

PiecesHolder::PiecesHolder(int w, int h)
{
    width = w;
    heigth = h;
    blockSize = w/10;   // jednostka miary, kwadrat jest 1bS/1bS

    realWidth = w/blockSize;
    realHeigth = h/blockSize;

    piece = myPiece(w,h,blockSize);

    init = false;
    getNewPiece = false;

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<15;j++)
        {
            placedTab[i][j] = 0;
        }
    }


    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateHolder()));
    timer->start(500);

}

void PiecesHolder::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        piece.rotate();
       // for(int i=0;i<4;i++)
       // {
            //kwadrat[i] = new QGraphicsRectItem();
            //kwadrat[i]->setRect(piece.getX(i)*blockSize ,piece.getY(i)*blockSize,blockSize,blockSize);
          //  scene()->addItem(kwadrat[i]);
       // }
        updateRects();
    }
    if(event->key() == Qt::Key_Left)
    {
       moveRectsLeft();
    }

    else if(event->key() == Qt::Key_Right)
    {
       moveRectsRight();
    }

    else if(event->key() == Qt::Key_Down)
    {
       moveRectsDown();
    }

    else if(event->key() == Qt::Key_Space)
    {
        drawRects();
    }


}

void PiecesHolder::drawRects()
{ //400x600
    piece = myPiece(width,heigth,blockSize);
    pieceCordX = width/2 + blockSize;
    pieceCordY = 0;
    qDebug() << pieceCordX << pieceCordY;
    for(int i=0;i<4;i++)
    {
        kwadrat[i] = new QGraphicsRectItem();
        //kwadrat[i]->setRect(piece.getX(i)*blockSize + pieceCordX ,piece.getY(i)*blockSize + pieceCordY,blockSize,blockSize);
        kwadrat[i]->setRect(pieceCordX+piece.getX(i)*blockSize,pieceCordY+piece.getY(i)*blockSize - piece.findMinY()*40,blockSize,blockSize);
        scene()->addItem(kwadrat[i]);
    }
    init = true;
}

void PiecesHolder::moveRectsDown()
{

    for(int i=0;i<4;i++)
    {

        if(  ( kwadrat[i]->y() + (-(piece.findMinY() - (piece.findMaxY() + 1)) * blockSize) ) < heigth)
        {
        kwadrat[i]->moveBy(0,blockSize);

            qDebug() << "X: " << kwadrat[i]->rect().x() << kwadrat[i]->x()<< "Y: " << kwadrat[i]->rect().y() << kwadrat[i]->y();
            qDebug() << "X: " << ( (kwadrat[i]->rect().x() - 200)/blockSize) << (kwadrat[i]->x())/blockSize<< "Y: " << (kwadrat[i]->rect().y())/blockSize << (kwadrat[i]->y())/blockSize;
            qDebug() << " ";
        getNewPiece = false;
        }
        else
        {
         getNewPiece = true;
        }


        if(//znaleziono w tablicy 1 na polu ponizej klocka z miny)
            placedTab[][qMax(kwadrat[i]->rect().y(),kwadrat[i]->rect())])
                )
        {

        }
    }

}

void PiecesHolder::moveRectsRight()
{
    for(int i=0;i<4;i++)
    {
        if(  (kwadrat[i]->x() + blockSize*piece.findMaxX()) < 120   )
        kwadrat[i]->moveBy(blockSize,0);
    }
}

void PiecesHolder::moveRectsLeft()
{
    for(int i=0;i<4;i++)
    {
        if(  (kwadrat[i]->x() + blockSize*piece.findMinX()) > -240   )
        kwadrat[i]->moveBy(-blockSize,0);
    }
}

void PiecesHolder::updateRects()
{
    for(int i=0;i<4;i++)
    {
        kwadrat[i]->setX(piece.findMinX() * blockSize);
        kwadrat[i]->setY(piece.findMinY() * blockSize);
    }
}

void PiecesHolder::updateHolder()
{
    if(!init)
            drawRects();
    else
    {
        moveRectsDown();
        if(getNewPiece)
            drawRects();
    }

}
