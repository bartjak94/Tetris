#ifndef MYPIECE_H
#define MYPIECE_H

#include <QGraphicsRectItem>
#include "QKeyEvent"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>

class myPiece {
public:
    myPiece(int w, int h, int s);
    int tablicaKwadratow[4][2];
    int pieceType;


    bool reachedBottom = false;
    int windowH;
    int windowW;
    int blockS;
    myPiece();
    void generatePieceType();
    void setPieceBody();
    void getCoordsOfRect();
    int getX(int i);
    int getY(int i);
    bool moveOneDown();
    bool moveOneLeft();
    bool moveOneRight();

    int findMaxY();
    int findMinY();
    int findMinX();
    int findMaxX();

    int findPieceWithMaxY();

    myPiece rotate();
};



#endif // MYPIECE_H
