/**
* @file TabEdition.cpp
* @author G. Killian, P. Sullivan
* @since 14/03/2017
* @brief implémentation des méthodes de la classe TabEdition
*
**/

//****************************************************************************************************
#include "Headers/TabEdition.h"

//****************************************************************************************************
TabEdition::TabEdition(Tags *tags,QWidget* parent) : QWidgetO(parent)
{

    setMouseTracking(true); //Lance le tracking de la souris

    this->model = new QDirModel(this); //initialise le model
    QModelIndex idx = this->model->index(QDir::homePath());

    //initialisation de la view
    this->view = new QTreeView(this);
    this->view->setModel(this->model);
    this->view->setRootIndex(idx);
    this->view->setColumnWidth(0,700);
    this->view->setColumnWidth(2,200);
    this->view->setColumnHidden(1,true);
    this->view->setColumnHidden(3,true);
    this->view->show();
    this->view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->view->setVisible(true);

    //initialiser tags
    this->tags=tags;

    //initialise la liste des tags
    foreach(Tag* tag, tags->getListTags()){
        this->buttonsList.append(new QPushButtonPlus(tag->getName(),this));
    }

    //initialise le bouton créerTag
    this->creerTag = new QPushButton("+ Créer tag",this);

    //Set le style du boutton créerTag (vert clair)
    Style::setStyle(this->creerTag,5);

    //initialise le bouton associerTag
    this->associerTag = new QPushButton("Associer >",this);


    //set le style du boutton associerTag (vert clair)
    Style::setStyle(this->associerTag,5);

    //initialiser le menuTag
    this->menuTag = new QMenu(this);
    this->menuTag->addAction("Supprimer");
    this->menuTag->setVisible(false);

    //connect la view a chaque click au slot selectedAuto
    connect(this->view,SIGNAL(clicked(QModelIndex)),this, SLOT(selectedAuto()));

    //connect le boutton créerTag au slot créationTag
    connect(this->creerTag, SIGNAL(clicked()), this, SLOT(creationTag()));

    //connect le boutton associerTag au slot association()
    connect(this->associerTag, SIGNAL(clicked()), this, SLOT(association()));

    //connect le menuTag au slot supTag
    connect(this->menuTag, SIGNAL(triggered(QAction*)), this, SLOT(supTag()));

    //initialisation de tout les bouttons (position/dimension)
    initialisationButtons();
}

//****************************************************************************************************
void TabEdition::creationTag()
{
    bool choix = false;
    QString tagName = QInputDialog::getText(this, "Creation Tag", "Quel est le tag que vous voulez ajouter ?", QLineEdit::Normal, QString(), &choix);

    bool contain = false;
    foreach(Tag* tag, this->tags->getListTags()){
        if(tag->getName()==tagName){
            contain = true;
        }
    }
    if (choix && !tagName.isEmpty() && !contain)
    {
        if(tagName.size()<11){
            QPushButtonPlus* button = new QPushButtonPlus(tagName,this);
            Style::setStyle(button,1);
            this->buttonsList.append(button);
            this->tags->add_tag(tagName, true);
            initialisationButtonsList();
            QMessageBox::information(this, "Tag", "Le " + tagName + " a bien été ajouté.");
            this->tags->getTabRecherche()->initialisationButtons();

        }else{
            QMessageBox::critical(this, "Erreur création Tag", "Veuillez saisir un nom de tag inférieur ou égal à 10 caractères.");
        }
    }
    else
    {
        QMessageBox::critical(this, "Erreur création Tag", "Aucun tag n'a été ajouté.");
    }
}

//****************************************************************************************************
void TabEdition::tagClicked()
{
    QPushButton *button = (QPushButton *)sender();
    if(button->isFlat()){
        button->setFlat(false);
        Style::setStyle(button,1);
        this->tagsSelected.removeAll(this->tags->getTag(button->text()));
    }else{
        button->setFlat(true);
        Style::setStyle(button,4);
        this->tagsSelected.append(this->tags->getTag(button->text()));
    }
}

//****************************************************************************************************
void TabEdition::association()
{
    if(!this->tagsSelected.isEmpty() && !this->waysSelected.isEmpty()){
        QString text = "tag(s) : ";
        int nb_tag = 1;
        foreach(Tag *tag, this->tagsSelected){
            if(nb_tag==this->tagsSelected.size())
                text = text + tag->getName()+" ";
            else
                text = text + tag->getName()+", ";
            nb_tag++;
        }
        text = text + "; chemin(s) : ";

        int nb_chemin = 1;
        foreach(QString way, this->waysSelected){
            if(nb_chemin == this->waysSelected.size())
                text = text + way+".";
            else
                text = text + way+", ";
        }

        foreach(Tag* tag, this->tagsSelected){
            foreach(QString way, this->waysSelected){
                tag->AddWay(way, true);
            }
        }

        QMessageBox::information(this,"Association", "Association sélectionné "+text);
        initialisationButtons();
        clearSelected();
        this->tags->getTabRecherche()->initialisationButtons();
    }else{
        if(this->waysSelected.isEmpty()){
            QMessageBox::critical(this,"Association", "Veuillez selectionner au moins un fichier ou dossier.");
        }else{
            QMessageBox::critical(this,"Association", "Veuillez selectionner au moins un tag.");
        }
    }
}


//****************************************************************************************************
void TabEdition::initialisationButtons(){
    

    int i=0;
    foreach(QPushButtonPlus* button, this->buttonsList){
        button->disconnect();
        button->setFlat(false);
        button->setGeometry(QRect(QPoint((i%3)*110+905, (i/3)*55),QSize(100, 50)));

        //connect le clic gauche avec le slot tagClicked
        connect(button, SIGNAL(leftClicked()), this, SLOT(tagClicked()));

        //connect le clic droit avec le slot menuTagClicked
        connect(button, SIGNAL(rightClicked()), this, SLOT(menuTagClicked()));

        //set le style du boutton (jaune)
        Style::setStyle(button,1);
        button->setVisible(true);
        ++i;
    }

    this->view->setGeometry(QRect(QPoint(0, 0),QSize(900, 700)));

    this->creerTag->setGeometry(QRect(QPoint(((i)%3)*110+905, ((i)/3)*55),QSize(100, 50)));

    this->associerTag->setGeometry(QRect(QPoint(((i)%3)+905, 650),QSize(325, 50)));

    clearSelected();
}

//****************************************************************************************************
void TabEdition::menuTagClicked(){
    //récupération du boutton cliqué
    QPushButtonPlus *button = (QPushButtonPlus *)sender();

    if(this->menuTag->isVisible()){
        this->tagEnSuppression = NULL;
        this->menuTag->setVisible(false);
    }else{
        this->tagEnSuppression = this->tags->getTag(button->text());
        this->menuTag->setGeometry(QRect(QPoint(button->getPos().x()+button->x()+50,button->getPos().y()+button->y()+53),QSize(112, 23)));
        this->menuTag->raise();
        this->menuTag->setVisible(true);
    }
}

//****************************************************************************************************
void TabEdition::supTag(){
    QString nb = QString::number(this->tagEnSuppression->getListWays().size());
    int reponse = QMessageBox::question(this, "Suppression de Tag", "Etês vous sur de vouloir supprimer le Tag : "+this->tagEnSuppression->getName()+" qui possède "+nb+" fichier(s) associé(s) ?", QMessageBox ::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QString nomtag= this->tagEnSuppression->getName();
        this->tags->supprimerTag(this->tagEnSuppression);
        this->sup(nomtag);
        this->initialisationButtons();
        this->tags->getTabRecherche()->initialisationButtons();
        this->menuTag->setVisible(false);
        QMessageBox::information(this, "Suppression de Tag", "Tag : "+nomtag+" a bien été supprimé.");

    }
    this->menuTag->setVisible(false);

}

//****************************************************************************************************
void TabEdition::initialisationButtonsList(){
    int i=0;
    foreach(QPushButtonPlus* button, this->buttonsList){
        button->disconnect();
        button->setGeometry(QRect(QPoint((i%3)*110+905, (i/3)*55),QSize(100, 50)));
        connect(button, SIGNAL(leftClicked()), this, SLOT(tagClicked()));
        connect(button, SIGNAL(rightClicked()), this, SLOT(menuTagClicked()));
        button->setVisible(true);
        ++i;
    }
    this->creerTag->setGeometry(QRect(QPoint(((i)%3)*110+905, ((i)/3)*55),QSize(100, 50)));
    this->associerTag->setGeometry(QRect(QPoint(((i)%3)+905, 625),QSize(325, 50)));
}

//****************************************************************************************************
void TabEdition::clearSelected(){
   this->tagsSelected.clear();
    this->waysSelected.clear();
}

//****************************************************************************************************
void TabEdition::selectedAuto(){
    this->waysSelected.clear();
    foreach(QModelIndex index, this->view->selectionModel()->selectedIndexes()){
        QFileInfo fileInfo = this->model->fileInfo(index);
        QString chemin = fileInfo.absoluteFilePath();
        if(!this->waysSelected.contains(chemin)){
            this->waysSelected.append(chemin);
        }
    }
}

//****************************************************************************************************
void TabEdition::sup(QString name){
    int pos = 0;
    for(int i =0; i<this->buttonsList.size();++i){
        if(this->buttonsList.at(i)->text() == name){
            pos = i;
            i= this->buttonsList.size();
        }
    }
    this->buttonsList.at(pos)->disconnect();
    this->buttonsList.at(pos)->setVisible(false);
    this->buttonsList.removeAt(pos);
    this->initialisationButtonsList();
    this->initialisationButtons();
}

//****************************************************************************************************
void TabEdition::messageAide(){
    QMessageBox::information(this,"Aide Edition", "Comment créer un tag ?<br/>"
                                          "Cliquer sur 'créer tag'.<br/><br/>"
                                          "Comment associer un ou plusieus éléments à un ou plusieurs tags ?<br/>"
                                          "Cliquer sur les éléments et sur les tags puis sur le boutton Associer. <br/><br/>"
                                          "Comment supprimer un tag ?<br/>"
                                          "Utiliser le clic droit sur le tag en question.<br/>");
}

//****************************************************************************************************
TabEdition::~TabEdition()
{
}
