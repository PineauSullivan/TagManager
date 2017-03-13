
#include "Headers/Tags.h"



Tags::Tags()
{
    initialiserTagsFiles();
}

QList<Tag*> Tags::getListTags(){
    return this->ListTags;
}
void Tags::setQWidgetRecherche(QWidgetO* TabRecherche){
    this->TabRecherche=TabRecherche;
}

void Tags::setQWidgetEdition(QWidgetO* TabEdition){
    this->TabEdition=TabEdition;
}

QWidgetO* Tags::getTabRecherche(){
    return this->TabRecherche;
}

QWidgetO* Tags::getTabEdition(){
    return this->TabEdition;
}

Tag* Tags::getTag(QString tagName){
    Tag* result = NULL;
    foreach(Tag* tag, this->ListTags){
        if(tag->is(tagName)){
            result =  tag;
        }
    }
    return result;
}

void Tags::add_tag(QString name, bool write){
    bool ok = true;
    foreach(Tag* tag, this->ListTags){
        if(tag->getName()==name||tag->getName()==name+"'\n"){
            ok = false;
        }
    }
    if(ok){
        if(write){
            QFile file("Configs/Config.txt");
            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream out(&file);
                out << name << '\n';
            }
        }
        this->ListTags.append(new Tag(name));
    }
}

void Tags::supprimerTag(Tag* tag){
    QFile file("Configs/ConfigTag"+tag->getName()+".txt");
    file.remove();
    QFile fileConfigBefore("Configs/Config.txt");
    fileConfigBefore.remove();
    this->ListTags.removeAll(tag);
    foreach(Tag* tag, this->ListTags){
        QFile file("Configs/Config.txt");
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&file);
            out << tag->getName() << '\n';
        }
    }
    tag->~Tag();

}

void Tags::initialiserTagsFiles(){
    QFile inputFile("Configs/Config.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if(!line.isEmpty()){
              add_tag(line, false);
          }
       }
       inputFile.close();
    }
}


Tags::~Tags()
{
}
