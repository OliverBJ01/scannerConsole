/********************************************************************************
** Form generated from reading UI file 'consoleForm.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLEFORM_H
#define UI_CONSOLEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mwarsForm
{
public:
    QWidget *centralWidget;
    QLabel *labelLaserFlt;
    QSlider *xSlider;
    QRadioButton *radioButtonVerboseOn;
    QLabel *labelScanYPwr;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *noteLabel;
    QLabel *labelScanYFlt;
    QSpinBox *xSpinBox;
    QLabel *xLabel;
    QSpinBox *ySpinBox;
    QLabel *labelScanX;
    QRadioButton *radioButtonVerboseOff;
    QLabel *labelScanXPwr;
    QLabel *labelLaserPwr;
    QLabel *yLabel;
    QLabel *labelScanXFlt;
    QPushButton *pushButtonConnect;
    QLabel *labelLaser;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *notificationLabel;
    QWidget *formLayoutWidget_6;
    QFormLayout *formLayout_6;
    QLabel *tcpStateLabel;
    QSlider *ySlider;
    QLabel *labelScanY;
    QLabel *labelHWStart;
    QLabel *labelScannerStateFault;
    QLabel *labelHWStartFault;
    QLabel *labelScannerState;
    QLCDNumber *lcdNumberX;
    QLCDNumber *lcdNumberY;
    QPushButton *pushButtonResetScanner;
    QPushButton *pushButtonTestDataToggle;
    QPushButton *pushButtonCameraDataToggle;
    QPushButton *pushButtonScannerToggle;
    QLabel *labelScanner;
    QPushButton *pushButtonLaserDisableToggle;
    QPushButton *pbLaserToggle;
    QLabel *labelLaser_2;
    QLabel *labelLaser_3;
    QLabel *labelCalX;
    QLabel *labelCalY;
    QPushButton *pbCalSetULHC;
    QPushButton *pbCalSetLRHC;
    QPushButton *pbCalibrateToggle;
    QLabel *notificationLabelCal;
    QPushButton *pbCalFullFrame;
    QPushButton *pbCalHalfFrame;
    QLabel *labelCalx;
    QLabel *labelCaly;
    QLabel *labelCalOffsetx;
    QLabel *labelCalOffsety;
    QLabel *labelCalScalex;
    QLabel *labelCalScaley;
    QPushButton *pbCamTrimOffset;
    QSpinBox *spinboxXCamTrim;
    QSpinBox *spinboxYCamTrim;
    QPushButton *pbCalLaserBsight;
    QPushButton *pbRectangle;
    QPushButton *pbStopRectangle;
    QPushButton *pbCamOffset;
    QSpinBox *sbXCamOffset;
    QSpinBox *sbYCamOffset;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mwarsForm)
    {
        if (mwarsForm->objectName().isEmpty())
            mwarsForm->setObjectName(QStringLiteral("mwarsForm"));
        mwarsForm->resize(561, 422);
        centralWidget = new QWidget(mwarsForm);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelLaserFlt = new QLabel(centralWidget);
        labelLaserFlt->setObjectName(QStringLiteral("labelLaserFlt"));
        labelLaserFlt->setGeometry(QRect(120, 79, 41, 16));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        labelLaserFlt->setFont(font);
        xSlider = new QSlider(centralWidget);
        xSlider->setObjectName(QStringLiteral("xSlider"));
        xSlider->setGeometry(QRect(270, 50, 20, 201));
        xSlider->setMaximum(65534);
        xSlider->setOrientation(Qt::Vertical);
        xSlider->setTickPosition(QSlider::NoTicks);
        radioButtonVerboseOn = new QRadioButton(centralWidget);
        radioButtonVerboseOn->setObjectName(QStringLiteral("radioButtonVerboseOn"));
        radioButtonVerboseOn->setGeometry(QRect(10, 230, 91, 19));
        radioButtonVerboseOn->setChecked(true);
        labelScanYPwr = new QLabel(centralWidget);
        labelScanYPwr->setObjectName(QStringLiteral("labelScanYPwr"));
        labelScanYPwr->setGeometry(QRect(80, 60, 31, 16));
        labelScanYPwr->setFont(font);
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 320, 82, 17));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        noteLabel = new QLabel(formLayoutWidget);
        noteLabel->setObjectName(QStringLiteral("noteLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, noteLabel);

        labelScanYFlt = new QLabel(centralWidget);
        labelScanYFlt->setObjectName(QStringLiteral("labelScanYFlt"));
        labelScanYFlt->setGeometry(QRect(120, 60, 41, 16));
        labelScanYFlt->setFont(font);
        labelScanYFlt->setFrameShape(QFrame::NoFrame);
        xSpinBox = new QSpinBox(centralWidget);
        xSpinBox->setObjectName(QStringLiteral("xSpinBox"));
        xSpinBox->setGeometry(QRect(250, 250, 61, 22));
        xSpinBox->setMaximum(65534);
        xSpinBox->setSingleStep(200);
        xSpinBox->setDisplayIntegerBase(10);
        xLabel = new QLabel(centralWidget);
        xLabel->setObjectName(QStringLiteral("xLabel"));
        xLabel->setGeometry(QRect(250, 90, 21, 16));
        QFont font1;
        font1.setFamily(QStringLiteral("Andale Mono"));
        font1.setPointSize(14);
        xLabel->setFont(font1);
        xLabel->setScaledContents(false);
        xLabel->setAlignment(Qt::AlignCenter);
        ySpinBox = new QSpinBox(centralWidget);
        ySpinBox->setObjectName(QStringLiteral("ySpinBox"));
        ySpinBox->setGeometry(QRect(320, 250, 61, 22));
        ySpinBox->setMaximum(65534);
        ySpinBox->setSingleStep(200);
        ySpinBox->setDisplayIntegerBase(10);
        labelScanX = new QLabel(centralWidget);
        labelScanX->setObjectName(QStringLiteral("labelScanX"));
        labelScanX->setGeometry(QRect(10, 40, 61, 16));
        radioButtonVerboseOff = new QRadioButton(centralWidget);
        radioButtonVerboseOff->setObjectName(QStringLiteral("radioButtonVerboseOff"));
        radioButtonVerboseOff->setGeometry(QRect(10, 250, 101, 19));
        radioButtonVerboseOff->setChecked(false);
        labelScanXPwr = new QLabel(centralWidget);
        labelScanXPwr->setObjectName(QStringLiteral("labelScanXPwr"));
        labelScanXPwr->setGeometry(QRect(80, 40, 31, 16));
        labelScanXPwr->setFont(font);
        labelLaserPwr = new QLabel(centralWidget);
        labelLaserPwr->setObjectName(QStringLiteral("labelLaserPwr"));
        labelLaserPwr->setGeometry(QRect(80, 80, 31, 16));
        labelLaserPwr->setFont(font);
        yLabel = new QLabel(centralWidget);
        yLabel->setObjectName(QStringLiteral("yLabel"));
        yLabel->setGeometry(QRect(320, 90, 21, 16));
        yLabel->setFont(font1);
        yLabel->setAlignment(Qt::AlignCenter);
        labelScanXFlt = new QLabel(centralWidget);
        labelScanXFlt->setObjectName(QStringLiteral("labelScanXFlt"));
        labelScanXFlt->setGeometry(QRect(120, 40, 41, 16));
        labelScanXFlt->setFont(font);
        pushButtonConnect = new QPushButton(centralWidget);
        pushButtonConnect->setObjectName(QStringLiteral("pushButtonConnect"));
        pushButtonConnect->setGeometry(QRect(10, 130, 91, 21));
        pushButtonConnect->setAutoDefault(false);
        labelLaser = new QLabel(centralWidget);
        labelLaser->setObjectName(QStringLiteral("labelLaser"));
        labelLaser->setGeometry(QRect(10, 80, 46, 12));
        formLayoutWidget_2 = new QWidget(centralWidget);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(80, 320, 311, 16));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        notificationLabel = new QLabel(formLayoutWidget_2);
        notificationLabel->setObjectName(QStringLiteral("notificationLabel"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, notificationLabel);

        formLayoutWidget_6 = new QWidget(centralWidget);
        formLayoutWidget_6->setObjectName(QStringLiteral("formLayoutWidget_6"));
        formLayoutWidget_6->setGeometry(QRect(110, 130, 141, 21));
        formLayout_6 = new QFormLayout(formLayoutWidget_6);
        formLayout_6->setSpacing(6);
        formLayout_6->setContentsMargins(11, 11, 11, 11);
        formLayout_6->setObjectName(QStringLiteral("formLayout_6"));
        formLayout_6->setContentsMargins(0, 0, 0, 0);
        tcpStateLabel = new QLabel(formLayoutWidget_6);
        tcpStateLabel->setObjectName(QStringLiteral("tcpStateLabel"));
        QFont font2;
        font2.setPointSize(8);
        tcpStateLabel->setFont(font2);

        formLayout_6->setWidget(0, QFormLayout::LabelRole, tcpStateLabel);

        ySlider = new QSlider(centralWidget);
        ySlider->setObjectName(QStringLiteral("ySlider"));
        ySlider->setGeometry(QRect(340, 50, 20, 201));
        ySlider->setMaximum(65534);
        ySlider->setOrientation(Qt::Vertical);
        ySlider->setTickPosition(QSlider::NoTicks);
        labelScanY = new QLabel(centralWidget);
        labelScanY->setObjectName(QStringLiteral("labelScanY"));
        labelScanY->setGeometry(QRect(10, 60, 61, 16));
        labelHWStart = new QLabel(centralWidget);
        labelHWStart->setObjectName(QStringLiteral("labelHWStart"));
        labelHWStart->setGeometry(QRect(10, 100, 71, 16));
        labelScannerStateFault = new QLabel(centralWidget);
        labelScannerStateFault->setObjectName(QStringLiteral("labelScannerStateFault"));
        labelScannerStateFault->setGeometry(QRect(110, 20, 41, 16));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        labelScannerStateFault->setFont(font3);
        labelHWStartFault = new QLabel(centralWidget);
        labelHWStartFault->setObjectName(QStringLiteral("labelHWStartFault"));
        labelHWStartFault->setGeometry(QRect(80, 100, 141, 16));
        labelHWStartFault->setFont(font3);
        labelScannerState = new QLabel(centralWidget);
        labelScannerState->setObjectName(QStringLiteral("labelScannerState"));
        labelScannerState->setGeometry(QRect(0, 20, 91, 16));
        lcdNumberX = new QLCDNumber(centralWidget);
        lcdNumberX->setObjectName(QStringLiteral("lcdNumberX"));
        lcdNumberX->setGeometry(QRect(240, 20, 64, 23));
        QFont font4;
        font4.setPointSize(10);
        lcdNumberX->setFont(font4);
        lcdNumberX->setAcceptDrops(false);
        lcdNumberX->setMode(QLCDNumber::Dec);
        lcdNumberX->setSegmentStyle(QLCDNumber::Flat);
        lcdNumberY = new QLCDNumber(centralWidget);
        lcdNumberY->setObjectName(QStringLiteral("lcdNumberY"));
        lcdNumberY->setGeometry(QRect(310, 20, 64, 23));
        lcdNumberY->setFont(font4);
        lcdNumberY->setMode(QLCDNumber::Dec);
        lcdNumberY->setSegmentStyle(QLCDNumber::Flat);
        pushButtonResetScanner = new QPushButton(centralWidget);
        pushButtonResetScanner->setObjectName(QStringLiteral("pushButtonResetScanner"));
        pushButtonResetScanner->setGeometry(QRect(10, 150, 91, 20));
        pushButtonTestDataToggle = new QPushButton(centralWidget);
        pushButtonTestDataToggle->setObjectName(QStringLiteral("pushButtonTestDataToggle"));
        pushButtonTestDataToggle->setGeometry(QRect(140, 280, 81, 31));
        pushButtonTestDataToggle->setAutoDefault(false);
        pushButtonCameraDataToggle = new QPushButton(centralWidget);
        pushButtonCameraDataToggle->setObjectName(QStringLiteral("pushButtonCameraDataToggle"));
        pushButtonCameraDataToggle->setGeometry(QRect(10, 280, 121, 31));
        pushButtonCameraDataToggle->setAutoDefault(false);
        pushButtonScannerToggle = new QPushButton(centralWidget);
        pushButtonScannerToggle->setObjectName(QStringLiteral("pushButtonScannerToggle"));
        pushButtonScannerToggle->setGeometry(QRect(10, 200, 111, 21));
        QFont font5;
        font5.setBold(false);
        font5.setWeight(50);
        pushButtonScannerToggle->setFont(font5);
        labelScanner = new QLabel(centralWidget);
        labelScanner->setObjectName(QStringLiteral("labelScanner"));
        labelScanner->setGeometry(QRect(130, 200, 31, 16));
        QFont font6;
        font6.setBold(true);
        font6.setWeight(75);
        labelScanner->setFont(font6);
        labelScanner->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonLaserDisableToggle = new QPushButton(centralWidget);
        pushButtonLaserDisableToggle->setObjectName(QStringLiteral("pushButtonLaserDisableToggle"));
        pushButtonLaserDisableToggle->setGeometry(QRect(230, 280, 111, 31));
        pushButtonLaserDisableToggle->setFont(font5);
        pbLaserToggle = new QPushButton(centralWidget);
        pbLaserToggle->setObjectName(QStringLiteral("pbLaserToggle"));
        pbLaserToggle->setGeometry(QRect(10, 180, 111, 21));
        pbLaserToggle->setFont(font5);
        labelLaser_2 = new QLabel(centralWidget);
        labelLaser_2->setObjectName(QStringLiteral("labelLaser_2"));
        labelLaser_2->setGeometry(QRect(130, 180, 31, 20));
        labelLaser_2->setFont(font6);
        labelLaser_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelLaser_3 = new QLabel(centralWidget);
        labelLaser_3->setObjectName(QStringLiteral("labelLaser_3"));
        labelLaser_3->setGeometry(QRect(350, 280, 61, 31));
        labelLaser_3->setFont(font6);
        labelLaser_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelCalX = new QLabel(centralWidget);
        labelCalX->setObjectName(QStringLiteral("labelCalX"));
        labelCalX->setGeometry(QRect(390, 140, 41, 16));
        QFont font7;
        font7.setFamily(QStringLiteral("Andale Mono"));
        font7.setPointSize(7);
        labelCalX->setFont(font7);
        labelCalX->setScaledContents(false);
        labelCalX->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelCalY = new QLabel(centralWidget);
        labelCalY->setObjectName(QStringLiteral("labelCalY"));
        labelCalY->setGeometry(QRect(390, 160, 41, 16));
        labelCalY->setFont(font7);
        labelCalY->setScaledContents(false);
        labelCalY->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pbCalSetULHC = new QPushButton(centralWidget);
        pbCalSetULHC->setObjectName(QStringLiteral("pbCalSetULHC"));
        pbCalSetULHC->setGeometry(QRect(380, 40, 61, 21));
        pbCalSetULHC->setFont(font2);
        pbCalSetULHC->setAutoDefault(false);
        pbCalSetLRHC = new QPushButton(centralWidget);
        pbCalSetLRHC->setObjectName(QStringLiteral("pbCalSetLRHC"));
        pbCalSetLRHC->setGeometry(QRect(450, 40, 61, 21));
        pbCalSetLRHC->setFont(font2);
        pbCalSetLRHC->setAutoDefault(false);
        pbCalibrateToggle = new QPushButton(centralWidget);
        pbCalibrateToggle->setObjectName(QStringLiteral("pbCalibrateToggle"));
        pbCalibrateToggle->setGeometry(QRect(380, 20, 121, 21));
        pbCalibrateToggle->setAutoDefault(false);
        notificationLabelCal = new QLabel(centralWidget);
        notificationLabelCal->setObjectName(QStringLiteral("notificationLabelCal"));
        notificationLabelCal->setGeometry(QRect(370, 110, 141, 20));
        notificationLabelCal->setAlignment(Qt::AlignCenter);
        pbCalFullFrame = new QPushButton(centralWidget);
        pbCalFullFrame->setObjectName(QStringLiteral("pbCalFullFrame"));
        pbCalFullFrame->setGeometry(QRect(400, 70, 91, 21));
        pbCalFullFrame->setFont(font2);
        pbCalFullFrame->setAutoDefault(false);
        pbCalHalfFrame = new QPushButton(centralWidget);
        pbCalHalfFrame->setObjectName(QStringLiteral("pbCalHalfFrame"));
        pbCalHalfFrame->setGeometry(QRect(400, 90, 91, 21));
        pbCalHalfFrame->setFont(font2);
        pbCalHalfFrame->setAutoDefault(false);
        labelCalx = new QLabel(centralWidget);
        labelCalx->setObjectName(QStringLiteral("labelCalx"));
        labelCalx->setGeometry(QRect(440, 130, 16, 16));
        QFont font8;
        font8.setFamily(QStringLiteral("Sans"));
        font8.setPointSize(7);
        labelCalx->setFont(font8);
        labelCalx->setScaledContents(false);
        labelCalx->setAlignment(Qt::AlignCenter);
        labelCaly = new QLabel(centralWidget);
        labelCaly->setObjectName(QStringLiteral("labelCaly"));
        labelCaly->setGeometry(QRect(480, 130, 16, 16));
        labelCaly->setFont(font8);
        labelCaly->setScaledContents(false);
        labelCaly->setAlignment(Qt::AlignCenter);
        labelCalOffsetx = new QLabel(centralWidget);
        labelCalOffsetx->setObjectName(QStringLiteral("labelCalOffsetx"));
        labelCalOffsetx->setGeometry(QRect(440, 140, 31, 16));
        QFont font9;
        font9.setPointSize(7);
        font9.setBold(false);
        font9.setWeight(50);
        labelCalOffsetx->setFont(font9);
        labelCalOffsety = new QLabel(centralWidget);
        labelCalOffsety->setObjectName(QStringLiteral("labelCalOffsety"));
        labelCalOffsety->setGeometry(QRect(480, 140, 31, 16));
        labelCalOffsety->setFont(font9);
        labelCalScalex = new QLabel(centralWidget);
        labelCalScalex->setObjectName(QStringLiteral("labelCalScalex"));
        labelCalScalex->setGeometry(QRect(440, 160, 21, 16));
        labelCalScalex->setFont(font9);
        labelCalScaley = new QLabel(centralWidget);
        labelCalScaley->setObjectName(QStringLiteral("labelCalScaley"));
        labelCalScaley->setGeometry(QRect(480, 160, 21, 16));
        labelCalScaley->setFont(font9);
        pbCamTrimOffset = new QPushButton(centralWidget);
        pbCamTrimOffset->setObjectName(QStringLiteral("pbCamTrimOffset"));
        pbCamTrimOffset->setGeometry(QRect(400, 260, 111, 20));
        pbCamTrimOffset->setFont(font2);
        pbCamTrimOffset->setAutoDefault(false);
        spinboxXCamTrim = new QSpinBox(centralWidget);
        spinboxXCamTrim->setObjectName(QStringLiteral("spinboxXCamTrim"));
        spinboxXCamTrim->setGeometry(QRect(400, 240, 51, 21));
        spinboxXCamTrim->setFont(font2);
        spinboxXCamTrim->setMinimum(-5000);
        spinboxXCamTrim->setMaximum(5000);
        spinboxXCamTrim->setSingleStep(100);
        spinboxXCamTrim->setDisplayIntegerBase(10);
        spinboxYCamTrim = new QSpinBox(centralWidget);
        spinboxYCamTrim->setObjectName(QStringLiteral("spinboxYCamTrim"));
        spinboxYCamTrim->setGeometry(QRect(460, 240, 51, 21));
        spinboxYCamTrim->setFont(font2);
        spinboxYCamTrim->setMinimum(-5000);
        spinboxYCamTrim->setMaximum(5000);
        spinboxYCamTrim->setSingleStep(100);
        spinboxYCamTrim->setDisplayIntegerBase(10);
        pbCalLaserBsight = new QPushButton(centralWidget);
        pbCalLaserBsight->setObjectName(QStringLiteral("pbCalLaserBsight"));
        pbCalLaserBsight->setGeometry(QRect(400, 350, 111, 20));
        pbCalLaserBsight->setFont(font2);
        pbCalLaserBsight->setAutoDefault(false);
        pbRectangle = new QPushButton(centralWidget);
        pbRectangle->setObjectName(QStringLiteral("pbRectangle"));
        pbRectangle->setGeometry(QRect(420, 290, 81, 21));
        pbRectangle->setAutoDefault(false);
        pbStopRectangle = new QPushButton(centralWidget);
        pbStopRectangle->setObjectName(QStringLiteral("pbStopRectangle"));
        pbStopRectangle->setGeometry(QRect(420, 310, 81, 21));
        pbStopRectangle->setAutoDefault(false);
        pbCamOffset = new QPushButton(centralWidget);
        pbCamOffset->setObjectName(QStringLiteral("pbCamOffset"));
        pbCamOffset->setGeometry(QRect(400, 210, 111, 20));
        pbCamOffset->setFont(font2);
        pbCamOffset->setAutoDefault(false);
        sbXCamOffset = new QSpinBox(centralWidget);
        sbXCamOffset->setObjectName(QStringLiteral("sbXCamOffset"));
        sbXCamOffset->setGeometry(QRect(400, 190, 51, 21));
        sbXCamOffset->setFont(font2);
        sbXCamOffset->setMinimum(-5000);
        sbXCamOffset->setMaximum(5000);
        sbXCamOffset->setSingleStep(100);
        sbXCamOffset->setDisplayIntegerBase(10);
        sbYCamOffset = new QSpinBox(centralWidget);
        sbYCamOffset->setObjectName(QStringLiteral("sbYCamOffset"));
        sbYCamOffset->setGeometry(QRect(460, 190, 51, 21));
        sbYCamOffset->setFont(font2);
        sbYCamOffset->setMinimum(-5000);
        sbYCamOffset->setMaximum(5000);
        sbYCamOffset->setSingleStep(100);
        sbYCamOffset->setDisplayIntegerBase(10);
        mwarsForm->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mwarsForm);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 561, 23));
        mwarsForm->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mwarsForm);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mwarsForm->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mwarsForm);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mwarsForm->setStatusBar(statusBar);

        retranslateUi(mwarsForm);
        QObject::connect(ySpinBox, SIGNAL(valueChanged(int)), ySlider, SLOT(setValue(int)));
        QObject::connect(xSpinBox, SIGNAL(valueChanged(int)), xSlider, SLOT(setValue(int)));
        QObject::connect(xSlider, SIGNAL(valueChanged(int)), xSpinBox, SLOT(setValue(int)));
        QObject::connect(ySlider, SIGNAL(valueChanged(int)), ySpinBox, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(mwarsForm);
    } // setupUi

    void retranslateUi(QMainWindow *mwarsForm)
    {
        mwarsForm->setWindowTitle(QApplication::translate("mwarsForm", "myfred", 0));
        labelLaserFlt->setText(QApplication::translate("mwarsForm", "zz", 0));
        radioButtonVerboseOn->setText(QApplication::translate("mwarsForm", "Verbose On", 0));
        labelScanYPwr->setText(QApplication::translate("mwarsForm", "OFF", 0));
        noteLabel->setText(QApplication::translate("mwarsForm", "Notifications:", 0));
        labelScanYFlt->setText(QApplication::translate("mwarsForm", "zz", 0));
        xLabel->setText(QApplication::translate("mwarsForm", "X", 0));
        labelScanX->setText(QApplication::translate("mwarsForm", "Scanner X", 0));
        radioButtonVerboseOff->setText(QApplication::translate("mwarsForm", "Verbose Off", 0));
        labelScanXPwr->setText(QApplication::translate("mwarsForm", "OFF", 0));
        labelLaserPwr->setText(QApplication::translate("mwarsForm", "OFF", 0));
        yLabel->setText(QApplication::translate("mwarsForm", "Y", 0));
        labelScanXFlt->setText(QApplication::translate("mwarsForm", "zz", 0));
        pushButtonConnect->setText(QApplication::translate("mwarsForm", "Connect Server", 0));
        labelLaser->setText(QApplication::translate("mwarsForm", "Laser", 0));
        notificationLabel->setText(QString());
        tcpStateLabel->setText(QString());
        labelScanY->setText(QApplication::translate("mwarsForm", "Scanner Y", 0));
        labelHWStart->setText(QApplication::translate("mwarsForm", "HW Started", 0));
        labelScannerStateFault->setText(QApplication::translate("mwarsForm", "zz", 0));
        labelHWStartFault->setText(QApplication::translate("mwarsForm", "zz", 0));
        labelScannerState->setText(QApplication::translate("mwarsForm", "SCANNER STATE:", 0));
        pushButtonResetScanner->setText(QApplication::translate("mwarsForm", "Reset Server", 0));
        pushButtonTestDataToggle->setText(QApplication::translate("mwarsForm", "Test Data", 0));
        pushButtonCameraDataToggle->setText(QApplication::translate("mwarsForm", "CONNECT OpenCV", 0));
        pushButtonScannerToggle->setText(QApplication::translate("mwarsForm", "SCANNER: ON/OFF", 0));
        labelScanner->setText(QApplication::translate("mwarsForm", "OFF", 0));
        pushButtonLaserDisableToggle->setText(QApplication::translate("mwarsForm", "LASER: DISABLE", 0));
        pbLaserToggle->setText(QApplication::translate("mwarsForm", "LASER: ON/OFF", 0));
        labelLaser_2->setText(QApplication::translate("mwarsForm", "OFF", 0));
        labelLaser_3->setText(QApplication::translate("mwarsForm", "ENABLED", 0));
        labelCalX->setText(QApplication::translate("mwarsForm", "offset", 0));
        labelCalY->setText(QApplication::translate("mwarsForm", "scale", 0));
        pbCalSetULHC->setText(QApplication::translate("mwarsForm", "Set ULHC", 0));
        pbCalSetLRHC->setText(QApplication::translate("mwarsForm", "Set LRHC", 0));
        pbCalibrateToggle->setText(QApplication::translate("mwarsForm", "CALIBRATE ON/OFF", 0));
        notificationLabelCal->setText(QApplication::translate("mwarsForm", "FF", 0));
        pbCalFullFrame->setText(QApplication::translate("mwarsForm", "Full Frame Cal", 0));
        pbCalHalfFrame->setText(QApplication::translate("mwarsForm", "Half Frame Cal", 0));
        labelCalx->setText(QApplication::translate("mwarsForm", "X", 0));
        labelCaly->setText(QApplication::translate("mwarsForm", "Y", 0));
        labelCalOffsetx->setText(QApplication::translate("mwarsForm", "zz", 0));
        labelCalOffsety->setText(QApplication::translate("mwarsForm", "zz", 0));
        labelCalScalex->setText(QApplication::translate("mwarsForm", "zz", 0));
        labelCalScaley->setText(QApplication::translate("mwarsForm", "zz", 0));
        pbCamTrimOffset->setText(QApplication::translate("mwarsForm", "Set Trim Offset", 0));
        pbCalLaserBsight->setText(QApplication::translate("mwarsForm", "Laser ON Boresight", 0));
        pbRectangle->setText(QApplication::translate("mwarsForm", "Rectangle", 0));
        pbStopRectangle->setText(QApplication::translate("mwarsForm", "Stop", 0));
        pbCamOffset->setText(QApplication::translate("mwarsForm", "Set Cam/Scan Offset", 0));
    } // retranslateUi

};

namespace Ui {
    class mwarsForm: public Ui_mwarsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLEFORM_H
