/********************************************************************************
** Form generated from reading UI file 'form_scope.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_SCOPE_H
#define UI_FORM_SCOPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_form_scope
{
public:
    QGridLayout *gridLayout_4;
    QSplitter *splitter;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_scope_tp;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_bufsize;
    QLabel *label;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_range_y_max;
    QDoubleSpinBox *doubleSpinBox_scale_v0;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_scale_v2;
    QDoubleSpinBox *doubleSpinBox_range_y_min;
    QDoubleSpinBox *doubleSpinBox_scale_v1;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *form_scope)
    {
        if (form_scope->objectName().isEmpty())
            form_scope->setObjectName(QString::fromUtf8("form_scope"));
        form_scope->resize(661, 538);
        form_scope->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 42, 42);\n"
"color: rgb(255, 255, 255);"));
        gridLayout_4 = new QGridLayout(form_scope);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(form_scope);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_scope_tp = new QGridLayout();
        gridLayout_scope_tp->setSpacing(0);
        gridLayout_scope_tp->setObjectName(QString::fromUtf8("gridLayout_scope_tp"));

        gridLayout_3->addLayout(gridLayout_scope_tp, 0, 0, 1, 1);

        splitter->addWidget(frame_2);
        frame = new QFrame(splitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMaximumSize(QSize(16777215, 75));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        doubleSpinBox_bufsize = new QDoubleSpinBox(frame);
        doubleSpinBox_bufsize->setObjectName(QString::fromUtf8("doubleSpinBox_bufsize"));
        doubleSpinBox_bufsize->setMaximum(500.000000000000000);
        doubleSpinBox_bufsize->setValue(80.000000000000000);

        gridLayout->addWidget(doubleSpinBox_bufsize, 2, 3, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        doubleSpinBox_range_y_max = new QDoubleSpinBox(frame);
        doubleSpinBox_range_y_max->setObjectName(QString::fromUtf8("doubleSpinBox_range_y_max"));
        doubleSpinBox_range_y_max->setMaximum(1000.000000000000000);
        doubleSpinBox_range_y_max->setValue(250.000000000000000);

        gridLayout->addWidget(doubleSpinBox_range_y_max, 1, 3, 1, 1);

        doubleSpinBox_scale_v0 = new QDoubleSpinBox(frame);
        doubleSpinBox_scale_v0->setObjectName(QString::fromUtf8("doubleSpinBox_scale_v0"));
        doubleSpinBox_scale_v0->setMaximum(1000.000000000000000);
        doubleSpinBox_scale_v0->setSingleStep(0.100000000000000);
        doubleSpinBox_scale_v0->setValue(5.000000000000000);

        gridLayout->addWidget(doubleSpinBox_scale_v0, 0, 1, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 2, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        doubleSpinBox_scale_v2 = new QDoubleSpinBox(frame);
        doubleSpinBox_scale_v2->setObjectName(QString::fromUtf8("doubleSpinBox_scale_v2"));
        doubleSpinBox_scale_v2->setMaximum(1000.000000000000000);
        doubleSpinBox_scale_v2->setSingleStep(0.100000000000000);
        doubleSpinBox_scale_v2->setValue(0.000000000000000);

        gridLayout->addWidget(doubleSpinBox_scale_v2, 2, 1, 1, 1);

        doubleSpinBox_range_y_min = new QDoubleSpinBox(frame);
        doubleSpinBox_range_y_min->setObjectName(QString::fromUtf8("doubleSpinBox_range_y_min"));
        doubleSpinBox_range_y_min->setMinimum(-1000.000000000000000);
        doubleSpinBox_range_y_min->setMaximum(0.000000000000000);
        doubleSpinBox_range_y_min->setValue(-120.000000000000000);

        gridLayout->addWidget(doubleSpinBox_range_y_min, 0, 3, 1, 1);

        doubleSpinBox_scale_v1 = new QDoubleSpinBox(frame);
        doubleSpinBox_scale_v1->setObjectName(QString::fromUtf8("doubleSpinBox_scale_v1"));
        doubleSpinBox_scale_v1->setMaximum(1000.000000000000000);
        doubleSpinBox_scale_v1->setSingleStep(0.100000000000000);
        doubleSpinBox_scale_v1->setValue(3.000000000000000);

        gridLayout->addWidget(doubleSpinBox_scale_v1, 1, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 1, 1, 1);

        splitter->addWidget(frame);

        gridLayout_4->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(form_scope);

        QMetaObject::connectSlotsByName(form_scope);
    } // setupUi

    void retranslateUi(QDialog *form_scope)
    {
        form_scope->setWindowTitle(QCoreApplication::translate("form_scope", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("form_scope", " range y max ", nullptr));
        label->setText(QCoreApplication::translate("form_scope", "scale v0", nullptr));
        label_3->setText(QCoreApplication::translate("form_scope", "scale v2", nullptr));
        label_4->setText(QCoreApplication::translate("form_scope", " buffer size ", nullptr));
        label_5->setText(QCoreApplication::translate("form_scope", " range y min ", nullptr));
        label_2->setText(QCoreApplication::translate("form_scope", "scale v1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class form_scope: public Ui_form_scope {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_SCOPE_H
