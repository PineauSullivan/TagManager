#include <QApplication>
#include <QPushButton>
#include <QSignalMapper>
#include <QTextCodec>
#include "Headers/TabEdition.h"
#include "Headers/TabRecherche.h"
#include "Sources/Tags.cpp"
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
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

    QMenuBar* bar = new QMenuBar(&MesOnglets);

    QMenu* menu1 = new QMenu("Fichier");
    QAction* act = new QAction(QObject::tr("Quitter"),&MesOnglets);
    act->setShortcut(QObject::tr("Ctrl+Q"));
    act->setStatusTip(QObject::tr("Quitter l'application"));
    menu1->addAction(act);
    QObject::connect(act, SIGNAL(triggered()), &MesOnglets, SLOT(close()));

    QMenu* menu2 = new QMenu("Aide");
    QAction* act1 = new QAction(QObject::tr("Recherche"),&MesOnglets);
    act1->setShortcut(QObject::tr("Ctrl+R"));
    act1->setStatusTip(QObject::tr("Aide mode recherche"));
    menu2->addAction(act1);
    QObject::connect(act1, SIGNAL(triggered()),  &MyTabRecherche, SLOT(messageAide()));

    QAction* act2 = new QAction(QObject::tr("Edition"),&MesOnglets);
    act2->setShortcut(QObject::tr("Ctrl+E"));
    act2->setStatusTip(QObject::tr("Aide mode recherche"));
    menu2->addAction(act2);
    QObject::connect(act2, SIGNAL(triggered()),  &MyTabEdition, SLOT(messageAide()));

    bar->addMenu(menu1);
    bar->addMenu(menu2);

//    MesOnglets.setMinimumSize(1000,600);
    //Affichage de l'application
    MesOnglets.showMaximized();
    if(tags->getListTags().isEmpty()){
        QMessageBox::information(NULL, "Bienvenu sur TagManager", "Bienvenu sur l'appication TagManager. <br/> Afin de profiter un maximum de cette application, vous devez créer un ou plusieurs tags et les associer aux fichiers ou répertoires que vous désirez. Pour ce faire, il vous suffit de passer en Mode Edition.");
    }

    a.setWindowIcon(QIcon(":/icons/icon.png"));
    return a.exec();
}
