#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Engine* engine, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    engine_(engine)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(engine_->scene());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    engine_->loadFile("D:\\IMG_9253.JPG");
    ui->graphicsView->fitInView(
        ui->graphicsView->scene()->itemsBoundingRect(),
        Qt::KeepAspectRatio);
    ui->graphicsView->setFocus();
}
