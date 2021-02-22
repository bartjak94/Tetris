#include "piecesholder.h"

PiecesHolder::PiecesHolder(int w, int h)
{
    width = w;
    heigth = h;
    blockSize = w/10;   // jednostka miary, kwadrat jest 1bS/1bS

    realWidth = w/blockSize;
    realHeigth = h/blockSize;

    pieceCordX = width/2 + blockSize;
    pieceCordY = 0;
    leftBound = width + blockSize;

    score = 0;
    level = 1;

    piece = myPiece(w,h,blockSize);

    initFinished = false;
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
    timer->start(500 - level);
    isStopped = false;

}

void PiecesHolder::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        int t1 = 0;
        int t2 = 0;
        bool canRotate = true;
        tmpPiece = piece.rotate();
        for(int i=0;i<4;i++)
        {
            t1 = kwadrat[i]->x() + pieceCordX + tmpPiece.getX(i)*blockSize; //x real
            t2 = kwadrat[i]->y() +pieceCordY+tmpPiece.getY(i)*blockSize - tmpPiece.findMinY()*blockSize; //y real
            //qDebug() << t1 << t2;
            if(     //jezeli jest na prawo od 0
                    t1 < 0
                    || //i na lewo od 400
                    t1 >= width
                    || //i wyzej niz minimum
                    t2 >= heigth
                    || // i pole akurat nie jest zajete
                    placedTab[t1/blockSize][t2/blockSize] == 1
                    )
            {
                canRotate = false;
            }
            /*
            qDebug() << "pos before: " << kwadrat[i]->pos();
            qDebug() << kwadrat[i]->rect();
            qDebug() << "pos after: " << kwadrat[i]->pos();
            qDebug() << kwadrat[i]->rect().x() + kwadrat[i]->x() << kwadrat[i]->rect().y() + kwadrat[i]->y();
            qDebug() << "Z klocka (" << tmpPiece.getX(i) << "," << tmpPiece.getY(i);
            qDebug() << "Pozycja klocka po rotacji: " << kwadrat[0]->x() + pieceCordX + tmpPiece.getX(i)*blockSize <<  kwadrat[0]->y() +pieceCordY+tmpPiece.getY(i)*blockSize - tmpPiece.findMinY()*40;
            qDebug() << " ";
*/
        }
        if(canRotate)
        {
            for(int i=0;i<4;i++)
             kwadrat[i]->setRect(pieceCordX+tmpPiece.getX(i)*blockSize,pieceCordY+tmpPiece.getY(i)*blockSize - tmpPiece.findMinY()*40,blockSize,blockSize);
            piece=tmpPiece;
        }
        canRotate = true;


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
                //qDebug() << placedTab[0][l] << placedTab[1][l] << placedTab[2][l] << placedTab[3][l] << placedTab[4][l] << placedTab[5][l] << placedTab[6][l] << placedTab[7][l] << placedTab[8][l] << placedTab[9][l];
        }
    }
}

void PiecesHolder::drawRects()
{ //400x600
    //po pierwszym obrocie
    if(initFinished)
    {
        //qDebug() << "KOLEJNY OBROT!!";
        piece = nextPiece;
        generateNextPiece();

    }
    //pierwszy obrot
    else
    {
        //qDebug() << "PIERWSZY OBROT!!!";
       piece = myPiece(width,heigth,blockSize);
       generateNextPiece();

       wynik = new QGraphicsSimpleTextItem();
       wynik->setText(QString::number(score));
       wynik->setPos(leftBound,6*blockSize);
       wynik->setFont(QFont("Arial",30));
       scene()->addItem(wynik);
    }

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
        if(placedTab[(pieceCordX+piece.getX(i)*blockSize)/blockSize][(pieceCordY+piece.getY(i)*blockSize - piece.findMinY()*blockSize)/blockSize] != 1)
        {
            kwadrat[i]->setRect(pieceCordX+piece.getX(i)*blockSize,pieceCordY+piece.getY(i)*blockSize - piece.findMinY()*blockSize,blockSize,blockSize);
            scene()->addItem(kwadrat[i]);
        }
        else
            timer->stop();
    }
    initFinished = true;
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
            if(  (kwadrat[i]->x() + blockSize*piece.findMaxX()) < (width - (pieceCordX + blockSize))   )
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
            if(  (kwadrat[i]->x() + blockSize*piece.findMinX()) > -pieceCordX   )
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
            val1 = (kwadrat[i]->rect().x() + kwadrat[i]->x())/blockSize;
            val2 = (kwadrat[i]->rect().y() + kwadrat[i]->y())/blockSize;
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
        v1 = (kwadrat[j]->rect().x() + kwadrat[j]->x()) / blockSize;
        v2 = (kwadrat[j]->rect().y() + kwadrat[j]->y()) / blockSize;
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
    //qDebug() << heigth - (((heigth/blockSize) - a )* blockSize);
    int v1 = 0;
    int v2 = 0;
    for(int i = 0; i<ilosc_ulozonych;i++)
    {
        if(ulozone[i]->rect().y() + ulozone[i]->y() == heigth - (((heigth/blockSize) - a )* blockSize))
        {
            v1 = (ulozone[i]->rect().x() + ulozone[i]->x())  / blockSize;
            v2 = (ulozone[i]->rect().y() + ulozone[i]->y())  / blockSize;
            ulozone[i]->setPos(2*width,2*heigth);
            placedTab[v1][v2] = 0;
            }
    }
    dropAllPiecesDown((heigth/blockSize) - a);
    score+=10;
    wynik->setText(QString::number(score));
    timer->stop();
    if(level < 300)
        level = level + 10;
    timer->start(500 - level);

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

void PiecesHolder::generateNextPiece()
{

    nextPiece = myPiece(width,heigth,blockSize);

    for(int i=0;i<4;i++)
    {
        if(initFinished)
        scene()->removeItem(nextPieceBlocks[i]);
        nextPieceBlocks[i] = new QGraphicsRectItem();
        switch(nextPiece.pieceType) //0-6
        {
        case 0:
            nextPieceBlocks[i]->setBrush(Qt::red);
            break;
        case 1:
            nextPieceBlocks[i]->setBrush(Qt::yellow);
            break;
        case 2:
            nextPieceBlocks[i]->setBrush(Qt::blue);
            break;
        case 3:
            nextPieceBlocks[i]->setBrush(Qt::green);
            break;
        case 4:
            nextPieceBlocks[i]->setBrush(Qt::cyan);
            break;
        case 5:
            nextPieceBlocks[i]->setBrush(Qt::magenta);
            break;
        case 6:
            nextPieceBlocks[i]->setBrush(Qt::gray);
            break;
        }
        nextPieceBlocks[i]->setRect(leftBound+nextPiece.getX(i)*blockSize - nextPiece.findMinX()*blockSize,(pieceCordY+nextPiece.getY(i)*blockSize - nextPiece.findMinY()*blockSize) + blockSize,blockSize,blockSize);
        scene()->addItem(nextPieceBlocks[i]);
    }


}

void PiecesHolder::updateHolder()
{
    if(!initFinished)
    {
            drawRects();
    }
    else
    {
        moveRectsDown();
        grabNewPiece(getNewPiece);
        checkForFullLines();

    }

}
