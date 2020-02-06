#include "mypiece.h"

myPiece::myPiece(int w, int h, int s)
{
    generatePieceType();
    setPieceBody();
   // getCoordsOfRect();
    windowH = h;    //600
    windowW = w;    //400
    blockS = s;     //w/10 = 40
}

myPiece::myPiece()
{

}


void myPiece::generatePieceType()
{
    pieceType =(QRandomGenerator::global()->bounded(7));
}

void myPiece::setPieceBody()
{
    switch(pieceType){
    case 0: // X
            // X
            // X
            // X
        //kazda para reprezentuje wspolrzedne jednego punktu
        tablicaKwadratow[0][0]=0;//x1
        tablicaKwadratow[0][1]=-1;//y1

        tablicaKwadratow[1][0]=0;//x2
        tablicaKwadratow[1][1]=0;//y2

        tablicaKwadratow[2][0]=0;//x3
        tablicaKwadratow[2][1]=1;//y3

        tablicaKwadratow[3][0]=0;//x4
        tablicaKwadratow[3][1]=2;//y4
        break;
    case 1: // XX
            // X
            // X
        tablicaKwadratow[0][0]=1;
        tablicaKwadratow[0][1]=-1;

        tablicaKwadratow[1][0]=0;
        tablicaKwadratow[1][1]=-1;

        tablicaKwadratow[2][0]=0;
        tablicaKwadratow[2][1]=0;

        tablicaKwadratow[3][0]=0;
        tablicaKwadratow[3][1]=1;
        break;
    case 2:  //  X
             // XX
             // X
        tablicaKwadratow[0][0]=0;
        tablicaKwadratow[0][1]=-1;

        tablicaKwadratow[1][0]=0;
        tablicaKwadratow[1][1]=0;

        tablicaKwadratow[2][0]=-1;
        tablicaKwadratow[2][1]=0;

        tablicaKwadratow[3][0]=-1;
        tablicaKwadratow[3][1]=1;
        break;
    case 3: // XX
            //  X
            //  X
        tablicaKwadratow[0][0]=-1;
        tablicaKwadratow[0][1]=-1;

        tablicaKwadratow[1][0]=0;
        tablicaKwadratow[1][1]=-1;

        tablicaKwadratow[2][0]=0;
        tablicaKwadratow[2][1]=0;

        tablicaKwadratow[3][0]=0;
        tablicaKwadratow[3][1]=1;
        break;
    case 4:  // X
             // XX
             //  X
        tablicaKwadratow[0][0]=0;
        tablicaKwadratow[0][1]=-1;

        tablicaKwadratow[1][0]=0;
        tablicaKwadratow[1][1]=0;

        tablicaKwadratow[2][0]=1;
        tablicaKwadratow[2][1]=0;

        tablicaKwadratow[3][0]=1;
        tablicaKwadratow[3][1]=1;
        break;
    case 5: // XX
            // XX
        tablicaKwadratow[0][0]=0;
        tablicaKwadratow[0][1]=0;

        tablicaKwadratow[1][0]=1;
        tablicaKwadratow[1][1]=0;

        tablicaKwadratow[2][0]=0;
        tablicaKwadratow[2][1]=1;

        tablicaKwadratow[3][0]=1;
        tablicaKwadratow[3][1]=1;
        break;
    case 6: // XXX
            //  X
        tablicaKwadratow[0][0]=-1;
        tablicaKwadratow[0][1]=0;

        tablicaKwadratow[1][0]=0;
        tablicaKwadratow[1][1]=0;

        tablicaKwadratow[2][0]=1;
        tablicaKwadratow[2][1]=0;

        tablicaKwadratow[3][0]=0;
        tablicaKwadratow[3][1]=1;
        break;

    }
}

void myPiece::getCoordsOfRect()
{
    qDebug() << "NEW SET: ";
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<2;j++)
        qDebug() << tablicaKwadratow[i][j];
    }
}

int myPiece::getX(int i)
{
    return tablicaKwadratow[i][0];
}

int myPiece::getY(int i)
{
    return tablicaKwadratow[i][1];
}



int myPiece::findMinY()
{
    int miny = tablicaKwadratow[0][1];
    for(int i=0;i<4;i++)
    {
        if(miny>tablicaKwadratow[i][1])
            miny = tablicaKwadratow[i][1];
    }
    return miny;
}



int myPiece::findMaxY()
{
    int maxy = tablicaKwadratow[0][1];
    for(int i=0;i<4;i++)
    {
        if(maxy<tablicaKwadratow[i][1])
            maxy = tablicaKwadratow[i][1];
    }
    return maxy;
}

int myPiece::findMinX()
{
    int minx = tablicaKwadratow[0][0];
    for(int i=0;i<4;i++)
    {
        if(minx>tablicaKwadratow[i][0])
            minx = tablicaKwadratow[i][0];
    }
    return minx;
}


int myPiece::findMaxX()
{
    int maxx = tablicaKwadratow[0][0];
    for(int i=0;i<4;i++)
    {
        if(maxx<tablicaKwadratow[i][0])
            maxx = tablicaKwadratow[i][0] ;
    }
    return maxx;
}

int myPiece::findPieceWithMaxY()
{
    int maxy = tablicaKwadratow[0][1];
    int pieceNumber = 0;
    for(int i=0;i<4;i++)
    {
        if(maxy<tablicaKwadratow[i][1])
        {
            maxy = tablicaKwadratow[i][1];
            pieceNumber = i;
        }
    }
    return pieceNumber;
}


void myPiece::rotate()
{
    if(pieceType!=5)
    {
    int tablicaZastepcza[4][2];

    for(int i=0; i<4; ++i) {
        for(int j=0;j<2;j++)
        {
            tablicaZastepcza[i][j] = tablicaKwadratow[i][j];
        }
    }
    setPieceBody();

    int offsetX = tablicaZastepcza[0][0] - tablicaKwadratow[0][0];
    int offsetY = tablicaZastepcza[0][1] - tablicaKwadratow[0][1];
    qDebug() << offsetX << offsetY;

    for(int i=0; i<4; ++i) {
        {
        qDebug() << tablicaKwadratow[i][0] << ">" << tablicaKwadratow[i][1];
        qDebug() << tablicaKwadratow[i][1] << ">" << -tablicaKwadratow[i][0];
        tablicaZastepcza[i][0] = tablicaKwadratow[i][1];
        tablicaZastepcza[i][1] = -tablicaKwadratow[i][0];
        }
    }

    for(int i=0; i<4; ++i) {
        for(int j=0;j<2;j++)
        {
            if(j==0)
            tablicaKwadratow[i][j] = tablicaZastepcza[i][j] * offsetX;
            else
            tablicaKwadratow[i][j] = tablicaZastepcza[i][j] * offsetY;
        }
    }


    }
}






