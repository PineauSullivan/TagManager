#include "Tag.h"

Tag::Tag(QString name)
{
    this->Name = name;
}

QList<QString> Tag::getListWays(){
    return this->ListWays;
}

void Tag::AddWay(QString way){
    if(!this->ListWays.contains(way)){
        this->ListWays.append(way);
    }
}

bool Tag::is(QString name){
    return (this->Name==name);
}

QString Tag::getName(){
    return this->Name;
}

Tag::~Tag()
{
}
