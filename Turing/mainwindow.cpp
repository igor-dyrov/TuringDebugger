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
//    QLabel *newlbl = new QLabel;
//    newlbl->setText("Asdfvsd");
//    ui->horizontalLayout_3->insertWidget(0, newlbl);
//    QLayoutItem* item = ui->horizontalLayout_3->itemAt(1);
//    QWidget* wd = item->widget();
//    QLabel* tmp = dynamic_cast<QLabel*>(wd);
//    tmp->setText("Aloha");
}

void MainWindow::on_LoadCmdBtn_clicked()
{
    Turing::Handler& Debugger = Turing::Handler::instance();
    belt_type b = {{0,"1"}};//, {1, "1"}, {2, "1"}, {3, "1"}, {4, "1"}};
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
    QLayoutItem *item;
    while((item = ui->horizontalLayout_3->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }
    delete ui->horizontalLayout_3;
    delete ui;
}

void MainWindow::on_btnOneStep_clicked()
{
    ui->btnStepBefore->setEnabled(true);
    Turing::Handler& Debugger = Turing::Handler::instance();
    Debugger.OneStep();
//    QMessageBox msgBox;
//    QString temp = QString::fromStdString(Debugger.GetBeltValues());
//    msgBox.setText(temp);
//    msgBox.exec();
//    ui->horizontalLayout_3->removeWidget(ui->horizontalLayout_3->itemAt(0)->widget());
//    ui->horizontalLayout_3->removeItem(ui->horizontalLayout_3->itemAt(0));
    belt_type map = Debugger.getBelt().getBelt();
    int min_index = get_min_key(map);
    int cur = Debugger.get_temp_index()-min_index;

    for (const auto& obj: map)
    {
        int index = obj.first - min_index;
        int size = ui->horizontalLayout_3->count();
        if (index < size){
            QLabel* lbl = dynamic_cast<QLabel*>(ui->horizontalLayout_3->itemAt(index)->widget());
            lbl->setText(QString::fromStdString(obj.second));
            if (index == cur)
                lbl->setStyleSheet("QLabel { background-color : red; color : blue; }");
            else
                lbl->setStyleSheet("QLabel { background-color : white; color : blue; }");
        }
        else {
            QWidget *parent = dynamic_cast<QLabel*>(ui->horizontalLayout_3);
            QLabel *newlbl = new QLabel(parent);
            newlbl->setText( QString::fromStdString(obj.second) );
            newlbl->setFixedSize(50,50);
            newlbl->setFrameShape(QFrame::Panel);
            newlbl->setFrameShadow(QFrame::Raised);
            newlbl->setStyleSheet("QLabel { background-color : white; color : blue; }");
            newlbl->setAlignment(Qt::AlignCenter);
            ui->horizontalLayout_3->insertWidget(index, newlbl);

            if (index == cur)
                newlbl->setStyleSheet("QLabel { background-color : red; color : blue; }");
            else
                newlbl->setStyleSheet("QLabel { background-color : white; color : blue; }");
        }
    }
}

void MainWindow::on_btnStepBefore_clicked()
{

    Turing::Handler& Debugger = Turing::Handler::instance();

    Debugger.StepBefore();
    if ( Debugger.isFirst() )
        ui->btnStepBefore->setEnabled(false);
//    QMessageBox msgBox;
//    QString temp = QString::fromStdString(Debugger.GetBeltValues());
//    msgBox.setText(temp);
//    msgBox.exec();
    belt_type map = Debugger.getBelt().getBelt();
    int min_index = get_min_key(map);
    int cur = Debugger.get_temp_index()-min_index;

    for (const auto& obj: map)
    {
        int index = obj.first - min_index;
        int size = ui->horizontalLayout_3->count();
        if (index < size){
            QLabel* lbl = dynamic_cast<QLabel*>(ui->horizontalLayout_3->itemAt(index)->widget());
            lbl->setText(QString::fromStdString(obj.second));
            if (index == cur)
                lbl->setStyleSheet("QLabel { background-color : red; color : blue; }");
            else
                lbl->setStyleSheet("QLabel { background-color : white; color : blue; }");
        }
        else {
            QWidget *parent = dynamic_cast<QLabel*>(ui->horizontalLayout_3);
            QLabel *newlbl = new QLabel(parent);
            newlbl->setText( QString::fromStdString(obj.second) );
            newlbl->setFixedSize(50,50);
            newlbl->setFrameShape(QFrame::Panel);
            newlbl->setFrameShadow(QFrame::Raised);
            newlbl->setStyleSheet("QLabel { background-color : white; color : blue; }");
            newlbl->setAlignment(Qt::AlignCenter);
            ui->horizontalLayout_3->insertWidget(index, newlbl);
            if (index == cur)
                newlbl->setStyleSheet("QLabel { background-color : red; color : blue; }");
            else
                newlbl->setStyleSheet("QLabel { background-color : white; color : blue; }");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    Turing::Handler& Debugger = Turing::Handler::instance();

    const belt_type map = Debugger.getBelt().getBelt();
    for (auto const& obj : map)
    {
        QWidget *parent = dynamic_cast<QLabel*>(ui->horizontalLayout_3);
        QLabel *newlbl = new QLabel(parent);
        newlbl->setText( QString::fromStdString(obj.second) );
        newlbl->setFixedSize(50,50);
        newlbl->setFrameShape(QFrame::Panel);
        newlbl->setFrameShadow(QFrame::Raised);
        newlbl->setStyleSheet("QLabel { background-color : white; color : blue; }");
        newlbl->setAlignment(Qt::AlignCenter);
        ui->horizontalLayout_3->insertWidget(obj.first, newlbl);
    }
    dynamic_cast<QLabel*>(ui->horizontalLayout_3->itemAt(0)->widget())->setStyleSheet("QLabel { background-color : red; color : blue; }");
}
