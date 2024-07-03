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

private slots:

    void on_toolButton_open_pressed();

    void on_toolButton_reload_pressed();

    void on_horizontalSlider_auto_velocity_procent_valueChanged(int value);

    void on_toolButton_run_pressed();

    void on_toolButton_pause_pressed();

    void on_toolButton_stop_pressed();

private:

    Ui::form_auto *ui;
    std::string m_file_name;
    cnc_run_mode m_run_mode;
};

#endif // FORM_AUTO_H
