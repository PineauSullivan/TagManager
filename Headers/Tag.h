/**
 * @file Tag.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de Tab
 *
**/

#ifndef TAG
#define TAG

#include <string>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>

/**
* @class Tag 
* 
* @brief Classe permettant de représenter un tag (chaque tag possède un nom et une liste de chemin qui lui ont été associé) 
*
*/

class Tag
{
private :
    QList<QString> ListWays; // attribut : Liste de QString de chemins 
    QString Name; // attribut : Nom 

public :

    /**
    * @brief Constructeur, crée un objet Tag avec un nom mis en paramètre
    * @param QString, name
    */
    Tag(QString name);
    
    /**
   * @brief Getter de l'attribut ListWays
   * @return attribut ListWays
   */
    QList<QString> getListWays();

    /**
   * @brief Getter de l'attribut Name
   * @return attribut Name
   */   
    QString getName();

    /**
    * @brief procédure permettant d'ajouter une association(chemin) dans la ListWays et avec une ecriture dans le fichier
    * @param QString way, bool write
    */
    void AddWay(QString way, bool write);

    /**
    * @brief fonction retournant le bool si le tag possède le même nom
    * @param QString name
    */
    bool is(QString name);

    /**
    * @brief procédure permettant d'initialiser ListWays avec son fichier de config
    */
    void initialiserTagFiles();
    
    /**
    * @brief fonction retournant le bool si le tag possède cette association (chemin)
    * @param QString way
    */
    bool tagPossedant(QString way);
    
    /**
    * @brief procédure permettant de supprimer une association(chemin)
    * @param QString way
    */    
    void supWay(QString way);
    
    /**
    * @brief Destructeur de Tag
    */
    ~Tag();
};

#endif // TAG

