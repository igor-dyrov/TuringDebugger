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
    try {
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
