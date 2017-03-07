
#include "TabEdition.h"



TabEdition::TabEdition(QWidget* parent) : QWidget(parent)
{
    this->creerTag = new QPushButton("Créer tag",this);
    this->AssocierTag = new QPushButton("Associer",this);

    initialisationButtons();

}

void TabEdition::creationTag()
{
    bool ok = false;
    QString tag = QInputDialog::getText(this, "Creation Tag", "Quel est le tag que vous voulez ajouter ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !tag.isEmpty())
    {
        this->buttonsList.insert(this->buttonsList.size(), new QPushButton(tag,this));
        initialisationButtons();
        QMessageBox::information(this, "Tag", "Le " + tag + " a bien été ajouté.");
    }
    else
    {
        QMessageBox::critical(this, "Erreur Tag", "Aucun tag n'a été ajouté.");
    }
}

void TabEdition::tagClicked()
{
    QMessageBox::information(this,"Tag sélectionné", "Tag sélectionné");
}

void TabEdition::association()
{
    QMessageBox::information(this,"Association sélectionné", "Association sélectionné");
}

void TabEdition::initialisationButtons(){
    int i;
    for(i = 0; i < this->buttonsList.size(); ++i) {
        this->buttonsList.value(i)->setGeometry(QRect(QPoint((i%3)*110, (i/3)*55),
                                                              QSize(100, 50)));
        connect(this->buttonsList.value(i), SIGNAL(clicked()), this, SLOT(tagClicked()));
        this->buttonsList.value(i)->setVisible(true);

    }

    connect(this->creerTag, SIGNAL(clicked()), this, SLOT(creationTag()));
    this->creerTag->setGeometry(QRect(QPoint(((i)%3)*110, ((i)/3)*55),
                                                          QSize(100, 50)));

    connect(this->AssocierTag, SIGNAL(clicked()), this, SLOT(association()));
    this->AssocierTag->setGeometry(QRect(QPoint(((i)%3)+1*110, (((i)/3)+1)*55),
                                                          QSize(100, 50)));
}

TabEdition::~TabEdition()
{
}
