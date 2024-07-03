#include "form_jog.h"
#include "ui_form_jog.h"

form_jog::form_jog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_jog)
{
    ui->setupUi(this);

    // Init values at startup.
    m_jog_speed_procent=ui->horizontalSlider_jog_velocity_procent->value();
    m_jog_step_enable=ui->toolButton_jog_step->isChecked();
    m_jog_step_size=ui->doubleSpinBox_stepsize->value();
}

form_jog::~form_jog()
{
    delete ui;
}

void form_jog::update(int *jog_array, int *jog_to_zero_array, double &jog_speed_procent, int &jog_step_enable, double &jog_step_size){
    for(uint i=0; i<9; i++){
        jog_array[i]=m_jog[i];
    }
    for(uint i=0; i<9; i++){
        jog_to_zero_array[i]=m_jog_to_zero[i];
    }
    jog_speed_procent=m_jog_speed_procent;
    jog_step_enable=m_jog_step_enable;
    jog_step_size=m_jog_step_size;

    ui->label_jog_velocity_procent->setText(QString::number(jog_speed_procent));
}

void form_jog::on_toolButton_jog_x_min_pressed()
{
    m_jog[0]=-1;
}

void form_jog::on_toolButton_jog_x_min_released()
{
    m_jog[0]=0;
}

void form_jog::on_toolButton_jog_x_plus_pressed()
{
    m_jog[0]=1;
}

void form_jog::on_toolButton_jog_x_plus_released()
{
    m_jog[0]=0;
}

void form_jog::on_toolButton_jog_y_min_pressed()
{
    m_jog[1]=-1;
}

void form_jog::on_toolButton_jog_y_min_released()
{
    m_jog[1]=0;
}

void form_jog::on_toolButton_jog_y_plus_pressed()
{
    m_jog[1]=1;
}

void form_jog::on_toolButton_jog_y_plus_released()
{
    m_jog[1]=0;
}

void form_jog::on_toolButton_jog_z_min_pressed()
{
    m_jog[2]=-1;
}

void form_jog::on_toolButton_jog_z_min_released()
{
    m_jog[2]=0;
}

void form_jog::on_toolButton_jog_z_plus_pressed()
{
    m_jog[2]=1;
}

void form_jog::on_toolButton_jog_z_plus_released()
{
    m_jog[2]=0;
}

void form_jog::on_toolButton_jog_a_min_pressed()
{
    m_jog[3]=-1;
}

void form_jog::on_toolButton_jog_a_min_released()
{
    m_jog[3]=0;
}

void form_jog::on_toolButton_jog_a_plus_pressed()
{
    m_jog[3]=1;
}

void form_jog::on_toolButton_jog_a_plus_released()
{
    m_jog[3]=0;
}

void form_jog::on_toolButton_jog_b_min_pressed()
{
    m_jog[4]=-1;
}

void form_jog::on_toolButton_jog_b_min_released()
{
    m_jog[4]=0;
}

void form_jog::on_toolButton_jog_b_plus_pressed()
{
    m_jog[4]=1;
}

void form_jog::on_toolButton_jog_b_plus_released()
{
    m_jog[4]=0;
}

void form_jog::on_toolButton_jog_c_min_pressed()
{
    m_jog[5]=-1;
}

void form_jog::on_toolButton_jog_c_min_released()
{
    m_jog[5]=0;
}

void form_jog::on_toolButton_jog_c_plus_pressed()
{
    m_jog[5]=1;
}

void form_jog::on_toolButton_jog_c_plus_released()
{
    m_jog[5]=0;
}

void form_jog::on_toolButton_jog_u_min_pressed()
{
    m_jog[6]=-1;
}

void form_jog::on_toolButton_jog_u_min_released()
{
    m_jog[6]=0;
}

void form_jog::on_toolButton_jog_u_plus_pressed()
{
    m_jog[6]=1;
}

void form_jog::on_toolButton_jog_u_plus_released()
{
    m_jog[6]=0;
}

void form_jog::on_toolButton_jog_v_min_pressed()
{
    m_jog[7]=-1;
}

void form_jog::on_toolButton_jog_v_min_released()
{
    m_jog[7]=0;
}

void form_jog::on_toolButton_jog_v_plus_pressed()
{
    m_jog[7]=1;
}

void form_jog::on_toolButton_jog_v_plus_released()
{
    m_jog[7]=0;
}

void form_jog::on_toolButton_jog_w_min_pressed()
{
    m_jog[8]=-1;
}

void form_jog::on_toolButton_jog_w_min_released()
{
    m_jog[8]=0;
}

void form_jog::on_toolButton_jog_w_plus_pressed()
{
    m_jog[8]=1;
}

void form_jog::on_toolButton_jog_w_plus_released()
{
    m_jog[8]=0;
}

void form_jog::on_doubleSpinBox_stepsize_valueChanged(double arg1)
{
    m_jog_step_size=arg1;
}

void form_jog::on_toolButton_jog_step_toggled(bool checked)
{
    m_jog_step_enable=checked;
}

void form_jog::on_horizontalSlider_jog_velocity_procent_sliderMoved(int position)
{
    m_jog_speed_procent=position;
}

void form_jog::on_toolButton_jog_goto_zero_xyz_pressed()
{
    m_jog_to_zero[0]=1;
    m_jog_to_zero[1]=1;
    m_jog_to_zero[2]=1;
}

void form_jog::on_toolButton_jog_goto_zero_xyz_released()
{
    m_jog_to_zero[0]=0;
    m_jog_to_zero[1]=0;
    m_jog_to_zero[2]=0;
}

void form_jog::on_toolButton_jog_goto_zero_abc_pressed()
{
    m_jog_to_zero[3]=1;
    m_jog_to_zero[4]=1;
    m_jog_to_zero[5]=1;
}

void form_jog::on_toolButton_jog_goto_zero_abc_released()
{
    m_jog_to_zero[3]=0;
    m_jog_to_zero[4]=0;
    m_jog_to_zero[5]=0;
}

void form_jog::on_toolButton_jog_goto_zero_uvw_pressed()
{
    m_jog_to_zero[6]=1;
    m_jog_to_zero[7]=1;
    m_jog_to_zero[8]=1;
}

void form_jog::on_toolButton_jog_goto_zero_uvw_released()
{
    m_jog_to_zero[6]=0;
    m_jog_to_zero[7]=0;
    m_jog_to_zero[8]=0;
}


