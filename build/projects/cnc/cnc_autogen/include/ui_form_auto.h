/********************************************************************************
** Form generated from reading UI file 'form_auto.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_AUTO_H
#define UI_FORM_AUTO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_form_auto
{
public:
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *doubleSpinBox_tooldir_fillet;
    QLabel *label_5;
    QLabel *label_4;
    QCheckBox *checkBox_tangential_override;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSlider *horizontalSlider_auto_velocity_procent;
    QLabel *label_auto_velocity_procent;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *doubleSpinBox_tool_angle_x;
    QCheckBox *checkBox_show_tooldir_blend_path;
    QDoubleSpinBox *doubleSpinBox_tool_angle_y;
    QGridLayout *gridLayout_2;
    QToolButton *toolButton_reload;
    QSpinBox *spinBox_run_from_line;
    QToolButton *toolButton_run;
    QToolButton *toolButton_pause;
    QToolButton *toolButton_open;
    QToolButton *toolButton_stop;
    QLabel *label_auto;
    QLabel *label;
    QLabel *label_6;

    void setupUi(QDialog *form_auto)
    {
        if (form_auto->objectName().isEmpty())
            form_auto->setObjectName(QString::fromUtf8("form_auto"));
        form_auto->resize(342, 632);
        form_auto->setMinimumSize(QSize(0, 0));
        form_auto->setMaximumSize(QSize(16777215, 16777215));
        form_auto->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 42, 42);\n"
"color: rgb(255, 255, 255);"));
        gridLayout_3 = new QGridLayout(form_auto);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        doubleSpinBox_tooldir_fillet = new QDoubleSpinBox(form_auto);
        doubleSpinBox_tooldir_fillet->setObjectName(QString::fromUtf8("doubleSpinBox_tooldir_fillet"));

        gridLayout_3->addWidget(doubleSpinBox_tooldir_fillet, 4, 0, 1, 1);

        label_5 = new QLabel(form_auto);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 6, 0, 1, 1);

        label_4 = new QLabel(form_auto);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 3, 0, 1, 1);

        checkBox_tangential_override = new QCheckBox(form_auto);
        checkBox_tangential_override->setObjectName(QString::fromUtf8("checkBox_tangential_override"));

        gridLayout_3->addWidget(checkBox_tangential_override, 5, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(form_auto);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        horizontalSlider_auto_velocity_procent = new QSlider(form_auto);
        horizontalSlider_auto_velocity_procent->setObjectName(QString::fromUtf8("horizontalSlider_auto_velocity_procent"));
        horizontalSlider_auto_velocity_procent->setMinimum(-100);
        horizontalSlider_auto_velocity_procent->setMaximum(100);
        horizontalSlider_auto_velocity_procent->setValue(50);
        horizontalSlider_auto_velocity_procent->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_auto_velocity_procent, 1, 0, 1, 2);

        label_auto_velocity_procent = new QLabel(form_auto);
        label_auto_velocity_procent->setObjectName(QString::fromUtf8("label_auto_velocity_procent"));
        QFont font;
        font.setPointSize(12);
        label_auto_velocity_procent->setFont(font);

        gridLayout->addWidget(label_auto_velocity_procent, 2, 0, 1, 1);

        label_2 = new QLabel(form_auto);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 187, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 10, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);

        doubleSpinBox_tool_angle_x = new QDoubleSpinBox(form_auto);
        doubleSpinBox_tool_angle_x->setObjectName(QString::fromUtf8("doubleSpinBox_tool_angle_x"));
        doubleSpinBox_tool_angle_x->setMinimum(-100.000000000000000);
        doubleSpinBox_tool_angle_x->setMaximum(100.000000000000000);
        doubleSpinBox_tool_angle_x->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(doubleSpinBox_tool_angle_x, 7, 0, 1, 1);

        checkBox_show_tooldir_blend_path = new QCheckBox(form_auto);
        checkBox_show_tooldir_blend_path->setObjectName(QString::fromUtf8("checkBox_show_tooldir_blend_path"));
        checkBox_show_tooldir_blend_path->setChecked(true);

        gridLayout_3->addWidget(checkBox_show_tooldir_blend_path, 2, 0, 1, 1);

        doubleSpinBox_tool_angle_y = new QDoubleSpinBox(form_auto);
        doubleSpinBox_tool_angle_y->setObjectName(QString::fromUtf8("doubleSpinBox_tool_angle_y"));
        doubleSpinBox_tool_angle_y->setMinimum(-100.000000000000000);
        doubleSpinBox_tool_angle_y->setMaximum(100.000000000000000);
        doubleSpinBox_tool_angle_y->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(doubleSpinBox_tool_angle_y, 9, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        toolButton_reload = new QToolButton(form_auto);
        toolButton_reload->setObjectName(QString::fromUtf8("toolButton_reload"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolButton_reload->sizePolicy().hasHeightForWidth());
        toolButton_reload->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/btn_25_25_file_refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_reload->setIcon(icon);
        toolButton_reload->setIconSize(QSize(35, 35));
        toolButton_reload->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_reload->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_reload, 2, 0, 1, 1);

        spinBox_run_from_line = new QSpinBox(form_auto);
        spinBox_run_from_line->setObjectName(QString::fromUtf8("spinBox_run_from_line"));

        gridLayout_2->addWidget(spinBox_run_from_line, 5, 0, 1, 1);

        toolButton_run = new QToolButton(form_auto);
        toolButton_run->setObjectName(QString::fromUtf8("toolButton_run"));
        sizePolicy.setHeightForWidth(toolButton_run->sizePolicy().hasHeightForWidth());
        toolButton_run->setSizePolicy(sizePolicy);
        toolButton_run->setAutoFillBackground(false);
        toolButton_run->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pictures/btn_25_25.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_run->setIcon(icon1);
        toolButton_run->setIconSize(QSize(35, 35));
        toolButton_run->setCheckable(false);
        toolButton_run->setChecked(false);
        toolButton_run->setAutoRepeat(false);
        toolButton_run->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_run->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_run, 3, 0, 1, 1);

        toolButton_pause = new QToolButton(form_auto);
        toolButton_pause->setObjectName(QString::fromUtf8("toolButton_pause"));
        sizePolicy.setHeightForWidth(toolButton_pause->sizePolicy().hasHeightForWidth());
        toolButton_pause->setSizePolicy(sizePolicy);
        toolButton_pause->setAutoFillBackground(false);
        toolButton_pause->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pictures/btn_25_25.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/pictures/btn_25_25_in_orange.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_pause->setIcon(icon2);
        toolButton_pause->setIconSize(QSize(35, 35));
        toolButton_pause->setCheckable(false);
        toolButton_pause->setChecked(false);
        toolButton_pause->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_pause->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_pause, 6, 0, 1, 1);

        toolButton_open = new QToolButton(form_auto);
        toolButton_open->setObjectName(QString::fromUtf8("toolButton_open"));
        sizePolicy.setHeightForWidth(toolButton_open->sizePolicy().hasHeightForWidth());
        toolButton_open->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pictures/btn_25_25_file_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_open->setIcon(icon3);
        toolButton_open->setIconSize(QSize(35, 35));
        toolButton_open->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_open->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_open, 1, 0, 1, 1);

        toolButton_stop = new QToolButton(form_auto);
        toolButton_stop->setObjectName(QString::fromUtf8("toolButton_stop"));
        sizePolicy.setHeightForWidth(toolButton_stop->sizePolicy().hasHeightForWidth());
        toolButton_stop->setSizePolicy(sizePolicy);
        toolButton_stop->setAutoFillBackground(false);
        toolButton_stop->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/pictures/btn_25_25.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/pictures/btn_25_25_in_purple.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_stop->setIcon(icon4);
        toolButton_stop->setIconSize(QSize(35, 35));
        toolButton_stop->setCheckable(false);
        toolButton_stop->setChecked(false);
        toolButton_stop->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_stop->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_stop, 7, 0, 1, 1);

        label_auto = new QLabel(form_auto);
        label_auto->setObjectName(QString::fromUtf8("label_auto"));
        label_auto->setMinimumSize(QSize(0, 35));
        label_auto->setFont(font);
        label_auto->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_auto, 0, 0, 1, 1);

        label = new QLabel(form_auto);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 4, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        label_6 = new QLabel(form_auto);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 8, 0, 1, 1);


        retranslateUi(form_auto);

        QMetaObject::connectSlotsByName(form_auto);
    } // setupUi

    void retranslateUi(QDialog *form_auto)
    {
        form_auto->setWindowTitle(QCoreApplication::translate("form_auto", "Dialog", nullptr));
        label_5->setText(QCoreApplication::translate("form_auto", "tool angle over x", nullptr));
        label_4->setText(QCoreApplication::translate("form_auto", "tooldir blend value mm", nullptr));
        checkBox_tangential_override->setText(QCoreApplication::translate("form_auto", "Tangential override", nullptr));
        label_3->setText(QCoreApplication::translate("form_auto", "%", nullptr));
        label_auto_velocity_procent->setText(QCoreApplication::translate("form_auto", "0", nullptr));
        label_2->setText(QCoreApplication::translate("form_auto", "auto speed -100 - 0 - 100%", nullptr));
        checkBox_show_tooldir_blend_path->setText(QCoreApplication::translate("form_auto", "Show tooldir blend path", nullptr));
        toolButton_reload->setText(QCoreApplication::translate("form_auto", " file reload", nullptr));
        toolButton_run->setText(QCoreApplication::translate("form_auto", " run", nullptr));
        toolButton_pause->setText(QCoreApplication::translate("form_auto", " pause", nullptr));
        toolButton_open->setText(QCoreApplication::translate("form_auto", " file open", nullptr));
        toolButton_stop->setText(QCoreApplication::translate("form_auto", " stop", nullptr));
        label_auto->setText(QCoreApplication::translate("form_auto", "- AUTO -", nullptr));
        label->setText(QCoreApplication::translate("form_auto", "From line", nullptr));
        label_6->setText(QCoreApplication::translate("form_auto", "tool angle over y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class form_auto: public Ui_form_auto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_AUTO_H
