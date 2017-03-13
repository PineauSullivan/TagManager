#ifndef TABRECHERCHE_H
#define TABRECHERCHE_H
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <Headers/Tags.h>
#include <Headers/QWidgetO.h>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLabel>
#include <QStandardItemModel>
#include <Headers/QPushButtonPlus.h>
#include <QMenuBar>
#include <Headers/Style.h>
#include <Headers/MyView.h>
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
    QCheckBox* modeRecherche;

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
    void checkboxChanged();

};
#endif // TABRECHERCHE_H
