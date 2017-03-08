#include "Tag.h"

Tag::Tag(QString name)
{
    this->Name = name;
    initialiserTagFiles();
}

QList<QString> Tag::getListWays(){
    return this->ListWays;
}

void Tag::AddWay(QString way, bool write){
    if(!this->ListWays.contains(way) && !this->ListWays.contains(way+'\n')){
        QFile file("ConfigTag"+this->Name+".txt");
        if (file.open(QIODevice::Append | QIODevice::Text) && write)
        {
            QTextStream out(&file);
            out << way << '\n';
        }
        this->ListWays.append(way);
    }
}

bool Tag::is(QString name){
    return (this->Name==name);
}

QString Tag::getName(){
    return this->Name;
}

void Tag::initialiserTagFiles(){
    QFile inputFile("ConfigTag"+this->Name+".txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if(!line.isEmpty()){
            AddWay(line, false);
          }
       }
       inputFile.close();
    }
}

Tag::~Tag()
{
}
