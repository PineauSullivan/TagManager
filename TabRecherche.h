#ifndef TABRECHERCHE_H
#define TABRECHERCHE_H
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <Tags.h>

class TabRecherche : public QWidget
{
    Q_OBJECT

private :
    Tags* tags;
    QHash<int, QPushButton*> buttonsList;
    QPushButton* rechercher;

public :
        TabRecherche(Tags *tags, QWidget* parent = 0);
        void initialisationButtons();
        ~TabRecherche();
private slots:

};
#endif // TABRECHERCHE_H
