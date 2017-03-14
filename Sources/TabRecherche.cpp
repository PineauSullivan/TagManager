/**
* @file TabRecherche.cpp
* @author G. Killian, P. Sullivan
* @since 14/03/2017
* @brief implémentation des méthodes de la classe QPushButtonPlus
*
**/

//****************************************************************************************************
#include "Headers/TabRecherche.h"

//****************************************************************************************************
TabRecherche::TabRecherche(Tags *tags, QWidget* parent) : QWidgetO(parent)
{
    //initialisation des tags
    this->tags=tags;
    this->tagsSelected.clear();

    //initialisation de la view
    this->view = new MyView(this);
    this->view->show();
    this->view->setVisible(true);
    this->view->setGeometry(QRect(QPoint(0, 200),QSize(1300,500)));

    //initialisation du menuWay (pour la view)
    this->menuWay = new QMenu(this);
    
    //initialisation du menuLancer
    QAction *menuLancer;
    menuLancer = this->menuWay->addAction("lancer");
    
    //initialisation du menuSup
    QAction * menuSup;
    menuSup = this->menuWay->addAction("supprimer");

    this->menuWay->setVisible(false);

    //initialisation du menu Tag
    this->menuTag = new QMenu(this);
    this->menuTag->addAction("Supprimer");
    this->menuTag->setVisible(false);

    //initialisation de la checkbox ET
    this->modeRechercheET = new QCheckBox("Recherche ET",this);
    this->modeRechercheET->setGeometry(QRect(QPoint((9)*110, 3*55+5),QSize(130, 25)));
    this->modeRechercheET->setVisible(true);

    //initialisation de la checkbox OU
    this->modeRechercheOU = new QCheckBox("Recherche OU",this);
    this->modeRechercheOU->setGeometry(QRect(QPoint((9)*110 + 135, 3*55+5),QSize(130, 25)));
    this->modeRechercheOU->setChecked(true);
    this->modeRechercheOU->setVisible(true);

    //connect double clic de la view vers le slot lancer
    connect(this->view,SIGNAL(doubleClicked()), this, SLOT(lancer()));

    //connect clic droit de la view vers le slot menuWayClicked
    connect(this->view,SIGNAL(rightClicked()), this, SLOT(menuWayClicked()));

    //connect du menuLancer vers le slot Lancer 
    connect(menuLancer, SIGNAL(triggered()), this, SLOT(lancer()));
    
    //connect du menuSup vers le slot supWay
    connect(menuSup, SIGNAL(triggered()), this, SLOT(supWay()));
    
    //initialisation du menuTag vers le slot supTag
    connect(this->menuTag, SIGNAL(triggered(QAction*)), this, SLOT(supTag()));
    
    //connect clic sur la checkbox ET vers checkboxETChanged
    connect(this->modeRechercheET,SIGNAL(clicked(bool)), this, SLOT(checkboxETChanged()));

    //connect clic sur la checkbox OU vers checkboxOUChanged
    connect(this->modeRechercheOU,SIGNAL(clicked(bool)), this, SLOT(checkboxOUChanged()));

    initialisationButtons();

}

//****************************************************************************************************
void TabRecherche::initialisationButtons(){
    this->tagsSelected.clear();
    this->view->setModel(NULL);
    foreach (QPushButton* button, this->buttonsList) {
        button->setVisible(false);
        button->disconnect();
    }
    this->buttonsList.clear();
    int nbtag=0;
    foreach(Tag* tag, this->tags->getListTags()){
        if(!tag->getListWays().empty()){
            nbtag++;
            QPushButtonPlus* button = new QPushButtonPlus(tag->getName(),this);
            this->buttonsList.append(button);
            Style::setStyle(button, 1);

            //connect un clic gauche du boutton vers le slot tagClicked()
            connect(button, SIGNAL(leftClicked()), this, SLOT(tagClicked()));

            //connect un clic droit du boutton vers le slot menuTagClicked()
            connect(button, SIGNAL(rightClicked()), this, SLOT(menuTagClicked()));
            button->setVisible(true);
        }
    }
    int i = 0;
    foreach(QPushButton* button, this->buttonsList) {
        button->setGeometry(QRect(QPoint((i%10)*110, (i/10)*55+5),QSize(100, 50)));
        button->setVisible(true);
        ++i;
    }
    if(nbtag==0){
        QPushButtonPlus* button = new QPushButtonPlus("Aucun fichier/dossier associé",this);
        this->buttonsList.append(button);
        Style::setStyle(button, 2);
        button->setGeometry(QRect(QPoint((0%10)*110, (0/10)*55+5),QSize(220, 50)));
        connect(button, SIGNAL(leftClicked()), this, SLOT(aucunTag()));
        button->setVisible(true);
    }


}

//****************************************************************************************************
void TabRecherche::tagClicked(){
    QPushButton *button = (QPushButton *)sender();
    if(button->isFlat()){
        Style::setStyle(button, 1);
        button->setFlat(false);
        this->tagsSelected.removeAll(this->tags->getTag(button->text()));
        if(this->tagsSelected.size()!=0){
            recherche();
        }else{
            this->view->setModel(NULL);
        }
    }else{
        Style::setStyle(button, 4);
        button->setFlat(true);
        this->tagsSelected.append(this->tags->getTag(button->text()));
        recherche();
    }
}

//****************************************************************************************************
void TabRecherche::aucunTag(){
    QMessageBox::critical(this,"Aucun Tag Disponible","Vous avez aucun Fichier ou dossier qui est taggé actuellement ! Pour se faire, il vous suffit de passer en Mode Edition.");
}

//****************************************************************************************************
void TabRecherche::recherche(){
    QList<QString> resultList;
    if(!this->tagsSelected.isEmpty()){
        QList<QString> firstWays = this->tagsSelected.first()->getListWays();
        if(this->modeRechercheET->isChecked()){
            bool ok = true;
            foreach(QString way, firstWays){
                ok = true;
                foreach(Tag* tag, this->tagsSelected){
                    if(!tag->getListWays().contains(way)){
                        ok = false;
                    }
                }
                if(ok){
                    if(!resultList.contains(way)){
                        resultList.append(way);
                    }
                }
            }
        }else{
            foreach(Tag* tag, this->tagsSelected){
                foreach(QString way, tag->getListWays()){
                    if(!resultList.contains(way)){
                        resultList.append(way);
                    }
                }
            }
        }

        if(!resultList.empty()){
            this->model = new QStandardItemModel(this);
            this->model->setColumnCount(1);
            this->model->setRowCount(resultList.size());
            int nb_way=1;
            foreach(QString way, resultList){
                this->model->setData(this->model->index(nb_way-1, 0), way);
                nb_way++;
            }
            this->view->setModel(this->model);
            this->view->show();
            this->view->setColumnWidth(0,this->width()*2);
            this->view->setVisible(true);

        }else{
            this->view->setModel(NULL);
        }
    }else{
        QMessageBox::critical(this,"Aucun Tag sélectionné","Pour effectuer une recherche vous devez sélectionner un ou plusieurs tags.");
    }
}

//****************************************************************************************************
void TabRecherche::supTag(){
    QString nb = QString::number(this->tagEnSuppression->getListWays().size());
    int reponse = QMessageBox::question(this, "Suppression de Tag", "Etês vous sur de vouloir supprimer le Tag : "+this->tagEnSuppression->getName()+" qui possède "+nb+" fichier(s) associé(s) ?", QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        QString nomtag= this->tagEnSuppression->getName();
        this->tags->supprimerTag(this->tagEnSuppression);
        this->tags->getTabEdition()->sup(nomtag);
        this->initialisationButtons();
        this->menuTag->setVisible(false);
        this->view->setModel(NULL);
        QMessageBox::information(this, "Suppression de Tag", "Tag : "+nomtag+" a bien été supprimé.");

    }
    this->menuTag->setVisible(false);

}

//****************************************************************************************************
void TabRecherche::menuTagClicked(){
    this->menuWay->setVisible(false);

    QPushButtonPlus *button = (QPushButtonPlus *)sender();

    if(this->menuTag->isVisible()){
        this->tagEnSuppression = NULL;
        this->menuTag->setVisible(false);
    }else{
        this->tagEnSuppression = this->tags->getTag(button->text());
        this->menuTag->setGeometry(QRect(QPoint(button->getPos().x()+button->x()+this->pos().x()+50,button->getPos().y()+button->y()+this->pos().y()+53),QSize(112, 23)));
        this->menuTag->raise();
        this->menuTag->setVisible(true);
    }
}

//****************************************************************************************************
void TabRecherche::menuWayClicked(){
    this->menuTag->setVisible(false);
    QModelIndex index = this->view->currentIndex();

    QString chemin = index.data().toString();

    if(this->menuWay->isVisible()||this->tagsSelected.empty()){
        this->menuWay->setVisible(false);
    }else{
        this->menuWay->setGeometry(QRect(QPoint(this->view->getPos().x()+this->view->x()+77,this->view->getPos().y()+this->view->y()+80),QSize(112, 46)));
        this->menuWay->raise();
        this->menuWay->setVisible(true);
    }

}

//****************************************************************************************************
void TabRecherche::lancer(){
    this->menuWay->setVisible(false);
    QModelIndex index = this->view->currentIndex();
    QString chemin = index.data().toString();

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(chemin)))
    {
        QMessageBox::critical(this,"Erreur d'ouverture", "Il est impossible d'ouvrir le fichier/dossier : "+chemin+".");
    }
}

//****************************************************************************************************
void TabRecherche::sup(QString name){
    if(name==""){
        
    }
}

//****************************************************************************************************
void TabRecherche::supWay(){

    this->menuWay->setVisible(false);
    QModelIndex index = this->view->currentIndex();
    QString chemin = index.data().toString();
    QMessageBox msgBox;
    msgBox.setText("Suppression d'associations.");
    msgBox.setInformativeText("Veuillez selectionner les différents tags que vous souhaitez désassocier de '"+chemin+"' : ");
    QList<QCheckBox*> list_check;
    foreach(Tag* tag, this->tags->getListTags()){
        if(tag->tagPossedant(chemin)){
            QCheckBox* dontPrompt = new QCheckBox(tag->getName(), &msgBox);
            dontPrompt->blockSignals(true);
            msgBox.addButton(dontPrompt, QMessageBox::ActionRole);
            list_check.push_back(dontPrompt);
        }
    }


    msgBox.addButton(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::Cancel);
    int res = msgBox.exec();
    int nb=0;
    foreach(QCheckBox* box, list_check){
        if ( box->checkState() == Qt::Checked && res == QMessageBox::Yes)
        {
            this->tags->getTag(box->text())->supWay(chemin);
            nb++;
        }
    }
    if(nb>0){
        this->view->setModel(NULL);
        QMessageBox::information(this,"Information", "Vos modifications ont bien été prise.");
        this->initialisationButtons();
    }else{
        QMessageBox::information(this,"Information", "Aucune désassociation a été effectuée.");
    }
}

//****************************************************************************************************
void TabRecherche::checkboxETChanged(){
    this->modeRechercheET->setChecked(true);
    this->modeRechercheOU->setChecked(false);

    if(!this->tagsSelected.isEmpty()){
        recherche();
    }
}

//****************************************************************************************************
void TabRecherche::checkboxOUChanged(){
    this->modeRechercheET->setChecked(false);
    this->modeRechercheOU->setChecked(true);

    if(!this->tagsSelected.isEmpty()){
        recherche();
    }
}

//****************************************************************************************************
void TabRecherche::messageAide(){
    QMessageBox::information(this,"Aide Recherche", "Pourquoi je n'ai pas de tag ? <br/> "
                                          "Il faut créer au moins un tag puis l'associer à l'aide du mode Edition.<br/><br/>"
                                          "A quoi correspondent les deux modes de recherche ? <br/>"
                                          "Mode ET : filtre les éléments qui possèdent la totalité des tags sélectionnés.<br/>"
                                          "Mode OU : filtre les éléments qui possèdent au moins un des tags sélectionnés.<br/><br/>"
                                          "Comment lancer ou dissocier un élément d'un tag ou supprimer un tag ?<br/>"
                                          "Utiliser le clic droit sur le chemin de l'élément en question.<br/>");
}

//****************************************************************************************************
TabRecherche::~TabRecherche()
{
}
