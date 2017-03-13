#ifndef MYVIEW
#define MYVIEW
#include <QTableView>

class MyView : public QTableView
{
    Q_OBJECT
public:
   explicit MyView(QWidget *parent = 0);


signals:
   void rightClicked();
   void doubleClicked();


private slots:
   void mousePressEvent(QMouseEvent *event);
   void mouseDoubleClickEvent( QMouseEvent * e );

};
#endif // MYVIEW

