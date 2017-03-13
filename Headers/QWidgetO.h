#ifndef QWIDGETO
#define QWIDGETO
#include <QWidget>

class QWidgetO : public QWidget
{
    Q_OBJECT
    public :
        QWidgetO(QWidget* parent = 0): QWidget(parent){};
        virtual void initialisationButtons()=0;
        virtual void sup(QString name) = 0;
};
#endif // QWIDGETO

