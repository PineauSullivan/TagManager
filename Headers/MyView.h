/**
 * @file MyView.h
* @author G. Killian, P. Sullivan
* @since 14/03/2017
 * @brief Définition d'une classe de MyView
 *
**/

#ifndef MYVIEW
#define MYVIEW

#include <QTableView>
#include <QPoint>

/**
* @class MyView
* 
* @brief Classe permettant de redéfinir la classe QTableView 
*
*/
class MyView : public QTableView
{
    Q_OBJECT

    private:
        QPoint pos; // attribut : position du dernier event (Afin de récupérer la position du click)
        QWidget* parent; // attribut : pointeur vers le widget parent

    public:

    	/**
    	* @brief Constructeur, crée un objet Myview
        * @param QWidget*, parent = 0
    	*/
    	explicit MyView(QWidget *parent = 0);

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
        * @brief procédure permettant de réprésenter le signal d'un double clic
        */
        void doubleClicked();


    private slots:

        /**
        * @brief procédure slot permettant de redéfinir l'événement d'un clic
        * @param QMouseEvent*, event
        */
        void mousePressEvent(QMouseEvent *event);
        
        /**
        * @brief procédure slot permettant de redéfinir l'événement d'un double clic
        * @param QMouseEvent*, e
        */
        void mouseDoubleClickEvent( QMouseEvent * e );


};
#endif // MYVIEW

