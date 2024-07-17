#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes.
#include <QMainWindow>
#include "QFileDialog"
#include <QTimer>
#include "QMessageBox"
#include "QTextStream"

// Std c++ includes.
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <chrono>
#include <vector>

// Make conversion's easy:
#define toRadians M_PI/180.0
#define toDegrees (180.0/M_PI)

//#ifdef Success
//#undef Success
//#endif

// Opencascade occ.
#include "draw_primitives.h"
#include "draw_clothoids.h"
#include "draw_rs274ngc_shapes.h"
#include "OcctQtViewer.h"

// Scurve motion.
#include "scurve_engine.h"

// Opencascade occ widget overlay, ensure it's a created from qt->add_new->dialog_gui_class->widget.
#include "form_dro.h"
#include "form_jog.h"
#include "form_auto.h"
#include "form_scope.h"
#include "form_settings.h"

// Qt widget, gcode editor.
#include "QGCodeEditor.h"

// Linuxcnc hal, hardware abstract layer.
#include "hal_functions.h"

// File open dialog.
#include "qt_functions.h"
#include "std_functions.h"
#include "gcode_parser.h"

// Shared memory
#include "state_machine_shm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update();
    void hal_connection();

private slots:

    void on_toolButton_fit_all_pressed();

    void on_toolButton_view_front_pressed();

    void on_toolButton_view_back_pressed();

    void on_toolButton_view_top_pressed();

    void on_toolButton_view_bottom_pressed();

    void on_toolButton_view_left_pressed();

    void on_toolButton_view_right_pressed();

    void on_toolButton_view_3d_pressed();

    void on_toolButton_zoom_min_pressed();

    void on_toolButton_zoom_plus_pressed();

    void on_toolButton_view_ortho_toggled(bool checked);

    void on_toolButton_manual_pressed();

    void on_toolButton_auto_pressed();

    void on_toolButton_mdi_pressed();

    void on_toolButton_settings_toggled(bool checked);

    void on_toolButton_edit_pressed();

    void on_toolButton_text_edit_home_pressed();

    void on_toolButton_textedit_save_as_pressed();

    void on_toolButton_textedit_save_pressed();

    void on_toolButton_remove_line_nrs_pressed();

    void on_toolButton_to_capital_letters_pressed();

    void on_toolButton_to_lower_letters_pressed();

    void on_toolButton_scope_toggled(bool checked);

    void on_toolButton_clear_toolpath_pressed();

    void on_toolButton_empty_2_pressed();

public:
    OcctQtViewer *occ;
    form_dro *dro = new form_dro();
    form_jog *jog = new form_jog();
    form_auto *aut = new form_auto();
    form_scope *scope = new form_scope();
    form_settings *settings = new form_settings();
    hal_functions *hal = new hal_functions();
    QGCodeEditor *editor;
    state_machine_shm *shm = new state_machine_shm();
    shared_mem_data shm_data;
    Ui::MainWindow *ui;
    cnc_state_mode mode;

    QTimer *timer = new QTimer(this);
};
#endif
