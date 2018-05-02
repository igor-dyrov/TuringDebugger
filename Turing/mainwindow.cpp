#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TM.hpp"

//static Turing::Handler& Debugger = Turing::Handler::instance();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->btnStepBefore->setEnabled(false);
    //connect(Ui::MainWindow::LoadCmdBtn, SIGNAL (released()), this, SLOT (on_LoadCmdBtn_clicked()));
}

void MainWindow::on_LoadCmdBtn_clicked()
{
    Turing::Handler& Debugger = Turing::Handler::instance();
    belt_type b = {{0,"1"}, {1, "1"}, {2, "1"}, {3, "1"}, {4, "1"}};
    Turing::Belt belt(b);
//    Turing::Handler hn(transitions_set(), belt, "", {});
    Debugger.setFields(transitions_set(), belt, "", {});
    TuringInterpreter* intr = new TuringInterpreter;
    auto commands = ui->CommandsEdit->toPlainText();
    try {
    auto cmd = intr->Interpret(commands.toStdString());
    Debugger.SetCommands(cmd);
//    Turing::ResultCode code = Turing::NormalWork;
//    while (code == Turing::NormalWork) {
//        code = Debugger.OneStep();
//    }
//    QMessageBox msgBox;
//    QString temp = QString::fromStdString(Debugger.GetBeltValues());
//    msgBox.setText(temp);
//    msgBox.exec();
    }
    catch (InterpretException e){
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString( e.what() ) );
        msgBox.exec();
    }

    delete intr;
}

void MainWindow::on_actionSave_triggered()
{
    QMessageBox msgBox;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save file",
                                                    "./");
    QFile file(fileName);
    if (!(file.open(QIODevice::WriteOnly)))
    {
        msgBox.setText("Permission denied");
        msgBox.exec();
        return;
    }

    QString text = ui->CommandsEdit->toPlainText();
    file.write(text.toUtf8());
    file.close();
}

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox msgBox;
    QString fileName = QFileDialog::getOpenFileName(this, "Open","./");
    ui->CommandsEdit->setText("Hello");
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
           msgBox.setText("Can't open file");
           msgBox.exec();
           return;
    }

    QString text = file.readAll();
    file.close();
    ui->CommandsEdit->setText(text);
}

void MainWindow::on_actionNew_triggered()
{
    //QString fileName = QFileDialog::getSaveFileName(this,
    // Complete later                                                "Create",                                                     "./");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOneStep_clicked()
{
    ui->btnStepBefore->setEnabled(true);
    Turing::Handler& Debugger = Turing::Handler::instance();
    Debugger.OneStep();
    QMessageBox msgBox;
    QString temp = QString::fromStdString(Debugger.GetBeltValues());
    msgBox.setText(temp);
    msgBox.exec();

}

void MainWindow::on_btnStepBefore_clicked()
{

    Turing::Handler& Debugger = Turing::Handler::instance();

    Debugger.StepBefore();
    if ( Debugger.isFirst() )
        ui->btnStepBefore->setEnabled(false);
    QMessageBox msgBox;
    QString temp = QString::fromStdString(Debugger.GetBeltValues());
    msgBox.setText(temp);
    msgBox.exec();
}
