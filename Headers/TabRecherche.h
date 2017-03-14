/**
 * @file TabRecherche.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de TabRecherche
 *
**/

#ifndef TABRECHERCHE_H
#define TABRECHERCHE_H

#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <Headers/Tags.h>
#include <Headers/QWidgetO.h>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLabel>
#include <QStandardItemModel>
#include <Headers/QPushButtonPlus.h>
#include <QMenuBar>
#include <Headers/Style.h>
#include <Headers/MyView.h>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QCheckBox>
#include <QToolBar>
/**
* @class TabRecherche
* 
* @brief Classe permettant de définir la classe TabRecherche 
*
*/
class TabRecherche : public QWidgetO
{
    Q_OBJECT

    private :
        Tags* tags;                         // attribut : pointeur vers l'objet tags
        QList<QPushButtonPlus*> buttonsList;// attribut : liste de tout les boutons (1 bouton = 1 tag)
        QList<Tag*> tagsSelected;           // attribut : liste des tags sélectionnés
        Tag* tagEnSuppression;              // attribut : pointeur vers le tag qui a été selectionné pour être supprimé
        MyView* view;                       // attribut : view des fichiers/dossier (MyView car certain events ont été rédéfinis)
        QStandardItemModel* model;          // attribut : model des fichiers/dossier
        QMenu* menuTag;                     // attribut : pointer vers le menu d'un clic droit sur un tag
        QMenu* menuWay;                     // attribut : pointer vers le menu d'un clic droit sur un chemin
        QCheckBox* modeRechercheET;         // attribut : pointeur vers une checkbox pour représenter le mode recherche en ET logique
        QCheckBox* modeRechercheOU;         // attribut : pointeur vers une checkbox pour représenter le mode recherche en OU logique

    public :
        /**
        * @brief Constructeur, crée un objet TabRecherche
        * @param Tags*, tags
        * @param QWidget*, parent = 0
        */
        TabRecherche(Tags *tags, QWidget* parent = 0);

        /**
        * @brief procédure permettant d'initialiser les buttons du widget
        */
        void initialisationButtons();

        /**
        * @brief procédure permettant de supprimer un tag
        * @param QString, name
        */
        void sup(QString name);

        /**
        * @brief Destructeur de TabRecherche
        */
        ~TabRecherche();

    private slots:
        /**
        * @brief procédure SLOT permettant d'ajouter un tag selectionné dans la liste tagsSelected
        */
        void tagClicked();
        
        /**
        * @brief procédure SLOT permettant d'afficher une pop-up si on clique sur le bouton aucun tag
        */
        void aucunTag();

        /**
        * @brief procédure SLOT permettant de lancer une recherche
        */
        void recherche();

        /**
        * @brief procédure SLOT permettant d'afficher le menu du tag et de le repositionner au bonne endroit
        */
        void menuTagClicked();

        /**
        * @brief procédure SLOT permettant d'afficher le menu du way et de le repositionner au bonne endroit
        */
        void menuWayClicked();

        /**
        * @brief procédure SLOT permettant de lancer/ouvrir le fichier/repertoire
        */  
        void lancer();

        /**
        * @brief procédure SLOT permettant de supprimer le tag sélectionné
        */
        void supTag();

        /**
        * @brief procédure SLOT permettant de supprimer le way sélectionné
        */
        void supWay();

        /**
        * @brief procédure SLOT permettant de gerer et faire les modification nécessaire si l'utilisateur clique sur la checkbox ET
        */
        void checkboxETChanged();

        /**
        * @brief procédure SLOT permettant de gerer et faire les modification nécessaire si l'utilisateur clique sur la checkbox OU
        */
        void checkboxOUChanged();

    public slots:
        /**
        * @brief procédure SLOT publique permettant d'afficher une pop-up d'aide edition
        */
        void messageAide();

};
#endif // TABRECHERCHE_H
