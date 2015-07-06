#ifndef MSIMULATOR_H
#define MSIMULATOR_H

#include <QMainWindow>
#include <QTimer>
#include <iostream>

namespace Ui {
class MSimulator;
}

class MSimulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit MSimulator(QWidget *parent = 0);
    ~MSimulator();

private:
    Ui::MSimulator *ui;

    std::string     strHostname;
    int             intPort;

    int             checkServer;

    QTimer         *timer;


private slots:
    void  on_btnSubmit_clicked();
    void on_btnExit_clicked();
    void on_btnClear_clicked();
};

#endif // MSIMULATOR_H
