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
#include <Headers/Tags.h>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QListView>
#include <QHeaderView>
#include <QList>
#include <Headers/Tag.h>
#include <QLabel>
#include <Headers/QWidgetO.h>
#include <Headers/Style.h>
#include <Headers/QPushButtonPlus.h>
#include <QMenuBar>
#include <QDirModel>
#include <QMouseEvent>

class TabEdition : public QWidgetO
{
    Q_OBJECT

private :
        Tags* tags;
        QPushButton* creerTag;
        QPushButton* associerTag;
        QList<QPushButtonPlus*> buttonsList;
        QTreeView* view;
        QDirModel* model;
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
        void selectedAuto();

public slots:
        void messageAide();

};
#endif // TABEDITION_H
