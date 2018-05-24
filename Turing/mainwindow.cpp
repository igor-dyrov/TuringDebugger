#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TM.hpp"

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
}

void MainWindow::on_LoadCmdBtn_clicked()
{
    Turing::Handler& Debugger = Turing::Handler::instance();
    Debugger.setFields(transitions_set(), Turing::Belt(), "", {});
    TuringInterpreter* intr = new TuringInterpreter;
    auto commands = ui->CommandsEdit->toPlainText();
    try {
    auto cmd = intr->Interpret(commands.toStdString());
    Debugger.SetCommands(cmd);
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
    QString str;
    str = QString::fromStdString(Debugger.get_temp_state());
    ui->label_state->setText(str);
    std::string step;
    Turing::Command cmd = Debugger.get_next_step();
    if (cmd.new_state == "") {
        step = "No suitable transition";
    }
    else {
        step += cmd.new_state;
        step += " ; ";
        step += cmd.new_symbol;
        if (cmd.move == Turing::Command::Right)
            step += " ; Right";
        else if (cmd.move == Turing::Command::Left)
            step += " ; Left";
        else
            step += " ; Center";
    }
    QString str2 = QString::fromStdString(step);
    ui->label_step->setText(str2);
    return code;
}

void MainWindow::on_btnStepBefore_clicked()
{
    m_state = Turing::EndOfProgram;
    Turing::Handler& Debugger = Turing::Handler::instance();

    Debugger.StepBefore();
    if ( Debugger.isFirst() )
        ui->btnStepBefore->setEnabled(false);
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
        QString str = QString::fromStdString(Debugger.get_temp_state());
        ui->label_state->setText(str);
        std::string step;
        Turing::Command cmd = Debugger.get_next_step();
        if (cmd.new_state == "") {
            step = "No suitable transition";
        }
        else {
            step += cmd.new_state;
            step += " ; ";
            step += cmd.new_symbol;
            if (cmd.move == Turing::Command::Right)
                step += " ; Right";
            else if (cmd.move == Turing::Command::Left)
                step += " ; Left";
            else
                step += " ; Center";
        }
        QString str2 = QString::fromStdString(step);
        ui->label_step->setText(str2);
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_state = Turing::EndOfProgram;
    Turing::Handler& Debugger = Turing::Handler::instance();
    ui->label_state->setText(QString());
    ui->label_step->setText(QString());
    TuringInterpreter* intr = new TuringInterpreter;
    auto commands = ui->lineEdit->text();
    try {
    belt_type new_belt = intr->BeltParser(commands.toStdString());
    Turing::Belt belt(new_belt);
    on_LoadCmdBtn_clicked();
    Debugger.setBelt(belt);
    if ( ui->lineEdit_2->text() != QString("index here") )
        Debugger.setIndex(ui->lineEdit_2->text().toInt());
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
    dynamic_cast<QLabel*>(ui->horizontalLayout_3->itemAt(Debugger.get_temp_index())->widget())->setStyleSheet("QLabel { background-color : blue; color : white; }");
    QString str = QString::fromStdString(Debugger.get_temp_state());
    ui->label_state->setText(str);
    std::string step;
    Turing::Command cmd = Debugger.get_next_step();
    if (cmd.new_state == "") {
        step = "No suitable transition";
    }
    else {
        step += cmd.new_state;
        step += " ; ";
        step += cmd.new_symbol;
        if (cmd.move == Turing::Command::Right)
            step += " ; Right";
        else if (cmd.move == Turing::Command::Left)
            step += " ; Left";
        else
            step += " ; Center";
    }
    QString str2 = QString::fromStdString(step);
    ui->label_step->setText(str2);
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
