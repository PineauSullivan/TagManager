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

class TabRecherche : public QWidgetO
{
    Q_OBJECT

private :
    Tags* tags;
    QList<QPushButton*> buttonsList;
    QPushButton* rechercher;
    QList<Tag*> tagsSelected;
    QTableView* view;
    QStandardItemModel* model;

public :
    TabRecherche(Tags *tags, QWidget* parent = 0);
    void initialisationButtons();
    ~TabRecherche();

private slots:
    void tagClicked();
    void aucunTag();
    void recherche();
};
#endif // TABRECHERCHE_H
