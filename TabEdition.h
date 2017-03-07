#ifndef TABEDITION_H
#define TABEDITION_H
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <string>

class TabEdition : public QWidget
{
    Q_OBJECT

private :
        QPushButton* creerTag;
        QPushButton* AssocierTag;
        QHash<int, QPushButton*> buttonsList;
public :
        TabEdition(QWidget* parent = 0 );
        void initialisationButtons();
        ~TabEdition();

private slots:
        void creationTag();
        void tagClicked();
        void association();
};
#endif // TABEDITION_H
