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
    ilosc_ulozonych = 0;

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<15;j++)
        {
            placedTab[i][j] = 0;
        }
    }
    connect(timer,SIGNAL(timeout()),this,SLOT(updateHolder()));
    timer->start(500);
    isStopped = false;

}

void PiecesHolder::keyPressEvent(QKeyEvent *event)
{
    int tmp[4][2];
    if(event->key() == Qt::Key_Up)
    {
        for(int i=0;i<4;i++)
        {
         qDebug() << "KW X: " << kwadrat[i]->rect().x(); //polozenie kazdego kwadratu w stosunku do poczatku figury
         //qDebug() << "KW X: " << kwadrat[i]->x();  //polozenie calej figury w stosunku do punktu poczatkowego
        // qDebug() << "Piece X: " << piece.getX(i) << "( " << 240 + piece.getX(i) * blockSize  << ")";

         qDebug() << "KW Y: " << kwadrat[i]->rect().y();
         //qDebug() << "KW Y: " << kwadrat[i]->y();
         //qDebug() << "Piece Y: " << piece.getY(i) << "( " << piece.getY(i)*blockSize - piece.findMinY()*40 << ")";


        }

        piece = piece.rotate();
        qDebug() << " ";
        pieceCordX = width/2 + blockSize;
        pieceCordY = 0;
        for(int i=0;i<4;i++)
        {
            kwadrat[i]->setRect(pieceCordX+piece.getX(i)*blockSize,pieceCordY+piece.getY(i)*blockSize - piece.findMinY()*40,blockSize,blockSize);
        }

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
        if(isStopped)
        {
            isStopped = false;
            timer->start();
        }
            else
        {
            isStopped = true;
            timer->stop();
        }
    }
    else if(event->key() == Qt::Key_D)
    {
        for(int l = 0;l<15;l++)
        {
                qDebug() << placedTab[0][l] << placedTab[1][l] << placedTab[2][l] << placedTab[3][l] << placedTab[4][l] << placedTab[5][l] << placedTab[6][l] << placedTab[7][l] << placedTab[8][l] << placedTab[9][l];
        }
    }
}

void PiecesHolder::drawRects()
{ //400x600
    piece = myPiece(width,heigth,blockSize);
    pieceCordX = width/2 + blockSize;
    pieceCordY = 0;
    //qDebug() << pieceCordX << pieceCordY;
    for(int i=0;i<4;i++)
    {
        kwadrat[i] = new QGraphicsRectItem();
        switch(piece.pieceType) //0-6
        {
        case 0:
            kwadrat[i]->setBrush(Qt::red);
            break;
        case 1:
            kwadrat[i]->setBrush(Qt::yellow);
            break;
        case 2:
            kwadrat[i]->setBrush(Qt::blue);
            break;
        case 3:
            kwadrat[i]->setBrush(Qt::green);
            break;
        case 4:
            kwadrat[i]->setBrush(Qt::cyan);
            break;
        case 5:
            kwadrat[i]->setBrush(Qt::magenta);
            break;
        case 6:
            kwadrat[i]->setBrush(Qt::gray);
            break;
        }
        kwadrat[i]->setRect(pieceCordX+piece.getX(i)*blockSize,pieceCordY+piece.getY(i)*blockSize - piece.findMinY()*40,blockSize,blockSize);
        scene()->addItem(kwadrat[i]);
    }
    init = true;
}

void PiecesHolder::moveRectsDown()
{
    bool kolizja = false;

    kolizja = canMove(0,1);

        for(int i=0;i<4;i++)
        {
            if(  ( kwadrat[i]->y() + (-(piece.findMinY() - (piece.findMaxY() + 1)) * blockSize) ) < heigth && kolizja)
            {
                kwadrat[i]->moveBy(0,blockSize);
                getNewPiece = false;
            }
            else
            {
                getNewPiece = true;
            }
    }

}

void PiecesHolder::moveRectsRight()
{
    if(canMove(1,0))
    {
        for(int i=0;i<4;i++)
        {
            if(  (kwadrat[i]->x() + blockSize*piece.findMaxX()) < 120   )
            kwadrat[i]->moveBy(blockSize,0);
        }
    }
}

void PiecesHolder::moveRectsLeft()
{
    if(canMove(-1,0))
    {
        for(int i=0;i<4;i++)
        {
            if(  (kwadrat[i]->x() + blockSize*piece.findMinX()) > -240   )
            kwadrat[i]->moveBy(-blockSize,0);
        }
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

void PiecesHolder::grabNewPiece(bool b)
{
    if(b)
    {
        int val1;
        int val2;
        for(int i=0;i<4;i++)
        {
            val1 = (kwadrat[i]->rect().x() + kwadrat[i]->x())/40;
            val2 = (kwadrat[i]->rect().y() + kwadrat[i]->y())/40;
            placedTab[val1][val2] = 1;
            ulozone[ilosc_ulozonych+i] = kwadrat[i];
           }
        ilosc_ulozonych+=4;
        drawRects();
    }
}

bool PiecesHolder::canMove(int x, int y)
{
    int v1;
    int v2;
    for(int j = 0; j < 4; j++)
    {
        v1 = (kwadrat[j]->rect().x() + kwadrat[j]->x()) / 40;
        v2 = (kwadrat[j]->rect().y() + kwadrat[j]->y()) / 40;
        if(placedTab[v1+x][v2+y] == 1)
            return false;
    }
    return true;
}

void PiecesHolder::checkForFullLines()
{
    int elementsInLine = 0;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(placedTab[j][i] == 1)
                elementsInLine ++;
            if(elementsInLine == 10)
                dropLine(i);
        }
        elementsInLine = 0;
    }
}

void PiecesHolder::dropLine(int a)
{
    qDebug() << heigth - (((heigth/blockSize) - a )* blockSize);
    int v1 = 0;
    int v2 = 0;
    for(int i = 0; i<ilosc_ulozonych;i++)
    {
        if(ulozone[i]->rect().y() + ulozone[i]->y() == heigth - (((heigth/blockSize) - a )* blockSize))
        {
            v1 = (ulozone[i]->rect().x() + ulozone[i]->x())  / 40;
            v2 = (ulozone[i]->rect().y() + ulozone[i]->y())  / 40;
            //scene()->removeItem(ulozone[i]);
            ulozone[i]->setPos(1000,1000);
            placedTab[v1][v2] = 0;
            }
    }
    dropAllPiecesDown((heigth/blockSize) - a);

}

void PiecesHolder::dropAllPiecesDown(int X)
{
    int v1,v2;
    int h;
    for(h=heigth-(X*blockSize) ; h>0 ; h-=blockSize) //sprawdzamy od dolu
    {
        for(int i=0;i<ilosc_ulozonych;i++) //sprawdzamy kazdy element z ulozonych
        {
            v1 = (ulozone[i]->rect().x() + ulozone[i]->x())  / blockSize;
            v2 = (ulozone[i]->rect().y() + ulozone[i]->y())  / blockSize;

            if(v2 == h/blockSize) //jezeli klocek jest na tej samej wysokosci
            {
            ulozone[i]->moveBy(0,blockSize);
            placedTab[v1][v2] = 0;
            placedTab[v1][v2+1] = 1;
            }

        }
    }
}

void PiecesHolder::updateHolder()
{
    if(!init)
            drawRects();
    else
    {
        moveRectsDown();
        grabNewPiece(getNewPiece);
        checkForFullLines();

    }

}
