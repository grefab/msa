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
    void onFileLoaded();

private:
    Ui::MainWindow *ui;
    Engine* engine_;
};

#endif // MAINWINDOW_H
