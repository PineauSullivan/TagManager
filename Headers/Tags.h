/**
 * @file Tags.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de Tabs
 *
**/

#ifndef TAGS
#define TAGS

#include <string>
#include <QString>
#include <Headers/Tag.h>
#include <Headers/QWidgetO.h>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

/**
* @class Tags
* 
* @brief Classe permettant de lister les différents tags et possède un pointeur vers les deux modes 
*
*/
class Tags
{
    private :
        QList<Tag*> ListTags;   // attribut : Liste de pointeur de Tag
        QWidgetO* TabRecherche; // attribut : pointeur vers un QWidgetO (TabRecherche, mode de recherche)
        QWidgetO* TabEdition;   // attribut : pointeur vers un QWidgetO (TabEdition, mode de recherche)

    public :

        /**
        * @brief Constructeur, crée un objet Tags
        */
        Tags();

        /**
        * @brief Getter de l'attribut TabRecherche
        * @return attribut TabRecherche
        */
        QWidgetO* getTabRecherche();
        
        /**
        * @brief Getter de l'attribut TabEdition
        * @return attribut TabEdition
        */
        QWidgetO* getTabEdition();
        
        /**
        * @brief Getter de l'attribut ListTags
        * @return attribut ListTags
        */
        QList<Tag*> getListTags();

        /**
        * @brief Getter d'un pointeur de tag possèdant le même nom que celui mis en paramètre
        * @param QString, nameTag
        * @return Tag*
        */
        Tag* getTag(QString nameTag);
        
        /**
        * @brief Setter de l'attribut TabRecherche
        * @param QWidgetO*, TabRecherche
        */
        void setQWidgetRecherche(QWidgetO* TabRecherche);

        /**
        * @brief Setter de l'attribut TabEdition
        * @param QWidgetO*, TabEdition
        */
        void setQWidgetEdition(QWidgetO* TabEdition);

        /**
        * @brief Procédure permettant de supprimer un tag dans Tags et de modifier/supprimer les fichiers de configs respectifs
        * @param Tag*, tag
        */
        void supprimerTag(Tag* tag);


        /**
        * @brief procédure permettant d'initialiser tous les tags avec le fichier de config
        */
        void initialiserTagsFiles();
        
        /**
        * @brief Procédure permettant d'ajouter un tag dans Tags et de modifier/ajouter les fichiers de configs respectifs avec ecriture ou non
        * @param QString, name
        * @param bool, write
        */
        void add_tag(QString name, bool write);
       
        /**
        * @brief Destructeur de Tags
        */
        ~Tags();

};
#endif // TAGS

