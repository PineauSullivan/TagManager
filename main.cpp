#include <QApplication>
#include <QPushButton>
#include <QSignalMapper>
#include <QTextCodec>
#include "TabEdition.h"
#include "TabRecherche.h"
#include "Tags.cpp"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    Tags* tags = new Tags();
    //Création de l'objet de gestion des onglets
    QTabWidget MesOnglets;

    //Création des différents widgets qui vont composer les onglets
    TabRecherche MyTabRecherche(tags);
    TabEdition MyTabEdition(tags);

    tags->setQWidgetEdition(&MyTabEdition);
    tags->setQWidgetRecherche(&MyTabRecherche);

    //Agencement des différents widgets en onglets
    MesOnglets.addTab(&MyTabRecherche,"Mode Recherche");//Creation du premier onglet

    MesOnglets.addTab(&MyTabEdition,"Mode Edition");//Creation du deuxième onglet

    //Affichage de l'application
    MesOnglets.showMaximized();


    return a.exec();
}
