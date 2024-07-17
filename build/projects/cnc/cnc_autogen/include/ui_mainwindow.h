/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_15;
    QStackedWidget *stackedWidget_toplevel;
    QWidget *page_4;
    QWidget *page_2;
    QGridLayout *gridLayout_12;
    QSplitter *splitter_3;
    QStackedWidget *stackedWidget_index;
    QWidget *page_9;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_9;
    QToolButton *toolButton_auto;
    QToolButton *toolButton_manual;
    QToolButton *toolButton_scope;
    QToolButton *toolButton_mdi;
    QToolButton *toolButton_online;
    QSpacerItem *verticalSpacer_2;
    QToolButton *toolButton_empty_2;
    QToolButton *toolButton_edit;
    QToolButton *toolButton_empty_3;
    QToolButton *toolButton_settings;
    QWidget *page_10;
    QStackedWidget *stackedWidget_main;
    QWidget *page_occ_gcode;
    QGridLayout *gridLayout_7;
    QSplitter *splitter;
    QFrame *frame_4;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_occ;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QToolButton *toolButton_view_front;
    QToolButton *toolButton_view_bottom;
    QToolButton *toolButton_view_right;
    QToolButton *toolButton_view_back;
    QToolButton *toolButton_fit_all;
    QToolButton *toolButton_view_3d;
    QToolButton *toolButton_zoom_plus;
    QToolButton *toolButton_view_left;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_view_ortho;
    QToolButton *toolButton_zoom_min;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton_view_top;
    QToolButton *toolButton_clear_toolpath;
    QFrame *frame_gcode;
    QGridLayout *gridLayout_17;
    QGridLayout *gridLayout_gcode;
    QGridLayout *gridLayout_8;
    QLabel *label_current_file;
    QLabel *label_14;
    QWidget *page_settings;
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_settings;
    QFrame *frame_5;
    QGridLayout *gridLayout_3;
    QSplitter *splitter_2;
    QStackedWidget *stackedWidget_mode_manual_auto_mdi;
    QWidget *page_manual;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_page_manual;
    QWidget *page_auto;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_auto;
    QWidget *page_mdi;
    QGridLayout *gridLayout_5;
    QLabel *label_15;
    QSpacerItem *verticalSpacer_4;
    QFrame *frame_3;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_scope;
    QWidget *editor;
    QGridLayout *gridLayout_19;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit_gcode;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *toolButton_textedit_save_as;
    QToolButton *toolButton_text_edit_home;
    QToolButton *toolButton_textedit_save;
    QFrame *frame_2;
    QGridLayout *gridLayout_21;
    QGridLayout *gridLayout_20;
    QLabel *label_13;
    QToolButton *toolButton_remove_line_nrs;
    QLabel *label_16;
    QPlainTextEdit *plainTextEdit;
    QToolButton *toolButton_to_lower_letters;
    QToolButton *toolButton_to_capital_letters;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1116, 723);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 42, 42);\n"
"color: rgb(255, 255, 255);"));
        MainWindow->setIconSize(QSize(30, 30));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAutoFillBackground(false);
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_15 = new QGridLayout(centralwidget);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        stackedWidget_toplevel = new QStackedWidget(centralwidget);
        stackedWidget_toplevel->setObjectName(QString::fromUtf8("stackedWidget_toplevel"));
        stackedWidget_toplevel->setAutoFillBackground(false);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        stackedWidget_toplevel->addWidget(page_4);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_12 = new QGridLayout(page_2);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        splitter_3 = new QSplitter(page_2);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        stackedWidget_index = new QStackedWidget(splitter_3);
        stackedWidget_index->setObjectName(QString::fromUtf8("stackedWidget_index"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget_index->sizePolicy().hasHeightForWidth());
        stackedWidget_index->setSizePolicy(sizePolicy);
        stackedWidget_index->setMinimumSize(QSize(135, 0));
        stackedWidget_index->setMaximumSize(QSize(150, 16777215));
        stackedWidget_index->setFrameShape(QFrame::StyledPanel);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        layoutWidget = new QWidget(page_9);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 109, 642));
        gridLayout_9 = new QGridLayout(layoutWidget);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        toolButton_auto = new QToolButton(layoutWidget);
        toolButton_auto->setObjectName(QString::fromUtf8("toolButton_auto"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButton_auto->sizePolicy().hasHeightForWidth());
        toolButton_auto->setSizePolicy(sizePolicy1);
        toolButton_auto->setAutoFillBackground(false);
        toolButton_auto->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/btn_25_25.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/pictures/btn_25_25_in_green.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_auto->setIcon(icon);
        toolButton_auto->setIconSize(QSize(35, 35));
        toolButton_auto->setCheckable(true);
        toolButton_auto->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_auto->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_auto, 2, 0, 1, 1);

        toolButton_manual = new QToolButton(layoutWidget);
        toolButton_manual->setObjectName(QString::fromUtf8("toolButton_manual"));
        sizePolicy1.setHeightForWidth(toolButton_manual->sizePolicy().hasHeightForWidth());
        toolButton_manual->setSizePolicy(sizePolicy1);
        toolButton_manual->setAutoFillBackground(false);
        toolButton_manual->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_manual->setIcon(icon);
        toolButton_manual->setIconSize(QSize(35, 35));
        toolButton_manual->setCheckable(true);
        toolButton_manual->setChecked(true);
        toolButton_manual->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_manual->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_manual, 1, 0, 1, 1);

        toolButton_scope = new QToolButton(layoutWidget);
        toolButton_scope->setObjectName(QString::fromUtf8("toolButton_scope"));
        sizePolicy1.setHeightForWidth(toolButton_scope->sizePolicy().hasHeightForWidth());
        toolButton_scope->setSizePolicy(sizePolicy1);
        toolButton_scope->setAutoFillBackground(false);
        toolButton_scope->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_scope->setIcon(icon);
        toolButton_scope->setIconSize(QSize(35, 35));
        toolButton_scope->setCheckable(true);
        toolButton_scope->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_scope->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_scope, 6, 0, 1, 1);

        toolButton_mdi = new QToolButton(layoutWidget);
        toolButton_mdi->setObjectName(QString::fromUtf8("toolButton_mdi"));
        sizePolicy1.setHeightForWidth(toolButton_mdi->sizePolicy().hasHeightForWidth());
        toolButton_mdi->setSizePolicy(sizePolicy1);
        toolButton_mdi->setAutoFillBackground(false);
        toolButton_mdi->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_mdi->setIcon(icon);
        toolButton_mdi->setIconSize(QSize(35, 35));
        toolButton_mdi->setCheckable(true);
        toolButton_mdi->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_mdi->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_mdi, 3, 0, 1, 1);

        toolButton_online = new QToolButton(layoutWidget);
        toolButton_online->setObjectName(QString::fromUtf8("toolButton_online"));
        sizePolicy1.setHeightForWidth(toolButton_online->sizePolicy().hasHeightForWidth());
        toolButton_online->setSizePolicy(sizePolicy1);
        toolButton_online->setAutoFillBackground(false);
        toolButton_online->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_online->setIcon(icon);
        toolButton_online->setIconSize(QSize(35, 35));
        toolButton_online->setCheckable(true);
        toolButton_online->setChecked(false);
        toolButton_online->setAutoRepeatDelay(0);
        toolButton_online->setAutoRepeatInterval(0);
        toolButton_online->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_online->setAutoRaise(false);

        gridLayout_9->addWidget(toolButton_online, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer_2, 10, 0, 1, 1);

        toolButton_empty_2 = new QToolButton(layoutWidget);
        toolButton_empty_2->setObjectName(QString::fromUtf8("toolButton_empty_2"));
        sizePolicy1.setHeightForWidth(toolButton_empty_2->sizePolicy().hasHeightForWidth());
        toolButton_empty_2->setSizePolicy(sizePolicy1);
        toolButton_empty_2->setAutoFillBackground(false);
        toolButton_empty_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_empty_2->setIcon(icon);
        toolButton_empty_2->setIconSize(QSize(35, 35));
        toolButton_empty_2->setCheckable(true);
        toolButton_empty_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_empty_2->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_empty_2, 7, 0, 1, 1);

        toolButton_edit = new QToolButton(layoutWidget);
        toolButton_edit->setObjectName(QString::fromUtf8("toolButton_edit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pictures/btn_25_25_text_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_edit->setIcon(icon1);
        toolButton_edit->setIconSize(QSize(35, 35));
        toolButton_edit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_edit->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_edit, 9, 0, 1, 1);

        toolButton_empty_3 = new QToolButton(layoutWidget);
        toolButton_empty_3->setObjectName(QString::fromUtf8("toolButton_empty_3"));
        sizePolicy1.setHeightForWidth(toolButton_empty_3->sizePolicy().hasHeightForWidth());
        toolButton_empty_3->setSizePolicy(sizePolicy1);
        toolButton_empty_3->setAutoFillBackground(false);
        toolButton_empty_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_empty_3->setIcon(icon);
        toolButton_empty_3->setIconSize(QSize(35, 35));
        toolButton_empty_3->setCheckable(true);
        toolButton_empty_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_empty_3->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_empty_3, 8, 0, 1, 1);

        toolButton_settings = new QToolButton(layoutWidget);
        toolButton_settings->setObjectName(QString::fromUtf8("toolButton_settings"));
        sizePolicy1.setHeightForWidth(toolButton_settings->sizePolicy().hasHeightForWidth());
        toolButton_settings->setSizePolicy(sizePolicy1);
        toolButton_settings->setAutoFillBackground(false);
        toolButton_settings->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pictures/btn_25_25_settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_settings->setIcon(icon2);
        toolButton_settings->setIconSize(QSize(35, 35));
        toolButton_settings->setCheckable(true);
        toolButton_settings->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_settings->setAutoRaise(true);

        gridLayout_9->addWidget(toolButton_settings, 4, 0, 1, 1);

        stackedWidget_index->addWidget(page_9);
        page_10 = new QWidget();
        page_10->setObjectName(QString::fromUtf8("page_10"));
        stackedWidget_index->addWidget(page_10);
        splitter_3->addWidget(stackedWidget_index);
        stackedWidget_main = new QStackedWidget(splitter_3);
        stackedWidget_main->setObjectName(QString::fromUtf8("stackedWidget_main"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget_main->sizePolicy().hasHeightForWidth());
        stackedWidget_main->setSizePolicy(sizePolicy2);
        stackedWidget_main->setFrameShape(QFrame::StyledPanel);
        stackedWidget_main->setFrameShadow(QFrame::Plain);
        page_occ_gcode = new QWidget();
        page_occ_gcode->setObjectName(QString::fromUtf8("page_occ_gcode"));
        gridLayout_7 = new QGridLayout(page_occ_gcode);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        splitter = new QSplitter(page_occ_gcode);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        frame_4 = new QFrame(splitter);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy3);
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_11 = new QGridLayout(frame_4);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_occ = new QGridLayout();
        gridLayout_occ->setObjectName(QString::fromUtf8("gridLayout_occ"));

        gridLayout_11->addLayout(gridLayout_occ, 2, 0, 1, 2);

        frame = new QFrame(frame_4);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy4);
        frame->setMinimumSize(QSize(0, 0));
        frame->setMaximumSize(QSize(16777215, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        toolButton_view_front = new QToolButton(frame);
        toolButton_view_front->setObjectName(QString::fromUtf8("toolButton_view_front"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pictures/btn_25_25_view_front.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_view_front->setIcon(icon3);
        toolButton_view_front->setIconSize(QSize(35, 35));
        toolButton_view_front->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_front, 0, 5, 1, 1);

        toolButton_view_bottom = new QToolButton(frame);
        toolButton_view_bottom->setObjectName(QString::fromUtf8("toolButton_view_bottom"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/pictures/btn_25_25_view_bottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_view_bottom->setIcon(icon4);
        toolButton_view_bottom->setIconSize(QSize(35, 35));
        toolButton_view_bottom->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_bottom, 0, 8, 1, 1);

        toolButton_view_right = new QToolButton(frame);
        toolButton_view_right->setObjectName(QString::fromUtf8("toolButton_view_right"));
        toolButton_view_right->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/pictures/btn_25_25_view_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_view_right->setIcon(icon5);
        toolButton_view_right->setIconSize(QSize(35, 35));
        toolButton_view_right->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_right, 0, 10, 1, 1);

        toolButton_view_back = new QToolButton(frame);
        toolButton_view_back->setObjectName(QString::fromUtf8("toolButton_view_back"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/pictures/btn_25_25_view_back.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_view_back->setIcon(icon6);
        toolButton_view_back->setIconSize(QSize(35, 35));
        toolButton_view_back->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_back, 0, 6, 1, 1);

        toolButton_fit_all = new QToolButton(frame);
        toolButton_fit_all->setObjectName(QString::fromUtf8("toolButton_fit_all"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/pictures/btn_25_25_zoom_extends.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_fit_all->setIcon(icon7);
        toolButton_fit_all->setIconSize(QSize(35, 35));
        toolButton_fit_all->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_fit_all, 0, 4, 1, 1);

        toolButton_view_3d = new QToolButton(frame);
        toolButton_view_3d->setObjectName(QString::fromUtf8("toolButton_view_3d"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/pictures/btn_25_25_view_3d.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_view_3d->setIcon(icon8);
        toolButton_view_3d->setIconSize(QSize(35, 35));
        toolButton_view_3d->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_3d, 0, 11, 1, 1);

        toolButton_zoom_plus = new QToolButton(frame);
        toolButton_zoom_plus->setObjectName(QString::fromUtf8("toolButton_zoom_plus"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/pictures/btn_25_25_zoom_plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_plus->setIcon(icon9);
        toolButton_zoom_plus->setIconSize(QSize(35, 35));
        toolButton_zoom_plus->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_zoom_plus, 0, 3, 1, 1);

        toolButton_view_left = new QToolButton(frame);
        toolButton_view_left->setObjectName(QString::fromUtf8("toolButton_view_left"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/pictures/btn_25_25_view_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_view_left->setIcon(icon10);
        toolButton_view_left->setIconSize(QSize(35, 35));
        toolButton_view_left->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_left, 0, 9, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 14, 1, 1);

        toolButton_view_ortho = new QToolButton(frame);
        toolButton_view_ortho->setObjectName(QString::fromUtf8("toolButton_view_ortho"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(toolButton_view_ortho->sizePolicy().hasHeightForWidth());
        toolButton_view_ortho->setSizePolicy(sizePolicy5);
        toolButton_view_ortho->setIcon(icon);
        toolButton_view_ortho->setIconSize(QSize(35, 35));
        toolButton_view_ortho->setCheckable(true);
        toolButton_view_ortho->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_view_ortho->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_ortho, 0, 12, 1, 1);

        toolButton_zoom_min = new QToolButton(frame);
        toolButton_zoom_min->setObjectName(QString::fromUtf8("toolButton_zoom_min"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/pictures/btn_25_25_zoom_min.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_min->setIcon(icon11);
        toolButton_zoom_min->setIconSize(QSize(35, 35));
        toolButton_zoom_min->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_zoom_min, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        toolButton_view_top = new QToolButton(frame);
        toolButton_view_top->setObjectName(QString::fromUtf8("toolButton_view_top"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/pictures/btn_25_25_view_top.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_view_top->setIcon(icon12);
        toolButton_view_top->setIconSize(QSize(35, 35));
        toolButton_view_top->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_view_top, 0, 7, 1, 1);

        toolButton_clear_toolpath = new QToolButton(frame);
        toolButton_clear_toolpath->setObjectName(QString::fromUtf8("toolButton_clear_toolpath"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/pictures/btn_25_25_clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_clear_toolpath->setIcon(icon13);
        toolButton_clear_toolpath->setIconSize(QSize(35, 35));
        toolButton_clear_toolpath->setAutoRaise(true);

        gridLayout_2->addWidget(toolButton_clear_toolpath, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_11->addWidget(frame, 0, 0, 1, 2);

        splitter->addWidget(frame_4);
        frame_gcode = new QFrame(splitter);
        frame_gcode->setObjectName(QString::fromUtf8("frame_gcode"));
        sizePolicy3.setHeightForWidth(frame_gcode->sizePolicy().hasHeightForWidth());
        frame_gcode->setSizePolicy(sizePolicy3);
        frame_gcode->setFrameShape(QFrame::StyledPanel);
        frame_gcode->setFrameShadow(QFrame::Raised);
        gridLayout_17 = new QGridLayout(frame_gcode);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        gridLayout_gcode = new QGridLayout();
        gridLayout_gcode->setObjectName(QString::fromUtf8("gridLayout_gcode"));

        gridLayout_17->addLayout(gridLayout_gcode, 1, 0, 1, 1);

        splitter->addWidget(frame_gcode);

        gridLayout_7->addWidget(splitter, 0, 0, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_current_file = new QLabel(page_occ_gcode);
        label_current_file->setObjectName(QString::fromUtf8("label_current_file"));
        sizePolicy2.setHeightForWidth(label_current_file->sizePolicy().hasHeightForWidth());
        label_current_file->setSizePolicy(sizePolicy2);
        label_current_file->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_current_file, 1, 1, 1, 1);

        label_14 = new QLabel(page_occ_gcode);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(label_14, 1, 0, 1, 1);


        gridLayout_7->addLayout(gridLayout_8, 1, 0, 1, 1);

        stackedWidget_main->addWidget(page_occ_gcode);
        page_settings = new QWidget();
        page_settings->setObjectName(QString::fromUtf8("page_settings"));
        gridLayout_14 = new QGridLayout(page_settings);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_settings = new QGridLayout();
        gridLayout_settings->setObjectName(QString::fromUtf8("gridLayout_settings"));

        gridLayout_14->addLayout(gridLayout_settings, 0, 0, 1, 1);

        stackedWidget_main->addWidget(page_settings);
        splitter_3->addWidget(stackedWidget_main);
        frame_5 = new QFrame(splitter_3);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter_2 = new QSplitter(frame_5);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        stackedWidget_mode_manual_auto_mdi = new QStackedWidget(splitter_2);
        stackedWidget_mode_manual_auto_mdi->setObjectName(QString::fromUtf8("stackedWidget_mode_manual_auto_mdi"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(stackedWidget_mode_manual_auto_mdi->sizePolicy().hasHeightForWidth());
        stackedWidget_mode_manual_auto_mdi->setSizePolicy(sizePolicy6);
        stackedWidget_mode_manual_auto_mdi->setMinimumSize(QSize(0, 0));
        stackedWidget_mode_manual_auto_mdi->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget_mode_manual_auto_mdi->setFrameShape(QFrame::StyledPanel);
        page_manual = new QWidget();
        page_manual->setObjectName(QString::fromUtf8("page_manual"));
        gridLayout_10 = new QGridLayout(page_manual);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_page_manual = new QGridLayout();
        gridLayout_page_manual->setObjectName(QString::fromUtf8("gridLayout_page_manual"));

        gridLayout_10->addLayout(gridLayout_page_manual, 0, 0, 1, 1);

        stackedWidget_mode_manual_auto_mdi->addWidget(page_manual);
        page_auto = new QWidget();
        page_auto->setObjectName(QString::fromUtf8("page_auto"));
        gridLayout_13 = new QGridLayout(page_auto);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_auto = new QGridLayout();
        gridLayout_auto->setObjectName(QString::fromUtf8("gridLayout_auto"));

        gridLayout_13->addLayout(gridLayout_auto, 0, 0, 1, 2);

        stackedWidget_mode_manual_auto_mdi->addWidget(page_auto);
        page_mdi = new QWidget();
        page_mdi->setObjectName(QString::fromUtf8("page_mdi"));
        gridLayout_5 = new QGridLayout(page_mdi);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_15 = new QLabel(page_mdi);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(0, 35));
        QFont font;
        font.setPointSize(12);
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_15, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_4, 1, 0, 1, 1);

        stackedWidget_mode_manual_auto_mdi->addWidget(page_mdi);
        splitter_2->addWidget(stackedWidget_mode_manual_auto_mdi);
        frame_3 = new QFrame(splitter_2);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy7);
        frame_3->setMinimumSize(QSize(0, 300));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_scope = new QGridLayout();
        gridLayout_scope->setObjectName(QString::fromUtf8("gridLayout_scope"));

        gridLayout_6->addLayout(gridLayout_scope, 0, 0, 1, 1);

        splitter_2->addWidget(frame_3);

        gridLayout_3->addWidget(splitter_2, 0, 0, 1, 1);

        splitter_3->addWidget(frame_5);

        gridLayout_12->addWidget(splitter_3, 0, 0, 1, 1);

        stackedWidget_toplevel->addWidget(page_2);
        editor = new QWidget();
        editor->setObjectName(QString::fromUtf8("editor"));
        gridLayout_19 = new QGridLayout(editor);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plainTextEdit_gcode = new QPlainTextEdit(editor);
        plainTextEdit_gcode->setObjectName(QString::fromUtf8("plainTextEdit_gcode"));

        gridLayout->addWidget(plainTextEdit_gcode, 0, 1, 1, 4);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 1, 1, 1);

        toolButton_textedit_save_as = new QToolButton(editor);
        toolButton_textedit_save_as->setObjectName(QString::fromUtf8("toolButton_textedit_save_as"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/pictures/btn_25_25_file_save_as.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_textedit_save_as->setIcon(icon14);
        toolButton_textedit_save_as->setIconSize(QSize(35, 35));
        toolButton_textedit_save_as->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_textedit_save_as->setAutoRaise(true);

        gridLayout->addWidget(toolButton_textedit_save_as, 1, 4, 1, 1);

        toolButton_text_edit_home = new QToolButton(editor);
        toolButton_text_edit_home->setObjectName(QString::fromUtf8("toolButton_text_edit_home"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/pictures/btn_25_25_home.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_text_edit_home->setIcon(icon15);
        toolButton_text_edit_home->setIconSize(QSize(35, 35));
        toolButton_text_edit_home->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_text_edit_home->setAutoRaise(true);

        gridLayout->addWidget(toolButton_text_edit_home, 1, 2, 1, 1);

        toolButton_textedit_save = new QToolButton(editor);
        toolButton_textedit_save->setObjectName(QString::fromUtf8("toolButton_textedit_save"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/pictures/btn_25_25_file_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_textedit_save->setIcon(icon16);
        toolButton_textedit_save->setIconSize(QSize(35, 35));
        toolButton_textedit_save->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_textedit_save->setAutoRaise(true);

        gridLayout->addWidget(toolButton_textedit_save, 1, 3, 1, 1);


        gridLayout_19->addLayout(gridLayout, 0, 2, 1, 1);

        frame_2 = new QFrame(editor);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy5.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy5);
        frame_2->setMinimumSize(QSize(200, 0));
        frame_2->setMaximumSize(QSize(16777215, 16777215));
        frame_2->setBaseSize(QSize(0, 0));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_21 = new QGridLayout(frame_2);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        gridLayout_20 = new QGridLayout();
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_20->addWidget(label_13, 0, 0, 1, 1);

        toolButton_remove_line_nrs = new QToolButton(frame_2);
        toolButton_remove_line_nrs->setObjectName(QString::fromUtf8("toolButton_remove_line_nrs"));
        sizePolicy1.setHeightForWidth(toolButton_remove_line_nrs->sizePolicy().hasHeightForWidth());
        toolButton_remove_line_nrs->setSizePolicy(sizePolicy1);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/pictures/btn_25_25.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_remove_line_nrs->setIcon(icon17);
        toolButton_remove_line_nrs->setIconSize(QSize(35, 35));
        toolButton_remove_line_nrs->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_remove_line_nrs->setAutoRaise(true);

        gridLayout_20->addWidget(toolButton_remove_line_nrs, 1, 0, 1, 1);

        label_16 = new QLabel(frame_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_20->addWidget(label_16, 4, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(frame_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy8);
        plainTextEdit->setMinimumSize(QSize(350, 0));

        gridLayout_20->addWidget(plainTextEdit, 5, 0, 1, 1);

        toolButton_to_lower_letters = new QToolButton(frame_2);
        toolButton_to_lower_letters->setObjectName(QString::fromUtf8("toolButton_to_lower_letters"));
        toolButton_to_lower_letters->setIcon(icon17);
        toolButton_to_lower_letters->setIconSize(QSize(35, 35));
        toolButton_to_lower_letters->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_to_lower_letters->setAutoRaise(true);

        gridLayout_20->addWidget(toolButton_to_lower_letters, 3, 0, 1, 1);

        toolButton_to_capital_letters = new QToolButton(frame_2);
        toolButton_to_capital_letters->setObjectName(QString::fromUtf8("toolButton_to_capital_letters"));
        toolButton_to_capital_letters->setIcon(icon17);
        toolButton_to_capital_letters->setIconSize(QSize(35, 35));
        toolButton_to_capital_letters->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_to_capital_letters->setAutoRaise(true);

        gridLayout_20->addWidget(toolButton_to_capital_letters, 2, 0, 1, 1);


        gridLayout_21->addLayout(gridLayout_20, 0, 1, 1, 1);


        gridLayout_19->addWidget(frame_2, 0, 0, 1, 1);

        stackedWidget_toplevel->addWidget(editor);

        gridLayout_15->addWidget(stackedWidget_toplevel, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget_toplevel->setCurrentIndex(1);
        stackedWidget_index->setCurrentIndex(0);
        stackedWidget_main->setCurrentIndex(0);
        stackedWidget_mode_manual_auto_mdi->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "cnc controller", nullptr));
        toolButton_auto->setText(QCoreApplication::translate("MainWindow", " auto", nullptr));
        toolButton_manual->setText(QCoreApplication::translate("MainWindow", " manual", nullptr));
        toolButton_scope->setText(QCoreApplication::translate("MainWindow", " scope", nullptr));
        toolButton_mdi->setText(QCoreApplication::translate("MainWindow", " mdi", nullptr));
        toolButton_online->setText(QCoreApplication::translate("MainWindow", " offline", nullptr));
        toolButton_empty_2->setText(QCoreApplication::translate("MainWindow", " ..", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_edit->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>edit in gcode editor.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_edit->setText(QCoreApplication::translate("MainWindow", " editor", nullptr));
        toolButton_empty_3->setText(QCoreApplication::translate("MainWindow", " ..", nullptr));
        toolButton_settings->setText(QCoreApplication::translate("MainWindow", " settings", nullptr));
        toolButton_view_front->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_view_bottom->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_view_right->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_view_back->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_fit_all->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_view_3d->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_zoom_plus->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_view_left->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_view_ortho->setText(QCoreApplication::translate("MainWindow", " ORTHO", nullptr));
        toolButton_zoom_min->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_view_top->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_clear_toolpath->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_current_file->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Current file: ", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "- MDI -", nullptr));
        plainTextEdit_gcode->setPlainText(QString());
        toolButton_textedit_save_as->setText(QCoreApplication::translate("MainWindow", " save as", nullptr));
        toolButton_text_edit_home->setText(QCoreApplication::translate("MainWindow", " back", nullptr));
        toolButton_textedit_save->setText(QCoreApplication::translate("MainWindow", " save", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Editor tools:", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_remove_line_nrs->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Remove line numbers and start spacing from text.</p><p>From:</p><p><span style=\" font-weight:700;\">N001 X0 Y0 Z0</span></p><p>to :</p><p><span style=\" font-weight:700;\">X0 Y0 Z0</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_remove_line_nrs->setText(QCoreApplication::translate("MainWindow", " remove line nr's", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Gcode legenda:", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("MainWindow", "G0 	line rapid\n"
"G1 	line feed\n"
"G2 	arc, cirlce, helix clockwise cw\n"
"G3 	arc, circle, helix counter clockwise ccw\n"
"G5          	spline\n"
"G9 	general motion \n"
"\n"
"G17  	xy plane \n"
"G18  	xz plane \n"
"G19  	yz plane \n"
"\n"
"G64 P Q L 	Path options\n"
"	P=tollerance\n"
"	Q=naive cam tollerance\n"
"	L=helix continuity\n"
"\n"
"# Spline valid gcode:\n"
"G5              	x0 y0 z0 	# spline start point.	\n"
"	x50 y50	# spline control point, newline\n"
"	# more control points, newline.\n"
"	x100 y0        # spline end point, newline\n"
"G0 ...\n"
"", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_to_lower_letters->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>From:</p><p><span style=\" font-weight:700;\">X0 Y0 Z0</span></p><p>to :</p><p><span style=\" font-weight:700;\">x0 x0 x0</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_to_lower_letters->setText(QCoreApplication::translate("MainWindow", " to lower letters", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_to_capital_letters->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>From:</p><p><span style=\" font-weight:700;\">x0 x0 x0</span></p><p>to :</p><p><span style=\" font-weight:700;\">X0 Y0 Z0</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_to_capital_letters->setText(QCoreApplication::translate("MainWindow", " to capital letters", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
