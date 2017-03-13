#ifndef TAGS
#define TAGS
#include <string>
#include <QString>
#include <Headers/Tag.h>
#include <Headers/QWidgetO.h>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

class Tags
{
private :
    QList<Tag*> ListTags;
    QWidgetO* TabRecherche;
    QWidgetO* TabEdition;

public :
    Tags();
    void setQWidgetRecherche(QWidgetO* TabRecherche);
    void setQWidgetEdition(QWidgetO* TabEdition);
    QWidgetO* getTabRecherche();
    QWidgetO* getTabEdition();
    QList<Tag*> getListTags();
    Tag* getTag(QString tag);
    void supprimerTag(Tag* tag);
    void initialiserTagsFiles();
    void add_tag(QString name, bool write);
    ~Tags();

};
#endif // TAGS

