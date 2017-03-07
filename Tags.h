#ifndef TAGS
#define TAGS
#include <string>
#include <QString>

class Tags
{
private :
    QHash<int, QString> ListTags;
public :
    Tags();
    ~Tags();
    QHash<int, QString> getListTags();
    void add_tag(QString name);
};
#endif // TAGS

