/********************************************************************************
** Form generated from reading UI file 'form_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_SETTINGS_H
#define UI_FORM_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_form_settings
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_16;
    QLabel *label_5;
    QLabel *label_30;
    QLabel *label;
    QLabel *label_33;
    QLineEdit *lineEdit_max_vel;
    QLineEdit *lineEdit_max_acc;
    QSpinBox *spinBox_axis;
    QLabel *label_29;
    QLabel *label_32;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_13;
    QLabel *label_28;
    QLabel *label_31;
    QLineEdit *lineEdit_max_jerk;
    QToolButton *toolButton_save;
    QLineEdit *lineEdit_min_pos;
    QLineEdit *lineEdit_max_pos;
    QPlainTextEdit *plainTextEdit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *form_settings)
    {
        if (form_settings->objectName().isEmpty())
            form_settings->setObjectName(QString::fromUtf8("form_settings"));
        form_settings->resize(383, 580);
        form_settings->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 42, 42);\n"
"color: rgb(255, 255, 255);"));
        gridLayout_2 = new QGridLayout(form_settings);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame = new QFrame(form_settings);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMaximumSize(QSize(300, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 35));
        QFont font;
        font.setPointSize(12);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(label_5, 0, 0, 1, 3);

        label_30 = new QLabel(frame);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_16->addWidget(label_30, 6, 2, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_16->addWidget(label, 1, 0, 1, 1);

        label_33 = new QLabel(frame);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_16->addWidget(label_33, 4, 0, 1, 1);

        lineEdit_max_vel = new QLineEdit(frame);
        lineEdit_max_vel->setObjectName(QString::fromUtf8("lineEdit_max_vel"));
        lineEdit_max_vel->setMinimumSize(QSize(100, 0));

        gridLayout_16->addWidget(lineEdit_max_vel, 2, 1, 1, 1);

        lineEdit_max_acc = new QLineEdit(frame);
        lineEdit_max_acc->setObjectName(QString::fromUtf8("lineEdit_max_acc"));

        gridLayout_16->addWidget(lineEdit_max_acc, 3, 1, 1, 1);

        spinBox_axis = new QSpinBox(frame);
        spinBox_axis->setObjectName(QString::fromUtf8("spinBox_axis"));
        spinBox_axis->setMinimum(0);
        spinBox_axis->setMaximum(8);
        spinBox_axis->setValue(0);

        gridLayout_16->addWidget(spinBox_axis, 1, 1, 1, 1);

        label_29 = new QLabel(frame);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_16->addWidget(label_29, 6, 0, 1, 1);

        label_32 = new QLabel(frame);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_16->addWidget(label_32, 2, 0, 1, 1);

        label_26 = new QLabel(frame);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_16->addWidget(label_26, 7, 2, 1, 1);

        label_27 = new QLabel(frame);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_16->addWidget(label_27, 3, 2, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_16->addWidget(label_13, 3, 0, 1, 1);

        label_28 = new QLabel(frame);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_16->addWidget(label_28, 2, 2, 1, 1);

        label_31 = new QLabel(frame);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_16->addWidget(label_31, 7, 0, 1, 1);

        lineEdit_max_jerk = new QLineEdit(frame);
        lineEdit_max_jerk->setObjectName(QString::fromUtf8("lineEdit_max_jerk"));

        gridLayout_16->addWidget(lineEdit_max_jerk, 4, 1, 1, 1);

        toolButton_save = new QToolButton(frame);
        toolButton_save->setObjectName(QString::fromUtf8("toolButton_save"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButton_save->sizePolicy().hasHeightForWidth());
        toolButton_save->setSizePolicy(sizePolicy1);
        toolButton_save->setLayoutDirection(Qt::LeftToRight);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/btn_25_25_file_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_save->setIcon(icon);
        toolButton_save->setIconSize(QSize(35, 35));
        toolButton_save->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        gridLayout_16->addWidget(toolButton_save, 8, 2, 1, 1);

        lineEdit_min_pos = new QLineEdit(frame);
        lineEdit_min_pos->setObjectName(QString::fromUtf8("lineEdit_min_pos"));

        gridLayout_16->addWidget(lineEdit_min_pos, 7, 1, 1, 1);

        lineEdit_max_pos = new QLineEdit(frame);
        lineEdit_max_pos->setObjectName(QString::fromUtf8("lineEdit_max_pos"));

        gridLayout_16->addWidget(lineEdit_max_pos, 6, 1, 1, 1);


        gridLayout->addLayout(gridLayout_16, 0, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(frame);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(plainTextEdit, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(form_settings);

        QMetaObject::connectSlotsByName(form_settings);
    } // setupUi

    void retranslateUi(QDialog *form_settings)
    {
        form_settings->setWindowTitle(QCoreApplication::translate("form_settings", "Dialog", nullptr));
        label_5->setText(QCoreApplication::translate("form_settings", "- SETTINGS -", nullptr));
        label_30->setText(QCoreApplication::translate("form_settings", "mm", nullptr));
        label->setText(QCoreApplication::translate("form_settings", "axis", nullptr));
        label_33->setText(QCoreApplication::translate("form_settings", "max jerk", nullptr));
        lineEdit_max_vel->setText(QCoreApplication::translate("form_settings", "0", nullptr));
        lineEdit_max_acc->setText(QCoreApplication::translate("form_settings", "0", nullptr));
        label_29->setText(QCoreApplication::translate("form_settings", "max position", nullptr));
        label_32->setText(QCoreApplication::translate("form_settings", "max velocity", nullptr));
        label_26->setText(QCoreApplication::translate("form_settings", "mm", nullptr));
        label_27->setText(QCoreApplication::translate("form_settings", "mm / s^2", nullptr));
        label_13->setText(QCoreApplication::translate("form_settings", "max acceleration", nullptr));
        label_28->setText(QCoreApplication::translate("form_settings", "mm / s", nullptr));
        label_31->setText(QCoreApplication::translate("form_settings", "min position", nullptr));
        lineEdit_max_jerk->setText(QCoreApplication::translate("form_settings", "0", nullptr));
        toolButton_save->setText(QCoreApplication::translate("form_settings", " save", nullptr));
        lineEdit_min_pos->setText(QCoreApplication::translate("form_settings", "0", nullptr));
        lineEdit_max_pos->setText(QCoreApplication::translate("form_settings", "0", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("form_settings", "sample values:\n"
"\n"
"maxvel: 	125.0\n"
"maxacc: 	325.0\n"
"maxjerk: 	150.0\n"
"maxpos: 	10000\n"
"minpos: 	-10000\n"
"", nullptr));
    } // retranslateUi

};

namespace Ui {
    class form_settings: public Ui_form_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_SETTINGS_H
