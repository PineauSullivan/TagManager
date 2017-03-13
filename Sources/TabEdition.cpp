#include "Headers/TabEdition.h"



TabEdition::TabEdition(Tags *tags,QWidget* parent) : QWidgetO(parent)
{

    this->model = new QFileSystemModel(this);


    this->model->setRootPath("/");

    this->view = new QTreeView(this);
    this->view->setModel(this->model);
    QModelIndex idx = this->model->index("/home/");
    this->view->setRootIndex(idx);

    this->view->setColumnWidth(0,700);
    this->view->setColumnWidth(2,200);
    this->view->setColumnHidden(1,true);
    this->view->setColumnHidden(3,true);
    this->view->show();
    this->view->setVisible(true);
    connect(this->view,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(selected()));


    this->resultLabelTag=new QLabel(this);
    this->resultLabelTag->setText("");
    this->resultLabelTag->show();


    this->resultLabelWay=new QLabel(this);
    this->resultLabelWay->setText("");
    this->resultLabelWay->show();

    this->tags=tags;
    foreach(Tag* tag, tags->getListTags()){
        this->buttonsList.append(new QPushButtonPlus(tag->getName(),this));
    }
    this->creerTag = new QPushButton("+ Créer tag",this);
    connect(this->creerTag, SIGNAL(clicked()), this, SLOT(creationTag()));
    Style::setStyle(this->creerTag,3);

    this->associerTag = new QPushButton("Associer >",this);
    connect(this->associerTag, SIGNAL(clicked()), this, SLOT(association()));
    Style::setStyle(this->associerTag,1);

    this->menuTag = new QMenu(this);
    this->menuTag->addAction("Supprimer");
    connect(this->menuTag, SIGNAL(triggered(QAction*)), this, SLOT(supTag()));
    this->menuTag->setVisible(false);

    initialisationButtons();
    setLabels();

}

void TabEdition::creationTag()
{
    bool ok = false;
    QString tag = QInputDialog::getText(this, "Creation Tag", "Quel est le tag que vous voulez ajouter ?", QLineEdit::Normal, QString(), &ok);

    bool contain = false;
    foreach(Tag* ta, this->tags->getListTags()){
        if(ta->getName()==tag){
            contain = true;
        }
    }

    if (ok && !tag.isEmpty() && !contain)
    {
        QPushButtonPlus* button = new QPushButtonPlus(tag,this);
        Style::setStyle(button,1);
        this->buttonsList.append(button);
        this->tags->add_tag(tag, true);
        initialisationButtonsList();
        QMessageBox::information(this, "Tag", "Le " + tag + " a bien été ajouté.");
        this->tags->getTabRecherche()->initialisationButtons();
    }
    else
    {
        QMessageBox::critical(this, "Erreur Tag", "Aucun tag n'a été ajouté.");
    }
}

void TabEdition::tagClicked()
{
    QPushButton *button = (QPushButton *)sender();
    if(button->isFlat()){
        button->setFlat(false);
        Style::setStyle(button,1);
        this->tagsSelected.removeAll(this->tags->getTag(button->text()));
//        QMessageBox::information(this,"Tag désélectionné", "Tag désélectionné "+button->text());
    }else{
        button->setFlat(true);
        Style::setStyle(button,4);
        this->tagsSelected.append(this->tags->getTag(button->text()));
//        QMessageBox::information(this,"Tag sélectionné", "Tag sélectionné "+button->text());
    }
    setLabels();
}

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
        setLabels();
        this->tags->getTabRecherche()->initialisationButtons();
    }else{
        if(this->waysSelected.isEmpty()){
            QMessageBox::critical(this,"Association", "Veuillez selectionner au moins un fichier ou dossier.");
        }else{
            QMessageBox::critical(this,"Association", "Veuillez selectionner au moins un tag.");
        }
    }
}

QString TabEdition::toStringTag(){
    QString result = "Tag(s) sélectionné(s) : ";
    int i =1;
    foreach(Tag *tag, this->tagsSelected){
        if(this->tagsSelected.size()==i){
            result = result + tag->getName()+".";
        }else{
            result = result + tag->getName()+", ";
        }
        ++i;
    }
    return result;
}

QString TabEdition::toStringWay(){
    QString result = "Fichier(s) et/ou dossier(s) sélectionné(s) : ";
    int i = 1;
    foreach(QString way, this->waysSelected){
        if(this->waysSelected.size()==i){
            result = result + way+".";
        }else{
            result = result + way+", ";

        }
        ++i;
    }
    return result;
}

void TabEdition::setLabels(){
    this->resultLabelTag->setText(toStringTag());
    this->resultLabelWay->setText(toStringWay());
}


void TabEdition::initialisationButtons(){
    int i=0;
    this->view->setGeometry(QRect(QPoint(0, 0),
                              QSize(900, 600)));

    this->resultLabelTag->setGeometry(QRect(QPoint(0, 605),
                                    QSize(900, 50)));

    this->resultLabelWay->setGeometry(QRect(QPoint(0, 650),
                                    QSize(900, 50)));

    foreach(QPushButtonPlus* button, this->buttonsList){
        button->disconnect();
        button->setFlat(false);
        button->setGeometry(QRect(QPoint((i%3)*110+905, (i/3)*55),
                                                              QSize(100, 50)));
        connect(button, SIGNAL(leftClicked()), this, SLOT(tagClicked()));
        connect(button, SIGNAL(rightClicked()), this, SLOT(menuTagClicked()));
        Style::setStyle(button,1);
        button->setVisible(true);
        ++i;
    }

    this->creerTag->setGeometry(QRect(QPoint(((i)%3)*110+905, ((i)/3)*55),
                                                          QSize(100, 50)));
    this->associerTag->setGeometry(QRect(QPoint(((i)%3)+905, 625),
                                         QSize(325, 50)));
    clearSelected();
}
void TabEdition::menuTagClicked(){
    QPushButton *button = (QPushButton *)sender();


    if(this->menuTag->isVisible()){
        this->tagEnSuppression = NULL;
        this->menuTag->setVisible(false);
    }else{
        this->tagEnSuppression = this->tags->getTag(button->text());
        this->menuTag->setGeometry(QRect(QPoint(button->pos().x()+90,button->pos().y()+90),
                               QSize(112, 23)));
        this->menuTag->raise();
        this->menuTag->setVisible(true);
    }
}


void TabEdition::supTag(){
    QString nb = QString::number(this->tagEnSuppression->getListWays().size());
    int reponse = QMessageBox::question(this, "Suppression de Tag", "Etês vous sur de vouloir supprimer le Tag : "+this->tagEnSuppression->getName()+" qui possède "+nb+" fichier(s) associé(s) ?", QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        QString nomtag= this->tagEnSuppression->getName();
        this->tags->supprimerTag(this->tagEnSuppression);
        this->sup(nomtag);
        this->initialisationButtons();
        this->setLabels();
        this->tags->getTabRecherche()->initialisationButtons();
        this->menuTag->setVisible(false);
        QMessageBox::information(this, "Suppression de Tag", "Tag :"+nomtag+" supprimé");

    }
    this->menuTag->setVisible(false);

}
void TabEdition::initialisationButtonsList(){
    int i=0;

    foreach(QPushButtonPlus* button, this->buttonsList){
        button->disconnect();
        button->setGeometry(QRect(QPoint((i%3)*110+905, (i/3)*55),
                                                              QSize(100, 50)));
        connect(button, SIGNAL(leftClicked()), this, SLOT(tagClicked()));
        connect(button, SIGNAL(rightClicked()), this, SLOT(menuTagClicked()));
        button->setVisible(true);
        ++i;
    }

    this->creerTag->setGeometry(QRect(QPoint(((i)%3)*110+905, ((i)/3)*55),
                                                          QSize(100, 50)));
    this->associerTag->setGeometry(QRect(QPoint(((i)%3)+905, 625),
                                                          QSize(325, 50)));
}

void TabEdition::clearSelected(){
   this->tagsSelected.clear();
    this->waysSelected.clear();
}

void TabEdition::selected(){
    QModelIndex index = this->view->currentIndex();
    QFileInfo fileInfo = this->model->fileInfo(index);
    QString chemin = fileInfo.absoluteFilePath();
    if(this->waysSelected.contains(chemin)){
        this->waysSelected.removeAll(chemin);
        QMessageBox::information(this,"Fichier désélectionné", "Fichier désélectionné "+chemin);
    }else{
        this->waysSelected.append(chemin);
        QMessageBox::information(this,"Fichier sélectionné", "Fichier sélectionné "+chemin);
    }
    setLabels();
}

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
TabEdition::~TabEdition()
{
}
