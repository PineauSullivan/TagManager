
#include "TabEdition.h"



TabEdition::TabEdition(QWidget* parent) : QWidget(parent)
{

    this->creerTag = new QPushButton("creerTag",this);
    connect(this->creerTag, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    this->AssocierTag = new QPushButton("Associer",this);

    //Gestion de la mise en forme du widget
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(this->creerTag);
    layout->addWidget(this->AssocierTag);
    this->setLayout(layout);
}

void TabEdition::buttonClicked()
{
    //Affichage d'une message box à l'utilisateur
    QMessageBox::information(this,"Création de tag","Créer un tag :");
}

TabEdition::~TabEdition()
{
}
