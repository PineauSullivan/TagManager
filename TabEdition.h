#ifndef TABEDITION_H
#define TABEDITION_H
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>

class TabEdition : public QWidget
{
    Q_OBJECT

private :
        QPushButton* creerTag;
        QPushButton* AssocierTag;

public :
        TabEdition(QWidget* parent = 0 );
        ~TabEdition();

private slots:
        void buttonClicked();
};
#endif // TABEDITION_H
