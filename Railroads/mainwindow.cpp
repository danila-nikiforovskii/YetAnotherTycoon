#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainScreen = new DMainScreen(this);
    MainScreen->setGeometry(this->geometry());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if (MainScreen)
    {
        MainScreen->setGeometry(QRect(0,0,this->geometry().width(),this->geometry().height()));
        MainScreen->updateGL();
    }
}
