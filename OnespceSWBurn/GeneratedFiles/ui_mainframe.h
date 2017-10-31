/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_mainframeClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditBinPath;
    QPushButton *pushButtonOpenBin;
    QGroupBox *groupBoxSerialSetting;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QComboBox *comboBoxBaud;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QComboBox *comboBoxSerialPort;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_12;
    QComboBox *comboBoxStopBit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QComboBox *comboBoxDataBit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QComboBox *comboBoxCheckBit;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *plainTextEditInfo;
    QPushButton *pushButtonBurn;
    QProgressBar *progressBar;

    void setupUi(QDialog *mainframeClass)
    {
        if (mainframeClass->objectName().isEmpty())
            mainframeClass->setObjectName(QStringLiteral("mainframeClass"));
        mainframeClass->resize(619, 400);
        mainframeClass->setMinimumSize(QSize(619, 400));
        mainframeClass->setMaximumSize(QSize(619, 400));
        gridLayout = new QGridLayout(mainframeClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(mainframeClass);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditBinPath = new QLineEdit(mainframeClass);
        lineEditBinPath->setObjectName(QStringLiteral("lineEditBinPath"));
        lineEditBinPath->setMinimumSize(QSize(400, 0));
        lineEditBinPath->setMaximumSize(QSize(800, 16777215));

        horizontalLayout->addWidget(lineEditBinPath);

        pushButtonOpenBin = new QPushButton(mainframeClass);
        pushButtonOpenBin->setObjectName(QStringLiteral("pushButtonOpenBin"));

        horizontalLayout->addWidget(pushButtonOpenBin);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        groupBoxSerialSetting = new QGroupBox(mainframeClass);
        groupBoxSerialSetting->setObjectName(QStringLiteral("groupBoxSerialSetting"));
        gridLayout_2 = new QGridLayout(groupBoxSerialSetting);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_11 = new QLabel(groupBoxSerialSetting);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_10->addWidget(label_11);

        comboBoxBaud = new QComboBox(groupBoxSerialSetting);
        comboBoxBaud->setObjectName(QStringLiteral("comboBoxBaud"));

        horizontalLayout_10->addWidget(comboBoxBaud);


        gridLayout_2->addLayout(horizontalLayout_10, 1, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_10 = new QLabel(groupBoxSerialSetting);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_9->addWidget(label_10);

        comboBoxSerialPort = new QComboBox(groupBoxSerialSetting);
        comboBoxSerialPort->setObjectName(QStringLiteral("comboBoxSerialPort"));

        horizontalLayout_9->addWidget(comboBoxSerialPort);


        gridLayout_2->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_12 = new QLabel(groupBoxSerialSetting);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_11->addWidget(label_12);

        comboBoxStopBit = new QComboBox(groupBoxSerialSetting);
        comboBoxStopBit->setObjectName(QStringLiteral("comboBoxStopBit"));

        horizontalLayout_11->addWidget(comboBoxStopBit);


        gridLayout_2->addLayout(horizontalLayout_11, 4, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(groupBoxSerialSetting);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_7->addWidget(label_8);

        comboBoxDataBit = new QComboBox(groupBoxSerialSetting);
        comboBoxDataBit->setObjectName(QStringLiteral("comboBoxDataBit"));

        horizontalLayout_7->addWidget(comboBoxDataBit);


        gridLayout_2->addLayout(horizontalLayout_7, 3, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_9 = new QLabel(groupBoxSerialSetting);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_8->addWidget(label_9);

        comboBoxCheckBit = new QComboBox(groupBoxSerialSetting);
        comboBoxCheckBit->setObjectName(QStringLiteral("comboBoxCheckBit"));

        horizontalLayout_8->addWidget(comboBoxCheckBit);


        gridLayout_2->addLayout(horizontalLayout_8, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 0, 1, 1);


        gridLayout->addWidget(groupBoxSerialSetting, 1, 0, 1, 2);

        plainTextEditInfo = new QPlainTextEdit(mainframeClass);
        plainTextEditInfo->setObjectName(QStringLiteral("plainTextEditInfo"));

        gridLayout->addWidget(plainTextEditInfo, 1, 2, 1, 1);

        pushButtonBurn = new QPushButton(mainframeClass);
        pushButtonBurn->setObjectName(QStringLiteral("pushButtonBurn"));
        pushButtonBurn->setMinimumSize(QSize(80, 50));
        QIcon icon;
        icon.addFile(QStringLiteral(":/mainframe/image/start_burn.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonBurn->setIcon(icon);
        pushButtonBurn->setIconSize(QSize(40, 40));
        pushButtonBurn->setFlat(true);

        gridLayout->addWidget(pushButtonBurn, 2, 0, 1, 1);

        progressBar = new QProgressBar(mainframeClass);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMinimumSize(QSize(0, 50));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);
        progressBar->setInvertedAppearance(false);

        gridLayout->addWidget(progressBar, 2, 1, 1, 2);


        retranslateUi(mainframeClass);
        QObject::connect(pushButtonBurn, SIGNAL(clicked()), mainframeClass, SLOT(Burn()));
        QObject::connect(pushButtonOpenBin, SIGNAL(clicked()), mainframeClass, SLOT(OpenBin()));

        pushButtonOpenBin->setDefault(true);


        QMetaObject::connectSlotsByName(mainframeClass);
    } // setupUi

    void retranslateUi(QDialog *mainframeClass)
    {
        mainframeClass->setWindowTitle(QApplication::translate("mainframeClass", "Onespace Software Burn \302\251 zhaoyeni", Q_NULLPTR));
        label->setText(QApplication::translate("mainframeClass", "Bin path:", Q_NULLPTR));
        pushButtonOpenBin->setText(QApplication::translate("mainframeClass", "Open", Q_NULLPTR));
        groupBoxSerialSetting->setTitle(QApplication::translate("mainframeClass", "Serial Port Setting:", Q_NULLPTR));
        label_11->setText(QApplication::translate("mainframeClass", "Baudrate:", Q_NULLPTR));
        comboBoxBaud->clear();
        comboBoxBaud->insertItems(0, QStringList()
         << QApplication::translate("mainframeClass", "1200", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "2400", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "4800", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "9600", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "19200", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "38400", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "57600", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "115200", Q_NULLPTR)
        );
        label_10->setText(QApplication::translate("mainframeClass", "Port:", Q_NULLPTR));
        label_12->setText(QApplication::translate("mainframeClass", "Stop bit:", Q_NULLPTR));
        comboBoxStopBit->clear();
        comboBoxStopBit->insertItems(0, QStringList()
         << QApplication::translate("mainframeClass", "1", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "1.5", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "2", Q_NULLPTR)
        );
        label_8->setText(QApplication::translate("mainframeClass", "Data bit:", Q_NULLPTR));
        comboBoxDataBit->clear();
        comboBoxDataBit->insertItems(0, QStringList()
         << QApplication::translate("mainframeClass", "5", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "6", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "7", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "8", Q_NULLPTR)
        );
        label_9->setText(QApplication::translate("mainframeClass", "Check bit:", Q_NULLPTR));
        comboBoxCheckBit->clear();
        comboBoxCheckBit->insertItems(0, QStringList()
         << QApplication::translate("mainframeClass", "NONE", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "ODD", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "EVEN", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "MARK", Q_NULLPTR)
         << QApplication::translate("mainframeClass", "SPACE", Q_NULLPTR)
        );
        pushButtonBurn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mainframeClass: public Ui_mainframeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
