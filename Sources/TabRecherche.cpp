#include "Headers/TabRecherche.h"



TabRecherche::TabRecherche(Tags *tags, QWidget* parent) : QWidgetO(parent)
{
    this->tags=tags;


    this->tagsSelected.clear();

    this->view = new MyView(this);
    this->view->show();
    this->view->setVisible(true);

    this->view->setGeometry(QRect(QPoint(0, 200),
                              QSize(this->width()*2,this->height())));
    connect(this->view,SIGNAL(doubleClicked()), this, SLOT(lancer()));
    connect(this->view,SIGNAL(rightClicked()), this, SLOT(menuWayClicked()));

    this->menuWay = new QMenu(this);
    QAction *menuAction;

    menuAction = this->menuWay->addAction("lancer");
    connect(menuAction, SIGNAL(triggered()), this, SLOT(lancer()));

    menuAction = this->menuWay->addAction("supprimer");
    connect(menuAction, SIGNAL(triggered()), this, SLOT(supWay()));

    this->menuWay->setVisible(false);

    this->menuTag = new QMenu(this);
    this->menuTag->addAction("Supprimer");
    connect(this->menuTag, SIGNAL(triggered(QAction*)), this, SLOT(supTag()));
    this->menuTag->setVisible(false);

    this->modeRecherche = new QCheckBox("Mode Recherche ET logique",this);
    this->modeRecherche->setGeometry(QRect(QPoint((9)*110, 3*55+5),
                                                         QSize(220, 25)));

    connect(this->modeRecherche,SIGNAL(stateChanged(int)), this, SLOT(checkboxChanged()));
    this->modeRecherche->setVisible(true);
    initialisationButtons();
}

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

            connect(button, SIGNAL(leftClicked()), this, SLOT(tagClicked()));
            connect(button, SIGNAL(rightClicked()), this, SLOT(menuTagClicked()));
            button->setVisible(true);
        }
    }
    if(nbtag==0){
        QPushButtonPlus* button = new QPushButtonPlus("Aucun Tag",this);
        this->buttonsList.append(button);
        Style::setStyle(button, 2);
        connect(button, SIGNAL(leftClicked()), this, SLOT(aucunTag()));
        button->setVisible(true);
    }
    int i = 0;
    foreach(QPushButton* button, this->buttonsList) {
        button->setGeometry(QRect(QPoint((i%10)*110, (i/10)*55+5),
                                                              QSize(100, 50)));
        button->setVisible(true);
        ++i;
    }


}

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

void TabRecherche::aucunTag(){
    QMessageBox::critical(this,"Aucun Tag Disponible","Vous avez aucun Fichier ou dossier qui est taggé actuellement ! Pour se faire, il vous suffit de passer en Mode Edition.");
}

void TabRecherche::recherche(){
    QList<QString> resultList;
    if(!this->tagsSelected.isEmpty()){
        QList<QString> firstWays = this->tagsSelected.first()->getListWays();
        if(this->modeRecherche->isChecked()){
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


void TabRecherche::menuTagClicked(){
    this->menuWay->setVisible(false);

    QPushButtonPlus *button = (QPushButtonPlus *)sender();

    if(this->menuTag->isVisible()){
        this->tagEnSuppression = NULL;
        this->menuTag->setVisible(false);
    }else{
        this->tagEnSuppression = this->tags->getTag(button->text());
        this->menuTag->setGeometry(QRect(QPoint(button->getPos().x()+button->x()+this->pos().x()+50,button->getPos().y()+button->y()+this->pos().y()+53),
                               QSize(112, 23)));
        this->menuTag->raise();
        this->menuTag->setVisible(true);
    }
}

void TabRecherche::menuWayClicked(){
    this->menuTag->setVisible(false);
    QModelIndex index = this->view->currentIndex();

    QString chemin = index.data().toString();

    if(this->menuWay->isVisible()||this->tagsSelected.empty()){
        this->menuWay->setVisible(false);
    }else{
        this->menuWay->setGeometry(QRect(QPoint(this->view->getPos().x()+this->view->x()+77,this->view->getPos().y()+this->view->y()+80),
                                         QSize(112, 46)));
        this->menuWay->raise();
        this->menuWay->setVisible(true);
    }

}

void TabRecherche::lancer(){
    this->menuWay->setVisible(false);
    QModelIndex index = this->view->currentIndex();
    QString chemin = index.data().toString();

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(chemin)))
    {
        QMessageBox::critical(this,"Erreur d'ouverture", "Il est impossible d'ouvrir le fichier/dossier : "+chemin+".");
    }
}
void TabRecherche::sup(QString name){
    if(name == ""){
    }else{

    }
}

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

void TabRecherche::checkboxChanged(){
    if(!this->tagsSelected.isEmpty()){
        recherche();
    }
}

TabRecherche::~TabRecherche()
{
}
