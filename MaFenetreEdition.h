#ifndef MAFENETREEDITION_H
#define MAFENETREEDITION_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>

class MaFenetreEdition : public QWidget
{
    public:
    MaFenetreEdition();
    ~MaFenetreEdition();

    private:
    QPushButton *m_bouton;
};


#endif // MAFENETREEDITION_H
