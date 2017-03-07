#include "TabRecherche.h"



TabRecherche::TabRecherche(Tags *tags, QWidget* parent) : QWidgetO(parent)
{
    this->tags=tags;


    this->tagsSelected.clear();

    this->model = new QFileSystemModel(this);

    this->view = new QTreeView(this);
    this->view->show();
    this->view->setVisible(true);

    this->resultLabelRecherche=new QLabel(this);
    this->resultLabelRecherche->setText("");
    this->resultLabelRecherche->show();


    this->rechercher = new QPushButton("Rechercher",this);

    initialisationButtons();
}

void TabRecherche::initialisationButtons(){
    this->tagsSelected.clear();
    this->resultLabelRecherche->setGeometry(QRect(QPoint(0, 0),
                                    QSize(this->width()*2, this->height())));

    this->view->setGeometry(QRect(QPoint(0, 500),
                              QSize(this->width()*2,this->height()-300)));

    foreach (QPushButton* button, this->buttonsList) {
        button->setVisible(false);
        button->disconnect();
    }
    this->buttonsList.clear();
    int nbtag=0;
    foreach(Tag* tag, this->tags->getListTags()){
        if(!tag->getListWays().empty()){
            nbtag++;
            QPushButton* button = new QPushButton(tag->getName(),this);
            this->buttonsList.append(button);
            connect(button, SIGNAL(clicked()), this, SLOT(tagClicked()));
            button->setVisible(true);
        }
    }
    if(nbtag==0){
        QPushButton* button = new QPushButton("Aucun Tag",this);
        button->setFlat(true);
        this->buttonsList.append(button);
        connect(button, SIGNAL(clicked()), this, SLOT(aucunTag()));
        button->setVisible(true);
        this->rechercher->setFlat(true);
    }else{
        this->rechercher->setFlat(false);
    }

    int i = 0;
    foreach(QPushButton* button, this->buttonsList) {
        button->setGeometry(QRect(QPoint((i%10)*110, (i/10)*55),
                                                              QSize(100, 50)));
        button->setVisible(true);
        ++i;
    }
    this->rechercher->setGeometry(QRect(QPoint(((i)%10)+1*110, (((i)/10)+1)*55),
                                                          QSize(100, 50)));
    this->rechercher->setVisible(true);
    this->rechercher->disconnect();
    connect(this->rechercher, SIGNAL(clicked()), this, SLOT(recherche()));

}

void TabRecherche::tagClicked(){
    QPushButton *button = (QPushButton *)sender();
    if(button->isFlat()){
        button->setFlat(false);
        this->tagsSelected.removeAll(this->tags->getTag(button->text()));
//        QMessageBox::information(this,"Tag désélectionné", "Tag désélectionné "+button->text());
    }else{
        button->setFlat(true);
        this->tagsSelected.append(this->tags->getTag(button->text()));
//        QMessageBox::information(this,"Tag sélectionné", "Tag sélectionné "+button->text());
    }
    this->resultLabelRecherche->setText("");
}

void TabRecherche::aucunTag(){
    QMessageBox::critical(this,"Aucun Tag Disponible","Vous avez aucun Fichier ou dossier qui est taggé actuellement ! Pour se faire, il vous suffit de passer en Mode Edition.");
}

void TabRecherche::recherche(){
    QList<QString> resultList;
    if(!this->tagsSelected.isEmpty()){
        QList<QString> firstWays = this->tagsSelected.first()->getListWays();
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
        QString result ="résultat : ";
        int nb_way=1;
        foreach(QString way, resultList){
            if(nb_way==resultList.size()){
                result = result + way + ".";
            }else{
                result = result + way + ", ";
            }
        }
        this->resultLabelRecherche->setText(result);
    }else{
        QMessageBox::critical(this,"Aucun Tag sélectionné","Pour effectuer une recherche vous devez sélectionner un ou plusieurs tags.");
    }
}

TabRecherche::~TabRecherche()
{
}
