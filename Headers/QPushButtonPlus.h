/**
 * @file QPushButtonPush.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de QPushButtonPush
 *
**/

#ifndef QPUSHBUTTONPLUS_H
#define QPUSHBUTTONPLUS_H

#include <QPushButton>
#include <QPoint>

/**
* @class QPushButtonPlus
* 
* @brief Classe permettant de redéfinir la classe QPushButton 
*
*/
class QPushButtonPlus : public QPushButton
{
   Q_OBJECT

	private:
		QPoint pos; // attribut : position du dernier event (Afin de récupérer la position du click)
	
	public:
		/**
		* @brief Constructeur, crée un objet QPushButtonPlus
		* @param QString, name
		* @param QWidget*, parent = 0
		*/
		explicit QPushButtonPlus(QString name, QWidget *parent = 0);

		/**
        * @brief Getter de l'attribut pos
        * @return attribut pos
        */
		QPoint getPos();

	signals:
		/**
        * @brief procédure permettant de réprésenter le signal d'un clic droit
        */
		void rightClicked();

        /**
        * @brief procédure permettant de réprésenter le signal d'un clic gauche
        */		
		void leftClicked();

	private slots:
        /**
        * @brief procédure slot permettant de redéfinir l'événement d'un clic
        * @param QMouseEvent*, event
        */
		void mousePressEvent(QMouseEvent *event);
};
#endif // QPUSHBUTTONPLUS_H
