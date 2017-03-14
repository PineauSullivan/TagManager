/**
 * @file QWidgetO.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de QWidgetO
 *
**/

#ifndef QWIDGETO
#define QWIDGETO

#include <QWidget>


/**
* @class QWidgetO
* 
* @brief Classe permettant de redéfinir la classe QWidget 
*
*/
class QWidgetO : public QWidget
{
    Q_OBJECT

    public :
		/**
		* @brief Constructeur, crée un objet QWidgetO
		* @param QWidget*, parent = 0
		*/
        QWidgetO(QWidget* parent = 0): QWidget(parent){};
    
    	/**
		* @brief procédure virtual permettant d'initialiser les buttons du widget
		*/
        virtual void initialisationButtons()=0;
    
    	/**
		* @brief procédure virtual de suppression du widget
		* @param QString, name
		*/
        virtual void sup(QString name) = 0;
};
#endif // QWIDGETO

