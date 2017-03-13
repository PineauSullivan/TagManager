#ifndef TABRECHERCHE_H
#define TABRECHERCHE_H
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <Tags.h>
#include <QWidgetO.h>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLabel>
#include <QStandardItemModel>
#include <QPushButtonPlus.h>
#include <QMenuBar>
#include <Style.h>
#include <MyView.h>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QCheckBox>
#include <QToolBar>

class TabRecherche : public QWidgetO
{
    Q_OBJECT

private :
    Tags* tags;
    QList<QPushButton*> buttonsList;
    QList<Tag*> tagsSelected;
    Tag* tagEnSuppression;
    MyView* view;
    QStandardItemModel* model;
    QMenu* menuTag;
    QMenu* menuWay;

public :
    TabRecherche(Tags *tags, QWidget* parent = 0);
    void initialisationButtons();
    void sup(QString name);
    ~TabRecherche();

private slots:
    void tagClicked();
    void aucunTag();
    void recherche();
    void menuTagClicked();
    void menuWayClicked();
    void lancer();
    void supTag();
    void supWay();

};
#endif // TABRECHERCHE_H
