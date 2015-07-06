/********************************************************************************
** Form generated from reading UI file 'msimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSIMULATOR_H
#define UI_MSIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MSimulator
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *ly_output;
    QLineEdit *mat12;
    QLineEdit *mat23;
    QLineEdit *mat24;
    QLineEdit *mat21;
    QLineEdit *mat32;
    QLineEdit *mat11;
    QLineEdit *mat33;
    QLineEdit *mat13;
    QLineEdit *mat14;
    QLineEdit *mat31;
    QLineEdit *mat34;
    QLineEdit *mat22;
    QLineEdit *mat41;
    QLineEdit *mat42;
    QLineEdit *mat43;
    QLineEdit *mat44;
    QWidget *widget;
    QVBoxLayout *ly_input;
    QHBoxLayout *ly_Server;
    QRadioButton *btnServer;
    QRadioButton *btnClient;
    QFormLayout *ly_3parameters;
    QLabel *lbHostname;
    QLineEdit *leHostname;
    QLabel *lbPort;
    QLineEdit *lePort;
    QLabel *lbX;
    QLineEdit *leX;
    QHBoxLayout *ly_Submit;
    QPushButton *btnSubmit;
    QPushButton *btnClear;
    QPushButton *btnExit;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MSimulator)
    {
        if (MSimulator->objectName().isEmpty())
            MSimulator->setObjectName(QStringLiteral("MSimulator"));
        MSimulator->resize(571, 233);
        centralWidget = new QWidget(MSimulator);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(300, 30, 256, 128));
        ly_output = new QGridLayout(gridLayoutWidget);
        ly_output->setSpacing(6);
        ly_output->setContentsMargins(11, 11, 11, 11);
        ly_output->setObjectName(QStringLiteral("ly_output"));
        ly_output->setContentsMargins(0, 0, 0, 0);
        mat12 = new QLineEdit(gridLayoutWidget);
        mat12->setObjectName(QStringLiteral("mat12"));

        ly_output->addWidget(mat12, 0, 1, 1, 1);

        mat23 = new QLineEdit(gridLayoutWidget);
        mat23->setObjectName(QStringLiteral("mat23"));

        ly_output->addWidget(mat23, 1, 2, 1, 1);

        mat24 = new QLineEdit(gridLayoutWidget);
        mat24->setObjectName(QStringLiteral("mat24"));

        ly_output->addWidget(mat24, 1, 3, 1, 1);

        mat21 = new QLineEdit(gridLayoutWidget);
        mat21->setObjectName(QStringLiteral("mat21"));

        ly_output->addWidget(mat21, 1, 0, 1, 1);

        mat32 = new QLineEdit(gridLayoutWidget);
        mat32->setObjectName(QStringLiteral("mat32"));

        ly_output->addWidget(mat32, 2, 1, 1, 1);

        mat11 = new QLineEdit(gridLayoutWidget);
        mat11->setObjectName(QStringLiteral("mat11"));
        mat11->setEnabled(true);

        ly_output->addWidget(mat11, 0, 0, 1, 1);

        mat33 = new QLineEdit(gridLayoutWidget);
        mat33->setObjectName(QStringLiteral("mat33"));

        ly_output->addWidget(mat33, 2, 2, 1, 1);

        mat13 = new QLineEdit(gridLayoutWidget);
        mat13->setObjectName(QStringLiteral("mat13"));

        ly_output->addWidget(mat13, 0, 2, 1, 1);

        mat14 = new QLineEdit(gridLayoutWidget);
        mat14->setObjectName(QStringLiteral("mat14"));

        ly_output->addWidget(mat14, 0, 3, 1, 1);

        mat31 = new QLineEdit(gridLayoutWidget);
        mat31->setObjectName(QStringLiteral("mat31"));

        ly_output->addWidget(mat31, 2, 0, 1, 1);

        mat34 = new QLineEdit(gridLayoutWidget);
        mat34->setObjectName(QStringLiteral("mat34"));

        ly_output->addWidget(mat34, 2, 3, 1, 1);

        mat22 = new QLineEdit(gridLayoutWidget);
        mat22->setObjectName(QStringLiteral("mat22"));

        ly_output->addWidget(mat22, 1, 1, 1, 1);

        mat41 = new QLineEdit(gridLayoutWidget);
        mat41->setObjectName(QStringLiteral("mat41"));

        ly_output->addWidget(mat41, 3, 0, 1, 1);

        mat42 = new QLineEdit(gridLayoutWidget);
        mat42->setObjectName(QStringLiteral("mat42"));

        ly_output->addWidget(mat42, 3, 1, 1, 1);

        mat43 = new QLineEdit(gridLayoutWidget);
        mat43->setObjectName(QStringLiteral("mat43"));

        ly_output->addWidget(mat43, 3, 2, 1, 1);

        mat44 = new QLineEdit(gridLayoutWidget);
        mat44->setObjectName(QStringLiteral("mat44"));

        ly_output->addWidget(mat44, 3, 3, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 241, 162));
        ly_input = new QVBoxLayout(widget);
        ly_input->setSpacing(6);
        ly_input->setContentsMargins(11, 11, 11, 11);
        ly_input->setObjectName(QStringLiteral("ly_input"));
        ly_input->setContentsMargins(0, 0, 0, 0);
        ly_Server = new QHBoxLayout();
        ly_Server->setSpacing(6);
        ly_Server->setObjectName(QStringLiteral("ly_Server"));
        btnServer = new QRadioButton(widget);
        btnServer->setObjectName(QStringLiteral("btnServer"));

        ly_Server->addWidget(btnServer);

        btnClient = new QRadioButton(widget);
        btnClient->setObjectName(QStringLiteral("btnClient"));

        ly_Server->addWidget(btnClient);


        ly_input->addLayout(ly_Server);

        ly_3parameters = new QFormLayout();
        ly_3parameters->setSpacing(6);
        ly_3parameters->setObjectName(QStringLiteral("ly_3parameters"));
        ly_3parameters->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        ly_3parameters->setContentsMargins(0, -1, -1, -1);
        lbHostname = new QLabel(widget);
        lbHostname->setObjectName(QStringLiteral("lbHostname"));

        ly_3parameters->setWidget(0, QFormLayout::LabelRole, lbHostname);

        leHostname = new QLineEdit(widget);
        leHostname->setObjectName(QStringLiteral("leHostname"));

        ly_3parameters->setWidget(0, QFormLayout::FieldRole, leHostname);

        lbPort = new QLabel(widget);
        lbPort->setObjectName(QStringLiteral("lbPort"));

        ly_3parameters->setWidget(1, QFormLayout::LabelRole, lbPort);

        lePort = new QLineEdit(widget);
        lePort->setObjectName(QStringLiteral("lePort"));

        ly_3parameters->setWidget(1, QFormLayout::FieldRole, lePort);

        lbX = new QLabel(widget);
        lbX->setObjectName(QStringLiteral("lbX"));

        ly_3parameters->setWidget(2, QFormLayout::LabelRole, lbX);

        leX = new QLineEdit(widget);
        leX->setObjectName(QStringLiteral("leX"));

        ly_3parameters->setWidget(2, QFormLayout::FieldRole, leX);


        ly_input->addLayout(ly_3parameters);

        ly_Submit = new QHBoxLayout();
        ly_Submit->setSpacing(6);
        ly_Submit->setObjectName(QStringLiteral("ly_Submit"));
        btnSubmit = new QPushButton(widget);
        btnSubmit->setObjectName(QStringLiteral("btnSubmit"));

        ly_Submit->addWidget(btnSubmit);

        btnClear = new QPushButton(widget);
        btnClear->setObjectName(QStringLiteral("btnClear"));

        ly_Submit->addWidget(btnClear);

        btnExit = new QPushButton(widget);
        btnExit->setObjectName(QStringLiteral("btnExit"));

        ly_Submit->addWidget(btnExit);


        ly_input->addLayout(ly_Submit);

        MSimulator->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MSimulator);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 571, 25));
        MSimulator->setMenuBar(menuBar);

        retranslateUi(MSimulator);

        QMetaObject::connectSlotsByName(MSimulator);
    } // setupUi

    void retranslateUi(QMainWindow *MSimulator)
    {
        MSimulator->setWindowTitle(QApplication::translate("MSimulator", "MSimulator", 0));
        btnServer->setText(QApplication::translate("MSimulator", "Server", 0));
        btnClient->setText(QApplication::translate("MSimulator", "Client", 0));
        lbHostname->setText(QApplication::translate("MSimulator", "Hostname :", 0));
        leHostname->setPlaceholderText(QApplication::translate("MSimulator", "localhost", 0));
        lbPort->setText(QApplication::translate("MSimulator", "Port :", 0));
        lePort->setPlaceholderText(QApplication::translate("MSimulator", "18944", 0));
        lbX->setText(QApplication::translate("MSimulator", "X :", 0));
        btnSubmit->setText(QApplication::translate("MSimulator", "&Submit", 0));
        btnClear->setText(QApplication::translate("MSimulator", "&Clear", 0));
        btnExit->setText(QApplication::translate("MSimulator", "&Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class MSimulator: public Ui_MSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSIMULATOR_H
