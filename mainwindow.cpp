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

    connect(ui->graphicsView, &ZoomPanGraphicsView::addCircle, engine_, &Engine::onAddCircle);
    connect(ui->graphicsView, &ZoomPanGraphicsView::removeCircle, engine_, &Engine::onRemoveCircle);

    connect(ui->graphicsView, &ZoomPanGraphicsView::loadFileRequest, this, &MainWindow::onLoadFileRequest);

    connect(engine_, &Engine::fileLoaded, this, &MainWindow::onFileLoaded);
    connect(engine_, &Engine::areaCalculated, this, &MainWindow::onAreaChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoadFileRequest(QString filename)
{
    engine_->loadFile(filename, getMaskName(filename));
}

void MainWindow::onFileLoaded(QString filename)
{
    currentFile_ = filename;
    ui->graphicsView->fitInView(
        ui->graphicsView->scene()->itemsBoundingRect(),
        Qt::KeepAspectRatio);
    ui->graphicsView->setFocus();
}

void MainWindow::onAreaChanged(qreal area)
{
    QString string = QString("%1px²").arg(area);
    ui->labelArea->setText(string);
}

void MainWindow::on_saveButton_clicked()
{
    if( !currentFile_.isEmpty() ) {
        engine_->saveMask(getMaskName(currentFile_));
        ui->graphicsView->setFocus();
    }
}

QString MainWindow::getMaskName(QString filename)
{
    return filename + "_mask.png";
}

void MainWindow::on_calculateAreaButton_clicked()
{
    engine_->calculateArea();
    ui->graphicsView->setFocus();
}
