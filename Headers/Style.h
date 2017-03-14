/**
 * @file Style.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de Style
 *
**/

#ifndef STYLE
#define STYLE

#include <QPushButton>

/**
* @class Style
* 
* @brief Classe permettant de définir la classe Style 
*
*/
class Style
{
public :
	/**
	* @brief procédure permettant d'attribuer un style au boutton en fonction de la version choisis
	* @param QPushButton*, button
	* @param int, version
	*/
    static void setStyle(QPushButton* button, int version);
};

#endif // STYLE

