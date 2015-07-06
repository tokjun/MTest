#include "msimulator.h"
#include "ui_msimulator.h"

MSimulator::MSimulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MSimulator)
{
    ui->setupUi(this);

    // qTimer
    timer = new QTimer(this);

    // Signal-Slot
    connect(timer,SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    connect(ui->btnSubmit,SIGNAL(clicked()), SLOT(on_btnSubmit_clicked()));
}

MSimulator::~MSimulator()
{
    delete ui;
}

void MSimulator::on_btnSubmit_clicked()
{
    checkServer = ui->btnServer->isChecked();
    strHostname = ui->leHostname->text().toStdString();
    intPort = ui->lePort->text().toInt();
}

void MSimulator::on_btnClear_clicked()
{
    ui->leHostname->clear();
    ui->lePort->clear();
}

void MSimulator::on_btnExit_clicked()
{
    qApp->quit();
}
