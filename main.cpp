#include <QApplication>
#include <QPushButton>
#include "TabEdition.h"
#include "TabRecherche.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Création de l'objet de gestion des onglets
    QTabWidget MesOnglets;

    //Création des différents widgets qui vont composer les onglets
    TabRecherche MyTabRecherche;
    TabEdition MyTabEdition;

    //Agencement des différents widgets en onglets
    MesOnglets.addTab(&MyTabRecherche,"Mode Recherche");//Creation du premier onglet
    MesOnglets.addTab(&MyTabEdition,"Mode Edition");//Creation du deuxième onglet

    //Affichage de l'application
    MesOnglets.show();

    return a.exec();
}
