#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(Ui::MainWindow::LoadCmdBtn, SIGNAL (released()), this, SLOT (on_LoadCmdBtn_clicked()));
}

void MainWindow::on_LoadCmdBtn_clicked()
{
    belt_type b = {{0,"1"}, {1, "1"}, {2, "1"}, {3, "1"}, {4, "1"}};
    Turing::Belt belt(b);
    Turing::Handler hn(transitions_set(), belt, "", {});
    TuringInterpreter* intr = new TuringInterpreter;
    auto commands = ui->CommandsEdit->toPlainText();
    auto cmd = intr->Interpret(commands.toStdString());
    hn.SetCommands(cmd);
    Turing::ResultCode code = Turing::NormalWork;
    while (code == Turing::NormalWork) {
        code = hn.OneStep();
    }
    QMessageBox msgBox;
    QString temp = QString::fromStdString(hn.GetBeltValues());
    msgBox.setText(temp);
    msgBox.exec();
    delete intr;
}

MainWindow::~MainWindow()
{
    delete ui;
}
