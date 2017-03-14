/**
* @file Main
* @author G. Killian, P. Sullivan
* @since 14/03/2017
* @brief Main de l'application TagManager
*
**/

//****************************************************************************************************
#include <QApplication>
#include <QPushButton>
#include <QSignalMapper>
#include <QTextCodec>
#include "Headers/TabEdition.h"
#include "Headers/TabRecherche.h"
#include "Sources/Tags.cpp"
#include <QMainWindow>

//****************************************************************************************************
int main(int argc, char *argv[])
{
    //Fonction permettant d'éviter le problème d'affichage des caractères
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    //Création de l'objet Tags
    Tags* tags = new Tags();

    //Création de l'objet de gestion des onglets
    QTabWidget MesOnglets;


    //Création des différents widgets qui vont composer les onglets
    TabRecherche MyTabRecherche(tags, &MesOnglets);
    TabEdition MyTabEdition(tags, &MesOnglets);

    tags->setQWidgetEdition(&MyTabEdition);
    tags->setQWidgetRecherche(&MyTabRecherche);


    //Agencement des différents widgets en onglets
    MesOnglets.addTab(&MyTabRecherche,"Mode Recherche");//Creation du premier onglet
    MesOnglets.addTab(&MyTabEdition,"Mode Edition");//Creation du deuxième onglet
    
    //Création du menubar
    QMenuBar* bar = new QMenuBar(&MesOnglets);

    //Création du menu Fichier -> Quitter (permettant de quitter l'application)
    QMenu* menu1 = new QMenu("Fichier");
    QAction* act = new QAction(QObject::tr("Quitter"),&MesOnglets);
    //Ajout du raccourcu Ctrl + Q
    act->setShortcut(QObject::tr("Ctrl+Q"));
    act->setStatusTip(QObject::tr("Quitter l'application"));
    menu1->addAction(act);
    QObject::connect(act, SIGNAL(triggered()), &MesOnglets, SLOT(close()));

    //Création du menu Aide (permettant de l'aide pour la recherche et l'édition)
    QMenu* menu2 = new QMenu("Aide");

    //Aide pour le mode Recherche
    QAction* act1 = new QAction(QObject::tr("Recherche"),&MesOnglets);
    //Ajout du raccourcu Ctrl + R pour recherche
    act1->setShortcut(QObject::tr("Ctrl+R"));
    act1->setStatusTip(QObject::tr("Aide mode recherche"));
    menu2->addAction(act1);
    QObject::connect(act1, SIGNAL(triggered()),  &MyTabRecherche, SLOT(messageAide()));
    
    //Aide pour le mode Edition
    QAction* act2 = new QAction(QObject::tr("Edition"),&MesOnglets);
    //Ajout du raccourcu Ctrl + E pour edition
    act2->setShortcut(QObject::tr("Ctrl+E"));
    act2->setStatusTip(QObject::tr("Aide mode recherche"));
    menu2->addAction(act2);
    QObject::connect(act2, SIGNAL(triggered()),  &MyTabEdition, SLOT(messageAide()));

    //Ajout des deux menus dans le menubar 
    bar->addMenu(menu1);
    bar->addMenu(menu2);

    //Affichage de l'application
    MesOnglets.showMaximized();

    //Affichage de la pop-up de bienvenu si aucun tag n'est créé
    if(tags->getListTags().isEmpty()){
        QMessageBox::information(NULL, "Bienvenu sur TagManager", "Bienvenu sur l'appication TagManager. <br/> Afin de profiter un maximum de cette application, vous devez créer un ou plusieurs tags et les associer aux fichiers ou répertoires que vous désirez. Pour ce faire, il vous suffit de passer en Mode Edition.");
    }

    return a.exec();
}
