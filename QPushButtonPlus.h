#ifndef QPUSHBUTTONPLUS_H
#define QPUSHBUTTONPLUS_H
#include <QPushButton>

class QPushButtonPlus : public QPushButton
{
   Q_OBJECT
public:
   explicit QPushButtonPlus(QString name, QWidget *parent = 0);


signals:
   void rightClicked();
   void leftClicked();


private slots:
   void mousePressEvent(QMouseEvent *event);

private:

};
#endif // QPUSHBUTTONPLUS_H
