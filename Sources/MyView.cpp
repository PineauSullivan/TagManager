/**
* @file View.cpp
* @author G. Killian, P. Sullivan
* @since 14/03/2017
* @brief implémentation des méthodes de la classe View
*
**/

//****************************************************************************************************
#include "Headers/MyView.h"
#include <QMouseEvent>

//****************************************************************************************************
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

   if(event->button() == Qt::RightButton){ //click droit détecté
       emit rightClicked();
   }
   QTableView::mousePressEvent(event);

}

//****************************************************************************************************
void MyView::mouseDoubleClickEvent( QMouseEvent * e )
{
    this->pos=  e->pos();
    if ( e->button() == Qt::LeftButton ) //click gauche détecté
    {
        emit doubleClicked();
    }


}

//****************************************************************************************************
QPoint MyView::getPos(){
    return this->pos;
}
