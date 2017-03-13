#include "Headers/QPushButtonPlus.h"
#include <QMouseEvent>

QPushButtonPlus::QPushButtonPlus(QString name, QWidget *parent) :
   QPushButton(name,parent)
{
}

//****************************************************************************************************
void QPushButtonPlus::mousePressEvent(QMouseEvent *event)
{

   if(event->button() == Qt::RightButton){

       emit rightClicked();
   }
  if(event->button() == Qt::LeftButton){

           emit leftClicked();
       }

}
