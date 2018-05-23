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
#include <QTimer>
#include <QTime>
#include <QLabel>
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

    Turing::ResultCode on_btnOneStep_clicked();

    void on_btnStepBefore_clicked();

    void on_pushButton_clicked();

    void on_StartDebugBtn_clicked();

    void on_PauseDebugBtn_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Turing::ResultCode m_state = Turing::EndOfProgram;
};

#endif // MAINWINDOW_H
