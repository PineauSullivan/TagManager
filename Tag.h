#ifndef TAG
#define TAG
#include <string>
#include <QString>
#include <QList>

class Tag
{
private :
    QList<QString> ListWays;
    QString Name;

public :
    Tag(QString);
    QList<QString> getListWays();
    QString getName();
    void AddWay(QString way);
    bool is(QString name);
    ~Tag();
};

#endif // TAG

