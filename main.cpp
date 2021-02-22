#include <QApplication>
#include <QGraphicsScene>
#include "mypiece.h"
#include <QGraphicsView>
#include "time.h"
#include "piecesholder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int WindowWidth = 400;
    int WindowHeigth = 600;

    QGraphicsScene *scene = new QGraphicsScene();
    PiecesHolder *pieceHolder = new PiecesHolder(WindowWidth, WindowHeigth);
    pieceHolder->setRect(0,0,WindowWidth,WindowHeigth);
    scene->addItem(pieceHolder);

    pieceHolder->setFlag(QGraphicsItem::ItemIsFocusable);
    pieceHolder->setFocus();
    QGraphicsView *view = new QGraphicsView();
    view->setFixedSize(WindowWidth+200,WindowHeigth+10);
    scene->setSceneRect(100,0,WindowWidth,WindowHeigth);
    view->setScene(scene);
    view->show();
    return a.exec();
}
