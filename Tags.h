#ifndef TAGS
#define TAGS
#include <string>
#include <QString>
#include <Tag.h>
#include <QWidgetO.h>
#include <QFile>
#include <QTextStream>

class Tags
{
private :
    QList<Tag*> ListTags;
    QWidgetO* TabRecherche;
    QWidgetO* TabEdition;
//    QHash<QString, QString> HashTags;
public :
    Tags();
    void setQWidgetRecherche(QWidgetO* TabRecherche);
    void setQWidgetEdition(QWidgetO* TabEdition);
    QWidgetO* getTabRecherche();
    QWidgetO* getTabEdition();
    QList<Tag*> getListTags();
    Tag* getTag(QString tag);
    void initialiserTagsFiles();
    ~Tags();

//    QHash<QString, QString> getHashTags();
    void add_tag(QString name);
};
#endif // TAGS

