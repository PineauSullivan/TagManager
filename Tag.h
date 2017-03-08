#ifndef TAG
#define TAG
#include <string>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>

class Tag
{
private :
    QList<QString> ListWays;
    QString Name;

public :
    Tag(QString);
    QList<QString> getListWays();
    QString getName();
    void AddWay(QString way, bool write);
    bool is(QString name);
    void initialiserTagFiles();
    ~Tag();
};

#endif // TAG

