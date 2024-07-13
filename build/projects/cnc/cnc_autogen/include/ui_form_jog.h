/********************************************************************************
** Form generated from reading UI file 'form_jog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_JOG_H
#define UI_FORM_JOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_form_jog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_jog_settings;
    QLabel *label_jog_velocity_procent;
    QLabel *label_3;
    QToolButton *toolButton_jog_step;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_stepsize;
    QLabel *label_2;
    QLabel *label_4;
    QSlider *horizontalSlider_jog_velocity_procent;
    QGridLayout *gridLayout_jog_buttons_xyz;
    QToolButton *toolButton_jog_a_plus;
    QToolButton *toolButton_jog_u_min;
    QToolButton *toolButton_jog_c_min;
    QToolButton *toolButton_jog_z_plus;
    QToolButton *toolButton_jog_v_min;
    QToolButton *toolButton_jog_b_min;
    QToolButton *toolButton_jog_x_min;
    QToolButton *toolButton_jog_y_plus;
    QToolButton *toolButton_jog_x_plus;
    QToolButton *toolButton_jog_b_plus;
    QToolButton *toolButton_jog_v_plus;
    QToolButton *toolButton_jog_z_min;
    QToolButton *toolButton_jog_w_plus;
    QToolButton *toolButton_jog_a_min;
    QToolButton *toolButton_jog_u_plus;
    QToolButton *toolButton_jog_w_min;
    QToolButton *toolButton_jog_c_plus;
    QToolButton *toolButton_jog_y_min;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QToolButton *toolButton_jog_goto_zero_xyz;
    QToolButton *toolButton_jog_goto_zero_abc;
    QToolButton *toolButton_jog_goto_zero_uvw;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *form_jog)
    {
        if (form_jog->objectName().isEmpty())
            form_jog->setObjectName(QString::fromUtf8("form_jog"));
        form_jog->resize(366, 616);
        form_jog->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 42, 42);\n"
"color: rgb(255, 255, 255);"));
        gridLayout_2 = new QGridLayout(form_jog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_jog_settings = new QGridLayout();
        gridLayout_jog_settings->setObjectName(QString::fromUtf8("gridLayout_jog_settings"));
        label_jog_velocity_procent = new QLabel(form_jog);
        label_jog_velocity_procent->setObjectName(QString::fromUtf8("label_jog_velocity_procent"));
        QFont font;
        font.setPointSize(12);
        label_jog_velocity_procent->setFont(font);

        gridLayout_jog_settings->addWidget(label_jog_velocity_procent, 3, 0, 1, 2);

        label_3 = new QLabel(form_jog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_jog_settings->addWidget(label_3, 3, 2, 1, 1);

        toolButton_jog_step = new QToolButton(form_jog);
        toolButton_jog_step->setObjectName(QString::fromUtf8("toolButton_jog_step"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolButton_jog_step->sizePolicy().hasHeightForWidth());
        toolButton_jog_step->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/btn_25_25.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/pictures/btn_25_25_in_green.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_jog_step->setIcon(icon);
        toolButton_jog_step->setIconSize(QSize(35, 35));
        toolButton_jog_step->setCheckable(true);
        toolButton_jog_step->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_jog_step->setAutoRaise(true);

        gridLayout_jog_settings->addWidget(toolButton_jog_step, 4, 0, 1, 3);

        label = new QLabel(form_jog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_jog_settings->addWidget(label, 5, 0, 1, 3);

        doubleSpinBox_stepsize = new QDoubleSpinBox(form_jog);
        doubleSpinBox_stepsize->setObjectName(QString::fromUtf8("doubleSpinBox_stepsize"));
        doubleSpinBox_stepsize->setMinimumSize(QSize(0, 35));
        doubleSpinBox_stepsize->setMaximum(10000.000000000000000);
        doubleSpinBox_stepsize->setSingleStep(0.100000000000000);
        doubleSpinBox_stepsize->setValue(1.000000000000000);

        gridLayout_jog_settings->addWidget(doubleSpinBox_stepsize, 6, 0, 1, 3);

        label_2 = new QLabel(form_jog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_jog_settings->addWidget(label_2, 1, 0, 1, 3);

        label_4 = new QLabel(form_jog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 35));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_jog_settings->addWidget(label_4, 0, 0, 1, 3);

        horizontalSlider_jog_velocity_procent = new QSlider(form_jog);
        horizontalSlider_jog_velocity_procent->setObjectName(QString::fromUtf8("horizontalSlider_jog_velocity_procent"));
        horizontalSlider_jog_velocity_procent->setMaximum(100);
        horizontalSlider_jog_velocity_procent->setValue(50);
        horizontalSlider_jog_velocity_procent->setOrientation(Qt::Horizontal);

        gridLayout_jog_settings->addWidget(horizontalSlider_jog_velocity_procent, 2, 0, 1, 3);


        gridLayout_2->addLayout(gridLayout_jog_settings, 0, 0, 1, 1);

        gridLayout_jog_buttons_xyz = new QGridLayout();
        gridLayout_jog_buttons_xyz->setObjectName(QString::fromUtf8("gridLayout_jog_buttons_xyz"));
        toolButton_jog_a_plus = new QToolButton(form_jog);
        toolButton_jog_a_plus->setObjectName(QString::fromUtf8("toolButton_jog_a_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_a_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_a_plus->setSizePolicy(sizePolicy);
        toolButton_jog_a_plus->setAutoFillBackground(false);
        toolButton_jog_a_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_a_plus->setIcon(icon);
        toolButton_jog_a_plus->setIconSize(QSize(35, 35));
        toolButton_jog_a_plus->setCheckable(false);
        toolButton_jog_a_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_a_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_a_plus, 2, 1, 1, 1);

        toolButton_jog_u_min = new QToolButton(form_jog);
        toolButton_jog_u_min->setObjectName(QString::fromUtf8("toolButton_jog_u_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_u_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_u_min->setSizePolicy(sizePolicy);
        toolButton_jog_u_min->setAutoFillBackground(false);
        toolButton_jog_u_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_u_min->setIcon(icon);
        toolButton_jog_u_min->setIconSize(QSize(35, 35));
        toolButton_jog_u_min->setCheckable(false);
        toolButton_jog_u_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_u_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_u_min, 3, 0, 1, 1);

        toolButton_jog_c_min = new QToolButton(form_jog);
        toolButton_jog_c_min->setObjectName(QString::fromUtf8("toolButton_jog_c_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_c_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_c_min->setSizePolicy(sizePolicy);
        toolButton_jog_c_min->setAutoFillBackground(false);
        toolButton_jog_c_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_c_min->setIcon(icon);
        toolButton_jog_c_min->setIconSize(QSize(35, 35));
        toolButton_jog_c_min->setCheckable(false);
        toolButton_jog_c_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_c_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_c_min, 2, 4, 1, 1);

        toolButton_jog_z_plus = new QToolButton(form_jog);
        toolButton_jog_z_plus->setObjectName(QString::fromUtf8("toolButton_jog_z_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_z_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_z_plus->setSizePolicy(sizePolicy);
        toolButton_jog_z_plus->setAutoFillBackground(false);
        toolButton_jog_z_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_z_plus->setIcon(icon);
        toolButton_jog_z_plus->setIconSize(QSize(35, 35));
        toolButton_jog_z_plus->setCheckable(false);
        toolButton_jog_z_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_z_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_z_plus, 1, 5, 1, 1);

        toolButton_jog_v_min = new QToolButton(form_jog);
        toolButton_jog_v_min->setObjectName(QString::fromUtf8("toolButton_jog_v_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_v_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_v_min->setSizePolicy(sizePolicy);
        toolButton_jog_v_min->setAutoFillBackground(false);
        toolButton_jog_v_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_v_min->setIcon(icon);
        toolButton_jog_v_min->setIconSize(QSize(35, 35));
        toolButton_jog_v_min->setCheckable(false);
        toolButton_jog_v_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_v_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_v_min, 3, 2, 1, 1);

        toolButton_jog_b_min = new QToolButton(form_jog);
        toolButton_jog_b_min->setObjectName(QString::fromUtf8("toolButton_jog_b_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_b_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_b_min->setSizePolicy(sizePolicy);
        toolButton_jog_b_min->setAutoFillBackground(false);
        toolButton_jog_b_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_b_min->setIcon(icon);
        toolButton_jog_b_min->setIconSize(QSize(35, 35));
        toolButton_jog_b_min->setCheckable(false);
        toolButton_jog_b_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_b_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_b_min, 2, 2, 1, 1);

        toolButton_jog_x_min = new QToolButton(form_jog);
        toolButton_jog_x_min->setObjectName(QString::fromUtf8("toolButton_jog_x_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_x_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_x_min->setSizePolicy(sizePolicy);
        toolButton_jog_x_min->setMinimumSize(QSize(0, 0));
        toolButton_jog_x_min->setAutoFillBackground(false);
        toolButton_jog_x_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_x_min->setIcon(icon);
        toolButton_jog_x_min->setIconSize(QSize(35, 35));
        toolButton_jog_x_min->setCheckable(false);
        toolButton_jog_x_min->setAutoRepeatDelay(300);
        toolButton_jog_x_min->setAutoRepeatInterval(100);
        toolButton_jog_x_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_x_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_x_min, 1, 0, 1, 1);

        toolButton_jog_y_plus = new QToolButton(form_jog);
        toolButton_jog_y_plus->setObjectName(QString::fromUtf8("toolButton_jog_y_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_y_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_y_plus->setSizePolicy(sizePolicy);
        toolButton_jog_y_plus->setAutoFillBackground(false);
        toolButton_jog_y_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_y_plus->setIcon(icon);
        toolButton_jog_y_plus->setIconSize(QSize(35, 35));
        toolButton_jog_y_plus->setCheckable(false);
        toolButton_jog_y_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_y_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_y_plus, 1, 3, 1, 1);

        toolButton_jog_x_plus = new QToolButton(form_jog);
        toolButton_jog_x_plus->setObjectName(QString::fromUtf8("toolButton_jog_x_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_x_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_x_plus->setSizePolicy(sizePolicy);
        toolButton_jog_x_plus->setAutoFillBackground(false);
        toolButton_jog_x_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_x_plus->setIcon(icon);
        toolButton_jog_x_plus->setIconSize(QSize(35, 35));
        toolButton_jog_x_plus->setCheckable(false);
        toolButton_jog_x_plus->setAutoRepeatDelay(300);
        toolButton_jog_x_plus->setAutoRepeatInterval(100);
        toolButton_jog_x_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_x_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_x_plus, 1, 1, 1, 1);

        toolButton_jog_b_plus = new QToolButton(form_jog);
        toolButton_jog_b_plus->setObjectName(QString::fromUtf8("toolButton_jog_b_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_b_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_b_plus->setSizePolicy(sizePolicy);
        toolButton_jog_b_plus->setAutoFillBackground(false);
        toolButton_jog_b_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_b_plus->setIcon(icon);
        toolButton_jog_b_plus->setIconSize(QSize(35, 35));
        toolButton_jog_b_plus->setCheckable(false);
        toolButton_jog_b_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_b_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_b_plus, 2, 3, 1, 1);

        toolButton_jog_v_plus = new QToolButton(form_jog);
        toolButton_jog_v_plus->setObjectName(QString::fromUtf8("toolButton_jog_v_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_v_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_v_plus->setSizePolicy(sizePolicy);
        toolButton_jog_v_plus->setAutoFillBackground(false);
        toolButton_jog_v_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_v_plus->setIcon(icon);
        toolButton_jog_v_plus->setIconSize(QSize(35, 35));
        toolButton_jog_v_plus->setCheckable(false);
        toolButton_jog_v_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_v_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_v_plus, 3, 3, 1, 1);

        toolButton_jog_z_min = new QToolButton(form_jog);
        toolButton_jog_z_min->setObjectName(QString::fromUtf8("toolButton_jog_z_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_z_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_z_min->setSizePolicy(sizePolicy);
        toolButton_jog_z_min->setMinimumSize(QSize(0, 0));
        toolButton_jog_z_min->setAutoFillBackground(false);
        toolButton_jog_z_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_z_min->setIcon(icon);
        toolButton_jog_z_min->setIconSize(QSize(35, 35));
        toolButton_jog_z_min->setCheckable(false);
        toolButton_jog_z_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_z_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_z_min, 1, 4, 1, 1);

        toolButton_jog_w_plus = new QToolButton(form_jog);
        toolButton_jog_w_plus->setObjectName(QString::fromUtf8("toolButton_jog_w_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_w_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_w_plus->setSizePolicy(sizePolicy);
        toolButton_jog_w_plus->setAutoFillBackground(false);
        toolButton_jog_w_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_w_plus->setIcon(icon);
        toolButton_jog_w_plus->setIconSize(QSize(35, 35));
        toolButton_jog_w_plus->setCheckable(false);
        toolButton_jog_w_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_w_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_w_plus, 3, 5, 1, 1);

        toolButton_jog_a_min = new QToolButton(form_jog);
        toolButton_jog_a_min->setObjectName(QString::fromUtf8("toolButton_jog_a_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_a_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_a_min->setSizePolicy(sizePolicy);
        toolButton_jog_a_min->setAutoFillBackground(false);
        toolButton_jog_a_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_a_min->setIcon(icon);
        toolButton_jog_a_min->setIconSize(QSize(35, 35));
        toolButton_jog_a_min->setCheckable(false);
        toolButton_jog_a_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_a_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_a_min, 2, 0, 1, 1);

        toolButton_jog_u_plus = new QToolButton(form_jog);
        toolButton_jog_u_plus->setObjectName(QString::fromUtf8("toolButton_jog_u_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_u_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_u_plus->setSizePolicy(sizePolicy);
        toolButton_jog_u_plus->setAutoFillBackground(false);
        toolButton_jog_u_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_u_plus->setIcon(icon);
        toolButton_jog_u_plus->setIconSize(QSize(35, 35));
        toolButton_jog_u_plus->setCheckable(false);
        toolButton_jog_u_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_u_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_u_plus, 3, 1, 1, 1);

        toolButton_jog_w_min = new QToolButton(form_jog);
        toolButton_jog_w_min->setObjectName(QString::fromUtf8("toolButton_jog_w_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_w_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_w_min->setSizePolicy(sizePolicy);
        toolButton_jog_w_min->setAutoFillBackground(false);
        toolButton_jog_w_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_w_min->setIcon(icon);
        toolButton_jog_w_min->setIconSize(QSize(35, 35));
        toolButton_jog_w_min->setCheckable(false);
        toolButton_jog_w_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_w_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_w_min, 3, 4, 1, 1);

        toolButton_jog_c_plus = new QToolButton(form_jog);
        toolButton_jog_c_plus->setObjectName(QString::fromUtf8("toolButton_jog_c_plus"));
        sizePolicy.setHeightForWidth(toolButton_jog_c_plus->sizePolicy().hasHeightForWidth());
        toolButton_jog_c_plus->setSizePolicy(sizePolicy);
        toolButton_jog_c_plus->setAutoFillBackground(false);
        toolButton_jog_c_plus->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_c_plus->setIcon(icon);
        toolButton_jog_c_plus->setIconSize(QSize(35, 35));
        toolButton_jog_c_plus->setCheckable(false);
        toolButton_jog_c_plus->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_c_plus->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_c_plus, 2, 5, 1, 1);

        toolButton_jog_y_min = new QToolButton(form_jog);
        toolButton_jog_y_min->setObjectName(QString::fromUtf8("toolButton_jog_y_min"));
        sizePolicy.setHeightForWidth(toolButton_jog_y_min->sizePolicy().hasHeightForWidth());
        toolButton_jog_y_min->setSizePolicy(sizePolicy);
        toolButton_jog_y_min->setMinimumSize(QSize(0, 0));
        toolButton_jog_y_min->setAutoFillBackground(false);
        toolButton_jog_y_min->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_y_min->setIcon(icon);
        toolButton_jog_y_min->setIconSize(QSize(35, 35));
        toolButton_jog_y_min->setCheckable(false);
        toolButton_jog_y_min->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_y_min->setAutoRaise(true);

        gridLayout_jog_buttons_xyz->addWidget(toolButton_jog_y_min, 1, 2, 1, 1);

        label_5 = new QLabel(form_jog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_jog_buttons_xyz->addWidget(label_5, 0, 0, 1, 6);


        gridLayout_2->addLayout(gridLayout_jog_buttons_xyz, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(form_jog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 0, 0, 1, 3);

        toolButton_jog_goto_zero_xyz = new QToolButton(form_jog);
        toolButton_jog_goto_zero_xyz->setObjectName(QString::fromUtf8("toolButton_jog_goto_zero_xyz"));
        sizePolicy.setHeightForWidth(toolButton_jog_goto_zero_xyz->sizePolicy().hasHeightForWidth());
        toolButton_jog_goto_zero_xyz->setSizePolicy(sizePolicy);
        toolButton_jog_goto_zero_xyz->setAutoFillBackground(false);
        toolButton_jog_goto_zero_xyz->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_goto_zero_xyz->setIcon(icon);
        toolButton_jog_goto_zero_xyz->setIconSize(QSize(35, 35));
        toolButton_jog_goto_zero_xyz->setCheckable(false);
        toolButton_jog_goto_zero_xyz->setAutoRepeatDelay(0);
        toolButton_jog_goto_zero_xyz->setAutoRepeatInterval(0);
        toolButton_jog_goto_zero_xyz->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_goto_zero_xyz->setAutoRaise(true);

        gridLayout->addWidget(toolButton_jog_goto_zero_xyz, 1, 0, 1, 1);

        toolButton_jog_goto_zero_abc = new QToolButton(form_jog);
        toolButton_jog_goto_zero_abc->setObjectName(QString::fromUtf8("toolButton_jog_goto_zero_abc"));
        sizePolicy.setHeightForWidth(toolButton_jog_goto_zero_abc->sizePolicy().hasHeightForWidth());
        toolButton_jog_goto_zero_abc->setSizePolicy(sizePolicy);
        toolButton_jog_goto_zero_abc->setAutoFillBackground(false);
        toolButton_jog_goto_zero_abc->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_goto_zero_abc->setIcon(icon);
        toolButton_jog_goto_zero_abc->setIconSize(QSize(35, 35));
        toolButton_jog_goto_zero_abc->setCheckable(false);
        toolButton_jog_goto_zero_abc->setAutoRepeatDelay(0);
        toolButton_jog_goto_zero_abc->setAutoRepeatInterval(0);
        toolButton_jog_goto_zero_abc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_goto_zero_abc->setAutoRaise(true);

        gridLayout->addWidget(toolButton_jog_goto_zero_abc, 1, 1, 1, 1);

        toolButton_jog_goto_zero_uvw = new QToolButton(form_jog);
        toolButton_jog_goto_zero_uvw->setObjectName(QString::fromUtf8("toolButton_jog_goto_zero_uvw"));
        sizePolicy.setHeightForWidth(toolButton_jog_goto_zero_uvw->sizePolicy().hasHeightForWidth());
        toolButton_jog_goto_zero_uvw->setSizePolicy(sizePolicy);
        toolButton_jog_goto_zero_uvw->setAutoFillBackground(false);
        toolButton_jog_goto_zero_uvw->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jog_goto_zero_uvw->setIcon(icon);
        toolButton_jog_goto_zero_uvw->setIconSize(QSize(35, 35));
        toolButton_jog_goto_zero_uvw->setCheckable(false);
        toolButton_jog_goto_zero_uvw->setAutoRepeatDelay(0);
        toolButton_jog_goto_zero_uvw->setAutoRepeatInterval(0);
        toolButton_jog_goto_zero_uvw->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_jog_goto_zero_uvw->setAutoRaise(true);

        gridLayout->addWidget(toolButton_jog_goto_zero_uvw, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);


        retranslateUi(form_jog);

        QMetaObject::connectSlotsByName(form_jog);
    } // setupUi

    void retranslateUi(QDialog *form_jog)
    {
        form_jog->setWindowTitle(QCoreApplication::translate("form_jog", "Dialog", nullptr));
        label_jog_velocity_procent->setText(QCoreApplication::translate("form_jog", "0", nullptr));
        label_3->setText(QCoreApplication::translate("form_jog", "%", nullptr));
        toolButton_jog_step->setText(QCoreApplication::translate("form_jog", " jog step", nullptr));
        label->setText(QCoreApplication::translate("form_jog", "step size unit", nullptr));
        label_2->setText(QCoreApplication::translate("form_jog", "jog speed 0-100%", nullptr));
        label_4->setText(QCoreApplication::translate("form_jog", "- manual -", nullptr));
        toolButton_jog_a_plus->setText(QCoreApplication::translate("form_jog", "a +", nullptr));
        toolButton_jog_u_min->setText(QCoreApplication::translate("form_jog", "u -", nullptr));
        toolButton_jog_c_min->setText(QCoreApplication::translate("form_jog", "c -", nullptr));
        toolButton_jog_z_plus->setText(QCoreApplication::translate("form_jog", "z +", nullptr));
        toolButton_jog_v_min->setText(QCoreApplication::translate("form_jog", "v -", nullptr));
        toolButton_jog_b_min->setText(QCoreApplication::translate("form_jog", "b -", nullptr));
        toolButton_jog_x_min->setText(QCoreApplication::translate("form_jog", "x -", nullptr));
        toolButton_jog_y_plus->setText(QCoreApplication::translate("form_jog", "y +", nullptr));
        toolButton_jog_x_plus->setText(QCoreApplication::translate("form_jog", "x +", nullptr));
        toolButton_jog_b_plus->setText(QCoreApplication::translate("form_jog", "b +", nullptr));
        toolButton_jog_v_plus->setText(QCoreApplication::translate("form_jog", "v +", nullptr));
        toolButton_jog_z_min->setText(QCoreApplication::translate("form_jog", "z -", nullptr));
        toolButton_jog_w_plus->setText(QCoreApplication::translate("form_jog", "w +", nullptr));
        toolButton_jog_a_min->setText(QCoreApplication::translate("form_jog", "a -", nullptr));
        toolButton_jog_u_plus->setText(QCoreApplication::translate("form_jog", "u +", nullptr));
        toolButton_jog_w_min->setText(QCoreApplication::translate("form_jog", "w -", nullptr));
        toolButton_jog_c_plus->setText(QCoreApplication::translate("form_jog", "c +", nullptr));
        toolButton_jog_y_min->setText(QCoreApplication::translate("form_jog", "y -", nullptr));
        label_5->setText(QCoreApplication::translate("form_jog", "- jog controls -", nullptr));
        label_6->setText(QCoreApplication::translate("form_jog", "- jog goto zero -", nullptr));
        toolButton_jog_goto_zero_xyz->setText(QCoreApplication::translate("form_jog", " xyz", nullptr));
        toolButton_jog_goto_zero_abc->setText(QCoreApplication::translate("form_jog", "abc", nullptr));
        toolButton_jog_goto_zero_uvw->setText(QCoreApplication::translate("form_jog", "uvw", nullptr));
    } // retranslateUi

};

namespace Ui {
    class form_jog: public Ui_form_jog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_JOG_H
