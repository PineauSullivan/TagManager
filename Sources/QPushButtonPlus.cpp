#include "Headers/QPushButtonPlus.h"
#include <QMouseEvent>

QPushButtonPlus::QPushButtonPlus(QString name, QWidget *parent) :
   QPushButton(name,parent)
{
    setMouseTracking(true);

}

//****************************************************************************************************
void QPushButtonPlus::mousePressEvent(QMouseEvent *event)
{
    this->pos=  event->pos();

   if(event->button() == Qt::RightButton){

       emit rightClicked();
   }
  if(event->button() == Qt::LeftButton){

           emit leftClicked();
       }

}

QPoint QPushButtonPlus::getPos(){
    return this->pos;
}
