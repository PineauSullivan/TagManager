
#include "Tags.h"



Tags::Tags()
{
    this->ListTags.append(new Tag("Rock"));
    this->ListTags.append(new Tag("Classique"));
    this->ListTags.append(new Tag("RNB"));
    this->ListTags.append(new Tag("RAP"));
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
    this->ListTags.append(new Tag(name));
}

Tags::~Tags()
{
}
