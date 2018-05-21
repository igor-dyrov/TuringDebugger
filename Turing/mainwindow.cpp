#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TM.hpp"

//static Turing::Handler& Debugger = Turing::Handler::instance();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_state = Turing::NormalWork;
    ui->setupUi(this);
    ui->btnStepBefore->setEnabled(false);
    QPixmap img(":/img/Mashina_Tjuringa-2.jpg");
    ui->label->setPixmap(img);
    this->setStyleSheet("background-color: white;");
    //ui->btnOneStep->setStyleSheet("background-color: blue;");
//    for (int i = 0; i < 15; ++i){
//        QLabel *newlbl = new QLabel;
//        newlbl->setText( QString::fromStdString("λ") );
//        newlbl->setFixedSize(50,50);
//        newlbl->setFrameShape(QFrame::Panel);
//        newlbl->setFrameShadow(QFrame::Raised);
//        newlbl->setStyleSheet("QLabel { background-color : white; color : black; }");
//        newlbl->setAlignment(Qt::AlignCenter);
//        ui->horizontalLayout_3->insertWidget(i, newlbl);
//    }
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
    Debugger.setFields(transitions_set(), Turing::Belt(), "", {});
//    Turing::Handler hn(transitions_set(), belt, "", {});
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

Turing::ResultCode MainWindow::on_btnOneStep_clicked()
{
    ui->btnStepBefore->setEnabled(true);
    Turing::Handler& Debugger = Turing::Handler::instance();
    Turing::ResultCode code = Debugger.OneStep();
    belt_type map = Debugger.getBelt().getBelt();
    int min_index = get_min_key(map);
    int cur = Debugger.get_temp_index()-min_index;

    for (const auto& obj: map)
    {
        int index = obj.first - min_index;
        int size = ui->horizontalLayout_3->count();
        if (index < size-1){
            QLabel* lbl = dynamic_cast<QLabel*>(ui->horizontalLayout_3->itemAt(index)->widget());
            lbl->setText(QString::fromStdString(obj.second));
            if (index == cur)
                lbl->setStyleSheet("QLabel { background-color : blue; color : white; }");
            else
                lbl->setStyleSheet("QLabel { background-color : white; color : black; }");
        }
        else {
            QLabel *newlbl = new QLabel;
            newlbl->setText( QString::fromStdString(obj.second) );
            newlbl->setFixedSize(50,50);
            newlbl->setFrameShape(QFrame::Panel);
            newlbl->setFrameShadow(QFrame::Raised);
            newlbl->setStyleSheet("QLabel { background-color : white; color : black; }");
            newlbl->setAlignment(Qt::AlignCenter);
            ui->horizontalLayout_3->insertWidget(index, newlbl);
            if (index == cur)
                newlbl->setStyleSheet("QLabel { background-color : blue; color : white; }");
            else
                newlbl->setStyleSheet("QLabel { background-color : white; color : black; }");
        }
    }
    return code;
}

void MainWindow::on_btnStepBefore_clicked()
{
    m_state = Turing::EndOfProgram;
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
                lbl->setStyleSheet("QLabel { background-color : blue; color : white; }");
            else
                lbl->setStyleSheet("QLabel { background-color : white; color : black; }");
        }
        else {
            QLabel *newlbl = new QLabel;
            newlbl->setText( QString::fromStdString(obj.second) );
            newlbl->setFixedSize(50,50);
            newlbl->setFrameShape(QFrame::Panel);
            newlbl->setFrameShadow(QFrame::Raised);
            newlbl->setStyleSheet("QLabel { background-color : white; color : black; }");
            newlbl->setAlignment(Qt::AlignCenter);
            ui->horizontalLayout_3->insertWidget(index, newlbl);
            if (index == cur)
                newlbl->setStyleSheet("QLabel { background-color : blue; color : white; }");
            else
                newlbl->setStyleSheet("QLabel { background-color : white; color : black; }");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_state = Turing::EndOfProgram;
    Turing::Handler& Debugger = Turing::Handler::instance();

    TuringInterpreter* intr = new TuringInterpreter;
    auto commands = ui->lineEdit->text();
    try {
    belt_type new_belt = intr->BeltParser(commands.toStdString());
    Turing::Belt belt(new_belt);
    on_LoadCmdBtn_clicked();
    Debugger.setBelt(belt);
    }
    catch (InterpretException e){
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString( e.what() ) );
        msgBox.exec();
    }

    delete intr;

    QLayoutItem *item;
    while((item = ui->horizontalLayout_3->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }
    ui->horizontalLayout_3->addStretch();

    auto map = Debugger.getBelt();
    for (auto obj = map.begin(); obj != map.end(); ++obj)
    {
        QLabel *newlbl = new QLabel;
        newlbl->setText( QString::fromStdString(obj.second()) );
        newlbl->setFixedSize(50,50);
        newlbl->setFrameShape(QFrame::Panel);
        newlbl->setFrameShadow(QFrame::Raised);
        newlbl->setStyleSheet("QLabel { background-color : white; color : black; }");
        newlbl->setAlignment(Qt::AlignCenter);
        ui->horizontalLayout_3->insertWidget(obj.first(), newlbl);
    }
    dynamic_cast<QLabel*>(ui->horizontalLayout_3->itemAt(0)->widget())->setStyleSheet("QLabel { background-color : blue; color : white; }");
}

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_StartDebugBtn_clicked()
{
    m_state = Turing::NormalWork;
    Turing::ResultCode code = Turing::NormalWork;
    while (code == Turing::NormalWork && m_state) {
            code = on_btnOneStep_clicked();
            delay();
    }

}

void MainWindow::on_PauseDebugBtn_clicked()
{
    m_state = Turing::EndOfProgram;
}
