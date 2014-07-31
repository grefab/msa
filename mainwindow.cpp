#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Engine* engine, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    engine_(engine)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(engine_->scene());

    connect(ui->graphicsView, &ZoomPanGraphicsView::circlePosChanged, engine_, &Engine::onCirclePosChanged);
    connect(ui->graphicsView, &ZoomPanGraphicsView::showCircle, engine_, &Engine::onShowCircle);
    connect(ui->graphicsView, &ZoomPanGraphicsView::hideCircle, engine_, &Engine::onHideCircle);

    connect(ui->graphicsView, &ZoomPanGraphicsView::enlargeCircle, engine_, &Engine::onEnlargeCircle);
    connect(ui->graphicsView, &ZoomPanGraphicsView::shrinkCircle, engine_, &Engine::onShrinkCircle);
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
