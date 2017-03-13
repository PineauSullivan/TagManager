#include "MyView.h"
#include <QMouseEvent>

MyView::MyView(QWidget *parent) :
   QTableView(parent)
{
}

//****************************************************************************************************
void MyView::mousePressEvent(QMouseEvent *event)
{

   if(event->button() == Qt::RightButton){
       emit rightClicked();
   }
   QTableView::mousePressEvent(event); // call base class implementation

}

void MyView::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
    {
        emit doubleClicked();
    }


}
