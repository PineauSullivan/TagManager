#include "TabRecherche.h"



TabRecherche::TabRecherche(Tags *tags, QWidget* parent) : QWidget(parent)
{
    this->tags=tags;
    for(int i = 0; i<tags->getListTags().size();++i){
        this->buttonsList.insert(i, new QPushButton(tags->getListTags().value(i),this));
    }
    this->rechercher = new QPushButton("Rechercher",this);

    initialisationButtons();
}

void TabRecherche::initialisationButtons(){
    int i;
    for(i = 0; i < this->buttonsList.size(); ++i) {
        this->buttonsList.value(i)->setGeometry(QRect(QPoint((i%3)*110, (i/3)*55),
                                                              QSize(100, 50)));
        this->buttonsList.value(i)->setVisible(true);

    }
    this->rechercher->setGeometry(QRect(QPoint(((i)%3)+1*110, (((i)/3)+1)*55),
                                                          QSize(100, 50)));
}

TabRecherche::~TabRecherche()
{
}
