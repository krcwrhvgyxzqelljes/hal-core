#include "form_settings.h"
#include "ui_form_settings.h"
#include <QSettings>
#include <iostream>

form_settings::form_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_settings)
{
    ui->setupUi(this);
    read_settings();
    on_spinBox_axis_valueChanged(0);
}

form_settings::~form_settings()
{
    write_settings();
    delete ui;
}

void form_settings::on_toolButton_save_pressed()
{
    write_settings();
}

void form_settings::read_settings()
{
    std::cout<<"reading motion settings."<<std::endl;
    QSettings settings("cnc", "motion");

    for(uint i=0; i<10; i++){                                  // defaultvalue = 0.0
        m_maxvel[i]=settings.value("maxvel_"+QString::number(i), 0.0).toDouble();
    }
    for(uint i=0; i<10; i++){
        m_maxacc[i]=settings.value("maxacc_"+QString::number(i), 0.0).toDouble();
    }
    for(uint i=0; i<10; i++){
        m_maxjer[i]=settings.value("maxjerk_"+QString::number(i), 0.0).toDouble();
    }
    for(uint i=0; i<10; i++){
        m_maxpos[i]=settings.value("maxpos_"+QString::number(i), 0.0).toDouble();
    }
    for(uint i=0; i<10; i++){
        m_minpos[i]=settings.value("minpos_"+QString::number(i), 0.0).toDouble();
    }
}

void form_settings::write_settings()
{
    m_maxvel[ui->spinBox_axis->value()]=ui->lineEdit_max_vel->text().toDouble();
    m_maxacc[ui->spinBox_axis->value()]=ui->lineEdit_max_acc->text().toDouble();
    m_maxjer[ui->spinBox_axis->value()]=ui->lineEdit_max_jerk->text().toDouble();
    m_maxpos[ui->spinBox_axis->value()]=ui->lineEdit_max_pos->text().toDouble();
    m_minpos[ui->spinBox_axis->value()]=ui->lineEdit_min_pos->text().toDouble();

    std::cout<<"writing motion settings."<<std::endl;
    QSettings settings("cnc", "motion");

    for(uint i=0; i<10; i++){
        settings.setValue("maxvel_"+QString::number(i), m_maxvel[i]);
    }
    for(uint i=0; i<10; i++){
        settings.setValue("maxacc_"+QString::number(i), m_maxacc[i]);
    }
    for(uint i=0; i<10; i++){
        settings.setValue("maxjerk_"+QString::number(i), m_maxjer[i]);
    }
    for(uint i=0; i<10; i++){
        settings.setValue("maxpos_"+QString::number(i), m_maxpos[i]);
    }
    for(uint i=0; i<10; i++){
        settings.setValue("minpos_"+QString::number(i), m_minpos[i]);
    }
}

void form_settings::on_spinBox_axis_valueChanged(int arg1)
{
    ui->lineEdit_max_vel->setText(QString::number(m_maxvel[arg1],'f',3));
    ui->lineEdit_max_acc->setText(QString::number(m_maxacc[arg1],'f',3));
    ui->lineEdit_max_jerk->setText(QString::number(m_maxjer[arg1],'f',3));
    ui->lineEdit_max_pos->setText(QString::number(m_maxpos[arg1],'f',3));
    ui->lineEdit_min_pos->setText(QString::number(m_minpos[arg1],'f',3));
}

void form_settings::read_settings(double (&maxvel)[10],
                                        double (&maxacc)[10],
                                        double (&maxjer)[10],
                                        double (&maxpos)[10],
                                        double (&minpos)[10]){

    for (int i = 0; i < 10; ++i) {
        maxvel[i] = m_maxvel[i];
        maxacc[i] = m_maxacc[i];
        maxjer[i] = m_maxjer[i];
        maxpos[i] = m_maxpos[i];
        minpos[i] = m_minpos[i];
    }
}



