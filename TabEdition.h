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

class TabEdition : public QWidget
{
    Q_OBJECT

private :
        Tags* tags;
        QPushButton* creerTag;
        QPushButton* associerTag;
        QHash<int, QPushButton*> buttonsList;
        QTreeView* view;
        QFileSystemModel* model;
public :
        TabEdition(Tags *tags ,QWidget* parent = 0);
        void initialisationButtons();
        ~TabEdition();

private slots:
        void creationTag();
        void tagClicked();
        void association();
};
#endif // TABEDITION_H
