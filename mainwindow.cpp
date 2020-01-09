#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Kind of only for my computer. Depending if C drive is available for everyone.
    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);

    // Avoid the current directory and parent directory and return all directories only.
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);

    //Set model for tree view.
    ui->treeView->setModel(dirmodel);

    //Create a file system model for list view.
    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(sPath);

    //Set the model for list view.
    ui->listView->setModel(filemodel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    //Get the selected path from the tree model.
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();

    //Show the files for the list view.
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
}
