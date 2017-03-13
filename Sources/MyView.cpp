#include "Headers/MyView.h"
#include <QMouseEvent>

MyView::MyView(QWidget *parent) :
   QTableView(parent)
{
    setMouseTracking(true);
    this->parent = parent;
}

//****************************************************************************************************
void MyView::mousePressEvent(QMouseEvent *event)
{
    this->pos= event->pos();

   if(event->button() == Qt::RightButton){
       emit rightClicked();
   }
   QTableView::mousePressEvent(event); // call base class implementation

}

void MyView::mouseDoubleClickEvent( QMouseEvent * e )
{
    this->pos=  e->pos();
    if ( e->button() == Qt::LeftButton )
    {
        emit doubleClicked();
    }


}

QPoint MyView::getPos(){
    return this->pos;
}
