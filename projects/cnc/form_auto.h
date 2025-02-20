#ifndef FORM_AUTO_H
#define FORM_AUTO_H

#include <QDialog>
#include "qt_functions.h"
#include "state_machine_shm.h"

class MainWindow;

namespace Ui {
class form_auto;
}

class form_auto : public QDialog
{
    Q_OBJECT

public:
    explicit form_auto(QWidget *parent = nullptr);
    ~form_auto();

    MainWindow *mainWindow; // Pointer to MainWindow

    void update(cnc_run_mode &run_mode,
                char (&file_name)[256],
                double &auto_speed_procent,
                int &run_from_line);
    void set_run_mode(cnc_run_mode run_mode);
    int load_file=0;
    double tooldir_fillet=0;
    int tangential_knife_override=0;
    double tangential_angle_x=0;
    double tangential_angle_y=0;

public slots:

    void on_toolButton_reload_pressed();

private slots:

    void on_toolButton_open_pressed();    

    void on_horizontalSlider_auto_velocity_procent_valueChanged(int value);

    void on_toolButton_run_pressed();

    void on_toolButton_pause_pressed();

    void on_toolButton_stop_pressed();

    void on_doubleSpinBox_tooldir_fillet_valueChanged(double arg1);

    void on_checkBox_tangential_override_toggled(bool checked);

    void on_doubleSpinBox_tool_angle_x_valueChanged(double arg1);

    void on_doubleSpinBox_tool_angle_y_valueChanged(double arg1);

private:

    Ui::form_auto *ui;
    std::string m_file_name;
    cnc_run_mode m_run_mode;
    gcode_limits m_gcode_limits;

};

#endif // FORM_AUTO_H
