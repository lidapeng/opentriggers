/********************************************************************************
** Form generated from reading UI file 'dialogdata.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDATA_H
#define UI_DIALOGDATA_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DialogData
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_DEM;
    QLabel *label_slope;
    QLabel *label_aspect;
    QLabel *label_fuel;
    QLabel *label_wind;
    QLineEdit *lineEdit_DEM;
    QToolButton *toolBtn_DEM;
    QLineEdit *lineEdit_slope;
    QLineEdit *lineEdit_aspect;
    QLineEdit *lineEdit_fuel;
    QToolButton *toolBtn_slope;
    QToolButton *toolBtn_aspect;
    QToolButton *toolBtn_fuel;
    QLabel *label;
    QLabel *label_wind_2;
    QDoubleSpinBox *doubleSpinBox_windspeed;
    QLabel *label_2;
    QGroupBox *groupBox;
    QLabel *label_wind_3;
    QSpinBox *spinBox_1hM;
    QLabel *label_wind_4;
    QSpinBox *spinBox_10hM;
    QLabel *label_wind_5;
    QSpinBox *spinBox_100hM;
    QLabel *label_wind_6;
    QSpinBox *spinBox_herb;
    QLabel *label_wind_7;
    QSpinBox *spinBox_wood;
    QDoubleSpinBox *doubleSpinBox_windDirect;

    void setupUi(QDialog *DialogData)
    {
        if (DialogData->objectName().isEmpty())
            DialogData->setObjectName(QString::fromUtf8("DialogData"));
        DialogData->resize(464, 334);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogData->sizePolicy().hasHeightForWidth());
        DialogData->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(DialogData);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(80, 300, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_DEM = new QLabel(DialogData);
        label_DEM->setObjectName(QString::fromUtf8("label_DEM"));
        label_DEM->setGeometry(QRect(20, 30, 46, 13));
        label_slope = new QLabel(DialogData);
        label_slope->setObjectName(QString::fromUtf8("label_slope"));
        label_slope->setGeometry(QRect(20, 70, 46, 13));
        label_aspect = new QLabel(DialogData);
        label_aspect->setObjectName(QString::fromUtf8("label_aspect"));
        label_aspect->setGeometry(QRect(20, 110, 46, 13));
        label_fuel = new QLabel(DialogData);
        label_fuel->setObjectName(QString::fromUtf8("label_fuel"));
        label_fuel->setGeometry(QRect(20, 150, 46, 13));
        label_wind = new QLabel(DialogData);
        label_wind->setObjectName(QString::fromUtf8("label_wind"));
        label_wind->setGeometry(QRect(21, 191, 56, 16));
        lineEdit_DEM = new QLineEdit(DialogData);
        lineEdit_DEM->setObjectName(QString::fromUtf8("lineEdit_DEM"));
        lineEdit_DEM->setGeometry(QRect(60, 30, 271, 20));
        toolBtn_DEM = new QToolButton(DialogData);
        toolBtn_DEM->setObjectName(QString::fromUtf8("toolBtn_DEM"));
        toolBtn_DEM->setGeometry(QRect(360, 30, 25, 19));
        lineEdit_slope = new QLineEdit(DialogData);
        lineEdit_slope->setObjectName(QString::fromUtf8("lineEdit_slope"));
        lineEdit_slope->setGeometry(QRect(60, 70, 271, 20));
        lineEdit_aspect = new QLineEdit(DialogData);
        lineEdit_aspect->setObjectName(QString::fromUtf8("lineEdit_aspect"));
        lineEdit_aspect->setGeometry(QRect(60, 110, 271, 20));
        lineEdit_fuel = new QLineEdit(DialogData);
        lineEdit_fuel->setObjectName(QString::fromUtf8("lineEdit_fuel"));
        lineEdit_fuel->setGeometry(QRect(60, 150, 271, 20));
        toolBtn_slope = new QToolButton(DialogData);
        toolBtn_slope->setObjectName(QString::fromUtf8("toolBtn_slope"));
        toolBtn_slope->setGeometry(QRect(360, 70, 25, 19));
        toolBtn_aspect = new QToolButton(DialogData);
        toolBtn_aspect->setObjectName(QString::fromUtf8("toolBtn_aspect"));
        toolBtn_aspect->setGeometry(QRect(360, 110, 25, 19));
        toolBtn_fuel = new QToolButton(DialogData);
        toolBtn_fuel->setObjectName(QString::fromUtf8("toolBtn_fuel"));
        toolBtn_fuel->setGeometry(QRect(360, 150, 25, 19));
        label = new QLabel(DialogData);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 190, 20, 16));
        label_wind_2 = new QLabel(DialogData);
        label_wind_2->setObjectName(QString::fromUtf8("label_wind_2"));
        label_wind_2->setGeometry(QRect(190, 190, 68, 16));
        doubleSpinBox_windspeed = new QDoubleSpinBox(DialogData);
        doubleSpinBox_windspeed->setObjectName(QString::fromUtf8("doubleSpinBox_windspeed"));
        doubleSpinBox_windspeed->setGeometry(QRect(90, 190, 62, 22));
        doubleSpinBox_windspeed->setDecimals(1);
        doubleSpinBox_windspeed->setMaximum(40);
        label_2 = new QLabel(DialogData);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 190, 111, 16));
        groupBox = new QGroupBox(DialogData);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 220, 421, 81));
        label_wind_3 = new QLabel(groupBox);
        label_wind_3->setObjectName(QString::fromUtf8("label_wind_3"));
        label_wind_3->setGeometry(QRect(10, 20, 31, 16));
        spinBox_1hM = new QSpinBox(groupBox);
        spinBox_1hM->setObjectName(QString::fromUtf8("spinBox_1hM"));
        spinBox_1hM->setGeometry(QRect(40, 20, 42, 22));
        label_wind_4 = new QLabel(groupBox);
        label_wind_4->setObjectName(QString::fromUtf8("label_wind_4"));
        label_wind_4->setGeometry(QRect(140, 20, 31, 16));
        spinBox_10hM = new QSpinBox(groupBox);
        spinBox_10hM->setObjectName(QString::fromUtf8("spinBox_10hM"));
        spinBox_10hM->setGeometry(QRect(180, 20, 42, 22));
        label_wind_5 = new QLabel(groupBox);
        label_wind_5->setObjectName(QString::fromUtf8("label_wind_5"));
        label_wind_5->setGeometry(QRect(250, 20, 31, 16));
        spinBox_100hM = new QSpinBox(groupBox);
        spinBox_100hM->setObjectName(QString::fromUtf8("spinBox_100hM"));
        spinBox_100hM->setGeometry(QRect(310, 20, 42, 22));
        label_wind_6 = new QLabel(groupBox);
        label_wind_6->setObjectName(QString::fromUtf8("label_wind_6"));
        label_wind_6->setGeometry(QRect(10, 50, 31, 16));
        spinBox_herb = new QSpinBox(groupBox);
        spinBox_herb->setObjectName(QString::fromUtf8("spinBox_herb"));
        spinBox_herb->setGeometry(QRect(40, 50, 42, 22));
        label_wind_7 = new QLabel(groupBox);
        label_wind_7->setObjectName(QString::fromUtf8("label_wind_7"));
        label_wind_7->setGeometry(QRect(140, 50, 31, 16));
        spinBox_wood = new QSpinBox(groupBox);
        spinBox_wood->setObjectName(QString::fromUtf8("spinBox_wood"));
        spinBox_wood->setGeometry(QRect(180, 50, 42, 22));
        doubleSpinBox_windDirect = new QDoubleSpinBox(DialogData);
        doubleSpinBox_windDirect->setObjectName(QString::fromUtf8("doubleSpinBox_windDirect"));
        doubleSpinBox_windDirect->setGeometry(QRect(260, 190, 62, 22));
        doubleSpinBox_windDirect->setDecimals(1);
        doubleSpinBox_windDirect->setMaximum(360);

        retranslateUi(DialogData);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogData, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogData, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogData);
    } // setupUi

    void retranslateUi(QDialog *DialogData)
    {
        DialogData->setWindowTitle(QApplication::translate("DialogData", "Input data setup", 0));
        label_DEM->setText(QApplication::translate("DialogData", "DEM", 0));
        label_slope->setText(QApplication::translate("DialogData", "Slope", 0));
        label_aspect->setText(QApplication::translate("DialogData", "Aspect", 0));
        label_fuel->setText(QApplication::translate("DialogData", "Fuel", 0));
        label_wind->setText(QApplication::translate("DialogData", "Wind speed", 0));
        toolBtn_DEM->setText(QApplication::translate("DialogData", "...", 0));
        toolBtn_slope->setText(QApplication::translate("DialogData", "...", 0));
        toolBtn_aspect->setText(QApplication::translate("DialogData", "...", 0));
        toolBtn_fuel->setText(QApplication::translate("DialogData", "...", 0));
        label->setText(QApplication::translate("DialogData", "mph", 0));
        label_wind_2->setText(QApplication::translate("DialogData", "Wind direction", 0));
        label_2->setText(QApplication::translate("DialogData", "(degrees from north)", 0));
        groupBox->setTitle(QApplication::translate("DialogData", "Fuel moistures (percentage)", 0));
        label_wind_3->setText(QApplication::translate("DialogData", "1 h", 0));
        label_wind_4->setText(QApplication::translate("DialogData", "10 h", 0));
        label_wind_5->setText(QApplication::translate("DialogData", "100 h", 0));
        label_wind_6->setText(QApplication::translate("DialogData", "herb", 0));
        label_wind_7->setText(QApplication::translate("DialogData", "wood", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogData: public Ui_DialogData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDATA_H
