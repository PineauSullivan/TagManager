#include "TabEdition.h"



TabEdition::TabEdition(Tags *tags,QWidget* parent) : QWidget(parent)
{
    this->model = new QFileSystemModel(this);
    this->model->setRootPath("E:\\");
    this->view = new QTreeView(this);
    this->view->setModel(this->model);
    this->view->show();
    this->view->setVisible(true);

    this->tags=tags;
    for(int i = 0; i<tags->getListTags().size();++i){
        this->buttonsList.insert(this->buttonsList.size(), new QPushButton(tags->getListTags().value(i),this));
    }
    this->creerTag = new QPushButton("Créer tag",this);
    connect(this->creerTag, SIGNAL(clicked()), this, SLOT(creationTag()));

    this->associerTag = new QPushButton("Associer",this);
    connect(this->associerTag, SIGNAL(clicked()), this, SLOT(association()));

    initialisationButtons();

}

void TabEdition::creationTag()
{
    bool ok = false;
    QString tag = QInputDialog::getText(this, "Creation Tag", "Quel est le tag que vous voulez ajouter ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !tag.isEmpty())
    {
        this->buttonsList.insert(this->buttonsList.size(), new QPushButton(tag,this));
        this->tags->add_tag(tag);
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
    this->view->setGeometry(QRect(QPoint(0, 0),
                              QSize(900, 600)));

    for(i = 0; i < this->buttonsList.size(); ++i) {
        this->buttonsList.value(i)->setGeometry(QRect(QPoint((i%3)*110+905, (i/3)*55),
                                                              QSize(100, 50)));
        connect(this->buttonsList.value(i), SIGNAL(clicked()), this, SLOT(tagClicked()));
        this->buttonsList.value(i)->setVisible(true);

    }

    this->creerTag->setGeometry(QRect(QPoint(((i)%3)*110+905, ((i)/3)*55),
                                                          QSize(100, 50)));
    this->associerTag->setGeometry(QRect(QPoint(((i)%3)+1*110+905, (((i)/3)+1)*55),
                                                          QSize(100, 50)));
}

TabEdition::~TabEdition()
{
}
