#ifndef DEF_MAFENETREPRINCIPALE
#define MAFENETREPRINCIPALE

#include <QApplication>
#include <QWidget>
#include <QPushButton>



class MaFenetrePrincipale : public QWidget
{
    public:
    MaFenetrePrincipale();
    ~MaFenetrePrincipale();

    private:
    QPushButton *m_bouton;
};


#endif
