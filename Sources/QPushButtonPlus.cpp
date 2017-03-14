/**
* @file QPushButtonPlus.cpp
* @author G. Killian, P. Sullivan
* @since 14/03/2017
* @brief implémentation des méthodes de la classe QPushButtonPlus
*
**/

//****************************************************************************************************
#include "Headers/QPushButtonPlus.h"
#include <QMouseEvent>

//****************************************************************************************************
QPushButtonPlus::QPushButtonPlus(QString name, QWidget *parent) :
   QPushButton(name,parent)
{
    setMouseTracking(true);

}

//****************************************************************************************************
void QPushButtonPlus::mousePressEvent(QMouseEvent *event)
{
    this->pos=  event->pos();

   if(event->button() == Qt::RightButton){ // click droit détecté

       emit rightClicked();
   }
  if(event->button() == Qt::LeftButton){  //click gauche détecté

           emit leftClicked();
       }

}

//****************************************************************************************************
QPoint QPushButtonPlus::getPos(){
    return this->pos;
}
