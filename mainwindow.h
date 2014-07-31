#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "engine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Engine* engine, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onCircleChanged(QPointF);

    void onLoadFileRequest(QString filename);
    void onFileLoaded(QString filename);
    void onAreaChanged(qreal area);

    void on_saveButton_clicked();

    void on_calculateAreaButton_clicked();

private:
    QString currentFile_;
    QString getMaskName(QString filename);
    QString getCompositeName(QString filename);

private:
    Ui::MainWindow *ui;
    Engine* engine_;

};

#endif // MAINWINDOW_H
