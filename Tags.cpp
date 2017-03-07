
#include "Tags.h"



Tags::Tags()
{
    this->ListTags.insert(0,"Rock");
    this->ListTags.insert(1,"Classique");
    this->ListTags.insert(2,"RNB");
    this->ListTags.insert(3,"RAP");
}

QHash<int, QString> Tags::getListTags(){
    return this->ListTags;
}

void Tags::add_tag(QString name){
    this->ListTags.insert(this->ListTags.size(),name);
}

Tags::~Tags()
{
}
