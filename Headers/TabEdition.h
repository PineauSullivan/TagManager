/**
 * @file TabEdition.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de TabEdition
 *
**/

#ifndef TABEDITION_H
#define TABEDITION_H
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QTreeView>
#include <string>
#include <Headers/Tags.h>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QListView>
#include <QHeaderView>
#include <QList>
#include <Headers/Tag.h>
#include <QLabel>
#include <Headers/QWidgetO.h>
#include <Headers/Style.h>
#include <Headers/QPushButtonPlus.h>
#include <QMenuBar>
#include <QDirModel>
#include <QMouseEvent>

/**
* @class TabEdition
* 
* @brief Classe permettant de définir la classe TabEdition 
*
*/
class TabEdition : public QWidgetO
{
    Q_OBJECT

    private :
        Tags* tags;                         // attribut : pointeur vers l'objet tags
        QPushButton* creerTag;              // attribut : pointeur vers le button creerTag
        QPushButton* associerTag;           // attribut : pointeur vers le button associerTag
        Tag* tagEnSuppression;              // attribut : pointeur vers le tag qui a été selectionné pour être supprimé
        QMenu* menuTag;                     // attribut : pointer vers le menu d'un clic droit sur un tag
        QList<QPushButtonPlus*> buttonsList;// attribut : liste de tout les boutons (1 bouton = 1 tag)
        QList<Tag*> tagsSelected;           // attribut : liste des tags sélectionnés
        QList<QString> waysSelected;        // attribut : liste des chemins/fichiers/dossiers sélectionné
        QTreeView* view;                    // attribut : view des fichiers/dossier
        QDirModel* model;                   // attribut : model des fichiers/dossier

    public :
        /**
        * @brief Constructeur, crée un objet TabEdition
        * @param Tags*, tags
        * @param QWidget*, parent = 0
        */
        TabEdition(Tags *tags ,QWidget* parent = 0);

        /**
        * @brief procédure permettant d'initialiser les buttons du widget
        */
        void initialisationButtons();

        /**
        * @brief procédure permettant d'initialiser les buttons des tags
        */
        void initialisationButtonsList();

        /**
        * @brief procédure permettant de vider les listes de selection
        */
        void clearSelected();

        /**
        * @brief procédure permettant de supprimer un tag de sa liste
        * @param QString, name
        */
        void sup(QString name);

        /**
        * @brief Destructeur de TabEdition
        */
        ~TabEdition();

    private slots:
        /**
        * @brief procédure SLOT permettant de créer un tag
        */
        void creationTag();

        /**
        * @brief procédure SLOT permettant d'ajouter un tag selectionné dans la liste tagsSelected
        */
        void tagClicked();

        /**
        * @brief procédure SLOT permettant de créer une association avec les différents chemins et tag selectionnés
        */
        void association();

        /**
        * @brief procédure SLOT permettant d'afficher le menu du tag et de le repositionner au bonne endroit
        */
        void menuTagClicked();

        /**
        * @brief procédure SLOT permettant de supprimer le tag sélectionné
        */
        void supTag();

        /**
        * @brief procédure SLOT permettant d'ajouter tous les chemins selectionnés a chaque fois qu'il y a clique sur la view 
        */
        void selectedAuto();

    public slots:
        /**
        * @brief procédure SLOT publique permettant d'afficher une pop-up d'aide edition
        */
        void messageAide();

};
#endif // TABEDITION_H
