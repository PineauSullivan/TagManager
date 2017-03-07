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

class TabEdition : public QWidgetO
{
    Q_OBJECT

private :
        Tags* tags;
        QPushButton* creerTag;
        QPushButton* associerTag;
        QList<QPushButton*> buttonsList;
        QTreeView* view;
        QFileSystemModel* model;
        QList<Tag*> tagsSelected;
        QList<QString> waysSelected;
        QLabel* resultLabelTag;
        QLabel* resultLabelWay;

public :
        TabEdition(Tags *tags ,QWidget* parent = 0);
        void initialisationButtons();
        void clearSelected();
        ~TabEdition();

private slots:
        void creationTag();
        void tagClicked();
        void association();
        void selected();
        QString toStringTag();
        QString toStringWay();
        void setLabels();
};
#endif // TABEDITION_H
