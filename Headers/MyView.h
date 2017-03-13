#ifndef MYVIEW
#define MYVIEW
#include <QTableView>
#include <QPoint>

class MyView : public QTableView
{
    Q_OBJECT
public:
   explicit MyView(QWidget *parent = 0);
    QPoint getPos();


signals:
   void rightClicked();
   void doubleClicked();


private slots:
   void mousePressEvent(QMouseEvent *event);
   void mouseDoubleClickEvent( QMouseEvent * e );

private:
   QPoint pos;
   QWidget* parent;

};
#endif // MYVIEW

