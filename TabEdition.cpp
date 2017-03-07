#include "TabEdition.h"



TabEdition::TabEdition(Tags *tags,QWidget* parent) : QWidgetO(parent)
{
    this->model = new QFileSystemModel(this);
    this->model->setRootPath("E:\\");
    this->view = new QTreeView(this);
    this->view->setModel(this->model);
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
        this->buttonsList.append(new QPushButton(tag->getName(),this));
    }
    this->creerTag = new QPushButton("Créer tag",this);
    connect(this->creerTag, SIGNAL(clicked()), this, SLOT(creationTag()));

    this->associerTag = new QPushButton("Associer",this);
    connect(this->associerTag, SIGNAL(clicked()), this, SLOT(association()));

    initialisationButtons();
    setLabels();

}

void TabEdition::creationTag()
{
    bool ok = false;
    QString tag = QInputDialog::getText(this, "Creation Tag", "Quel est le tag que vous voulez ajouter ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !tag.isEmpty())
    {
        this->buttonsList.append(new QPushButton(tag,this));
        this->tags->add_tag(tag);
        initialisationButtons();
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
        this->tagsSelected.removeAll(this->tags->getTag(button->text()));
//        QMessageBox::information(this,"Tag désélectionné", "Tag désélectionné "+button->text());
    }else{
        button->setFlat(true);
        this->tagsSelected.append(this->tags->getTag(button->text()));
//        QMessageBox::information(this,"Tag sélectionné", "Tag sélectionné "+button->text());
    }
    setLabels();
}

void TabEdition::association()
{
    if(!this->tagsSelected.isEmpty() && !this->waysSelected.isEmpty()){
        QString text = "tags : ";
        foreach(Tag *tag, this->tagsSelected){
            text = text + tag->getName()+", ";
        }
        text = text + "; chemin : ";

        foreach(QString way, this->waysSelected){
            text = text + way+", ";
        }

        foreach(Tag* tag, this->tagsSelected){
            foreach(QString way, this->waysSelected){
                tag->AddWay(way);
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

    foreach(QPushButton* button, this->buttonsList){
        button->disconnect();
        button->setFlat(false);
        button->setGeometry(QRect(QPoint((i%3)*110+905, (i/3)*55),
                                                              QSize(100, 50)));
        connect(button, SIGNAL(clicked()), this, SLOT(tagClicked()));
        button->setVisible(true);
        ++i;
    }

    this->creerTag->setGeometry(QRect(QPoint(((i)%3)*110+905, ((i)/3)*55),
                                                          QSize(100, 50)));
    this->associerTag->setGeometry(QRect(QPoint(((i)%3)+1*110+905, (((i)/3)+1)*55),
                                                          QSize(100, 50)));
    clearSelected();
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

TabEdition::~TabEdition()
{
}
