#ifndef FORM_JOG_H
#define FORM_JOG_H

#include <QDialog>

namespace Ui {
class form_jog;
}

class form_jog : public QDialog
{
    Q_OBJECT

public:
    explicit form_jog(QWidget *parent = nullptr);
    ~form_jog();

    void update(int *jog_array,
                int *jog_to_zero_array,
                double &jog_speed_procent,
                int &jog_step_enable,
                double &jog_step_size);

private slots:
    void on_toolButton_jog_x_min_pressed();

    void on_toolButton_jog_x_min_released();

    void on_toolButton_jog_x_plus_pressed();

    void on_toolButton_jog_x_plus_released();

    void on_toolButton_jog_y_min_pressed();

    void on_toolButton_jog_y_min_released();

    void on_toolButton_jog_y_plus_pressed();

    void on_toolButton_jog_y_plus_released();

    void on_toolButton_jog_z_min_pressed();

    void on_toolButton_jog_z_min_released();

    void on_toolButton_jog_z_plus_pressed();

    void on_toolButton_jog_z_plus_released();

    void on_toolButton_jog_a_min_pressed();

    void on_toolButton_jog_a_min_released();

    void on_toolButton_jog_a_plus_pressed();

    void on_toolButton_jog_a_plus_released();

    void on_toolButton_jog_b_min_pressed();

    void on_toolButton_jog_b_min_released();

    void on_toolButton_jog_b_plus_pressed();

    void on_toolButton_jog_b_plus_released();

    void on_toolButton_jog_c_min_pressed();

    void on_toolButton_jog_c_min_released();

    void on_toolButton_jog_c_plus_pressed();

    void on_toolButton_jog_c_plus_released();

    void on_toolButton_jog_u_min_pressed();

    void on_toolButton_jog_u_min_released();

    void on_toolButton_jog_u_plus_pressed();

    void on_toolButton_jog_u_plus_released();

    void on_toolButton_jog_v_min_pressed();

    void on_toolButton_jog_v_min_released();

    void on_toolButton_jog_v_plus_pressed();

    void on_toolButton_jog_v_plus_released();

    void on_toolButton_jog_w_min_pressed();

    void on_toolButton_jog_w_min_released();

    void on_toolButton_jog_w_plus_pressed();

    void on_toolButton_jog_w_plus_released();

    void on_doubleSpinBox_stepsize_valueChanged(double arg1);

    void on_toolButton_jog_step_toggled(bool checked);

    void on_horizontalSlider_jog_velocity_procent_sliderMoved(int position);

    void on_toolButton_jog_goto_zero_xyz_pressed();

    void on_toolButton_jog_goto_zero_xyz_released();

    void on_toolButton_jog_goto_zero_abc_pressed();

    void on_toolButton_jog_goto_zero_abc_released();

    void on_toolButton_jog_goto_zero_uvw_pressed();

    void on_toolButton_jog_goto_zero_uvw_released();

private:
    Ui::form_jog *ui;

    int m_jog[9]={0,0,0,0,0,0,0,0,0}; // -1 is negative jog, 0 is jog stop, 1 is jog positive.
    double m_jog_speed_procent=0;
    int m_jog_step_enable=0;
    double m_jog_step_size=0;
    int m_jog_to_zero[9]={0,0,0,0,0,0,0,0,0};

};

#endif // FORM_JOG_H
