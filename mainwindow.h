#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QTableView>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>
#include <QJsonObject>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
//#include <SACsvStream>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString fileName,filePath;
    QPushButton *open,*save;
    QGridLayout *mainLayout;
    QTableView *CMtableView;
    QWidget *mainWidget;
    QStandardItemModel *ctlModel;
public slots:
    void setUpModel();
    void openFile();
    void savFlie();
};

#endif // MAINWINDOW_H
