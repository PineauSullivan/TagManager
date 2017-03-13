#ifndef QPUSHBUTTONPLUS_H
#define QPUSHBUTTONPLUS_H
#include <QPushButton>
#include <QPoint>

class QPushButtonPlus : public QPushButton
{
   Q_OBJECT
public:
   explicit QPushButtonPlus(QString name, QWidget *parent = 0);
   QPoint getPos();


signals:
   void rightClicked();
   void leftClicked();

private slots:
   void mousePressEvent(QMouseEvent *event);

private:
   QPoint pos;
};
#endif // QPUSHBUTTONPLUS_H
