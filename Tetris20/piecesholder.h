#ifndef PIECESHOLDER_H
#define PIECESHOLDER_H

#include "mypiece.h"
#include "QGraphicsRectItem"
#include "QDebug"
#include <QGraphicsScene>
#include "QKeyEvent"
#include <QObject>
#include <QTimer>
#include <QDebug>

class PiecesHolder : public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    PiecesHolder(int w, int h);
    myPiece piece;
    myPiece tmpPiece;
    QGraphicsRectItem *kwadrat[4];
    QTimer * timer = new QTimer();

    int width;
    int heigth;

    int realWidth;
    int realHeigth;

    int pieceCordX;
    int pieceCordY;

    bool isStopped;

    int placedTab[10][15];
    QGraphicsRectItem *ulozone[4000];
    int ilosc_ulozonych;

    void keyPressEvent(QKeyEvent *event);
    void drawRects();
    void moveRectsDown();
    void moveRectsRight();
    void moveRectsLeft();
    void updateRects();
    void grabNewPiece(bool b);
    bool canMove(int x, int y);
    void checkForFullLines();
    void dropLine(int a);

    void dropAllPiecesDown(int X);


public slots:
    void updateHolder();
private:
    int blockSize;
    bool init;
    bool getNewPiece;
};

#endif // PIECESHOLDER_H
