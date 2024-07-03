#include "form_dro.h"
#include "ui_form_dro.h"

form_dro::form_dro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_dro)
{
    ui->setupUi(this);
}

form_dro::~form_dro()
{
    delete ui;
}

void form_dro::update_dro(double *dro, double *dro_dtg, int *homed, double vel, double time){

    ui->label_dro_x->setText(QString::number(dro[0],'f',3));
    ui->label_dro_y->setText(QString::number(dro[1],'f',3));
    ui->label_dro_z->setText(QString::number(dro[2],'f',3));

    ui->label_dro_a->setText(QString::number(dro[3],'f',3));
    ui->label_dro_b->setText(QString::number(dro[4],'f',3));
    ui->label_dro_c->setText(QString::number(dro[5],'f',3));

    ui->label_dro_u->setText(QString::number(dro[6],'f',3));
    ui->label_dro_v->setText(QString::number(dro[7],'f',3));
    ui->label_dro_w->setText(QString::number(dro[8],'f',3));

    ui->label_dro_dtg_x->setText(QString::number(dro_dtg[0],'f',3));
    ui->label_dro_dtg_y->setText(QString::number(dro_dtg[1],'f',3));
    ui->label_dro_dtg_z->setText(QString::number(dro_dtg[2],'f',3));

    ui->label_dro_dtg_a->setText(QString::number(dro_dtg[3],'f',3));
    ui->label_dro_dtg_b->setText(QString::number(dro_dtg[4],'f',3));
    ui->label_dro_dtg_c->setText(QString::number(dro_dtg[5],'f',3));

    ui->label_dro_dtg_u->setText(QString::number(dro_dtg[6],'f',3));
    ui->label_dro_dtg_v->setText(QString::number(dro_dtg[7],'f',3));
    ui->label_dro_dtg_w->setText(QString::number(dro_dtg[8],'f',3));

    ui->label_dro_vel->setText(QString::number(vel*60,'f',3));
    ui->label_dro_time->setText(QString::number(time,'f',3));

    if(homed[0]){
        ui->label_dro_uh_x->setText(QString("H"));
    } else {
        ui->label_dro_uh_x->setText(QString("UH"));
    }
    if(homed[1]){
        ui->label_dro_uh_y->setText(QString("H"));
    } else {
        ui->label_dro_uh_y->setText(QString("UH"));
    }
    if(homed[2]){
        ui->label_dro_uh_z->setText(QString("H"));
    } else {
        ui->label_dro_uh_z->setText(QString("UH"));
    }

    if(homed[3]){
        ui->label_dro_uh_a->setText(QString("H"));
    } else {
        ui->label_dro_uh_a->setText(QString("UH"));
    }
    if(homed[4]){
        ui->label_dro_uh_b->setText(QString("H"));
    } else {
        ui->label_dro_uh_b->setText(QString("UH"));
    }
    if(homed[5]){
        ui->label_dro_uh_c->setText(QString("H"));
    } else {
        ui->label_dro_uh_c->setText(QString("UH"));
    }

    if(homed[6]){
        ui->label_dro_uh_u->setText(QString("H"));
    } else {
        ui->label_dro_uh_u->setText(QString("UH"));
    }
    if(homed[7]){
        ui->label_dro_uh_v->setText(QString("H"));
    } else {
        ui->label_dro_uh_v->setText(QString("UH"));
    }
    if(homed[8]){
        ui->label_dro_uh_w->setText(QString("H"));
    } else {
        ui->label_dro_uh_w->setText(QString("UH"));
    }
}
















