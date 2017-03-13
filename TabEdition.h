#ifndef TABEDITION_H
#define TABEDITION_H
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QTreeView>
#include <string>
#include <Tags.h>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QListView>
#include <QHeaderView>
#include <QList>
#include <Tag.h>
#include <QLabel>
#include <QWidgetO.h>
#include <Style.h>
#include <QPushButtonPlus.h>
#include <QMenuBar>

class TabEdition : public QWidgetO
{
    Q_OBJECT

private :
        Tags* tags;
        QPushButton* creerTag;
        QPushButton* associerTag;
        QList<QPushButtonPlus*> buttonsList;
        QTreeView* view;
        QFileSystemModel* model;
        QList<Tag*> tagsSelected;
        QList<QString> waysSelected;
        QLabel* resultLabelTag;
        QLabel* resultLabelWay;
        Tag* tagEnSuppression;
        QMenu* menuTag;
public :
        TabEdition(Tags *tags ,QWidget* parent = 0);
        void initialisationButtons();
        void initialisationButtonsList();
        void clearSelected();
        void sup(QString name);
        ~TabEdition();

private slots:
        void creationTag();
        void tagClicked();
        void association();
        void selected();
        QString toStringTag();
        QString toStringWay();
        void setLabels();
        void menuTagClicked();
        void supTag();

};
#endif // TABEDITION_H
