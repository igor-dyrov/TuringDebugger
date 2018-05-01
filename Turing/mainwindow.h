#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include "settings.hpp"
#include "TM.hpp"
#include "Lang.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:

    void on_LoadCmdBtn_clicked();
    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
