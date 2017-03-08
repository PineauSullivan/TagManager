
#include "Tags.h"



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
    Tag* result;
    foreach(Tag* tag, this->ListTags){
        if(tag->is(tagName)){
            result =  tag;
        }
    }
    return result;
}

void Tags::add_tag(QString name){
    bool ok = true;
    foreach(Tag* tag, this->ListTags){
        if(tag->getName()==name){
            ok = false;
        }
    }
    if(ok){
        QFile file("Config.txt");
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&file);
            out << name << '\n';
        }
        this->ListTags.append(new Tag(name));
    }
}

void Tags::initialiserTagsFiles(){
    QFile inputFile("Config.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if(!line.isEmpty()){
            add_tag(line);
          }
       }
       inputFile.close();
    }
}

Tags::~Tags()
{
}
