#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "string"

// Todo tool offsets.
// Jog to zero.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // occ = new Opencascade();
    occ = new  OcctQtViewer();
    occ->set_perspective();

    //! Add gridlayout on top of the occ widget.
    QGridLayout *layout=new QGridLayout(occ);

    //! Add the controls into the occ gridlayout..
    layout->addWidget(dro);

    ui->gridLayout_page_manual->addWidget(jog);

    aut->mainWindow=this; // Set the reference pointer.
    ui->gridLayout_auto->addWidget(aut);

    ui->gridLayout_settings->addWidget(settings);

    ui->gridLayout_scope->addWidget(scope);

    ui->gridLayout_occ->addWidget(occ);
    occ->create_tp_cone(5,15);

    editor = new QGCodeEditor();
    ui->gridLayout_gcode->addWidget(editor);
    editor->setStyleSheet("background-color: rgb(75, 75, 75);");

    ui->stackedWidget_toplevel->setCurrentIndex(1);

    //! This activates a screen update when robot is moving and screen needs to be updated automaticly.
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(20);

    clothoid_test();

}

MainWindow::~MainWindow()
{
    hal->exit();
    shm->detach_shared_memory();
    delete ui;
}

#include <GeomAPI_Interpolate.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <gp_Pnt.hxx>
#include <Precision.hxx>
#include <iostream>

// Function to interpolate between points with a B-spline curve
Handle(Geom_BSplineCurve) interpolatePoints(const std::vector<gp_Pnt>& points, bool periodicFlag, double tolerance) {
    // Create handle to array of points
    Handle(TColgp_HArray1OfPnt) arrayPoints = new TColgp_HArray1OfPnt(1, static_cast<Standard_Integer>(points.size()));
    for (size_t i = 0; i < points.size(); ++i) {
        arrayPoints->SetValue(i + 1, points[i]);
    }

    // Create GeomAPI_Interpolate object
    GeomAPI_Interpolate interpolator(arrayPoints, periodicFlag, tolerance);

    // Perform interpolation
    interpolator.Perform();

    // Check if interpolation was successful
    if (!interpolator.IsDone()) {
        std::cerr << "Failed to interpolate points." << std::endl;
        return nullptr;
    }

    // Retrieve the interpolated B-spline curve
    Handle(Geom_BSplineCurve) splineCurve = interpolator.Curve();
    return splineCurve;
}

#include <BRepBuilderAPI_MakeEdge.hxx>

void MainWindow::clothoid_test(){

    occ->clear_shapevec();

    // Draw first line.
    gp_Pnt p0={10,10,0};
    gp_Pnt p2={20,20,0};
    gp_Pnt p1=draw_primitives::get_line_midpoint(p0,p2);
    occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line(p0,p2),Quantity_NOC_ALICEBLUE,0));

    // Draw second line.
    gp_Pnt p3={ui->spinBox_l0_x->value(),ui->spinBox_l0_y->value(),ui->spinBox_l0_z->value()};
    gp_Pnt p5={ui->spinBox_l1_x->value(),ui->spinBox_l1_y->value(),ui->spinBox_l1_z->value()};
    gp_Pnt p4=draw_primitives::get_line_midpoint(p3,p5);
    occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line(p3,p5),Quantity_NOC_ALICEBLUE,0));

    // Construct 3d clothoid.
    // pvec0 = projection on xy plane.
    // pvec1 = projection on xz plane.
    // pvec2 = projection 3d.
    int segments=100;
    std::vector<gp_Pnt> pvec0,pvec1,pvec2,pvec3;
    draw_clothoids::draw_inbetween_3d_clothoid_3arc_G2_non_planar(p0,p1,p2,p3,p4,p5,segments,pvec0,pvec1,pvec2,pvec3);
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec0));
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec1));
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec2));
    occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage(pvec3));

    // draw boundairy box.
    double xmin=-INFINITY,xmax=INFINITY;
    double ymin=-INFINITY,ymax=INFINITY;
    double zmin=-INFINITY,zmax=INFINITY;

    for(uint i=0; i<pvec0.size(); i++){
        if(pvec0[i].X()>xmin){
            xmin=pvec0[i].X();
        }
        if(pvec0[i].X()<xmax){
            xmax=pvec0[i].X();
        }
        if(pvec0[i].Y()>ymin){
            ymin=pvec0[i].Y();
        }
        if(pvec0[i].Y()<ymax){
            ymax=pvec0[i].Y();
        }
    }
    for(uint i=0; i<pvec1.size(); i++){
        if(pvec1[i].Z()>zmin){
            zmin=pvec1[i].Z();
        }
        if(pvec1[i].Z()<zmax){
            zmax=pvec1[i].Z();
        }
    }

    Handle(AIS_Shape) aShape=draw_primitives::draw_3d_box(xmax-xmin,ymax-ymin,zmax-zmin);
    aShape=draw_primitives::translate_3d(aShape,{0,0,0},{xmin,ymin,zmin});
    aShape=draw_primitives::colorize(aShape,Quantity_NOC_ALICEBLUE,0.95);
    occ->add_shapevec( aShape );

    // Interpolate the points with a B-spline curve

    gp_Pnt pi0, pi1;
    draw_primitives::interpolate_point_on_line(p0,p2,0.95,pi0);
    draw_primitives::interpolate_point_on_line(p3,p5,0.05,pi1);

    occ->add_shapevec( draw_primitives::draw_3d_point(pvec3[int(pvec3.size()*0.5)]) );


    Handle(Geom_BSplineCurve) spline = interpolatePoints({pi0, p2, p3, pi1}, false, Precision::Approximation());

    // Create an edge from the B-spline curve
    BRepBuilderAPI_MakeEdge edgeMaker(spline);
    TopoDS_Edge edge = edgeMaker.Edge();



    // Create an AIS_Shape for the edge
    Handle(AIS_Shape) aisShape = new AIS_Shape(edge);

    // Setup the AIS_Shape (optional)
    aisShape->SetColor(Quantity_NOC_GREEN); // Set color to red

    // Add the shape to the interactive context (occ is your AIS_InteractiveContext)
    occ->add_shapevec( aisShape);

}

void MainWindow::update(){

    shm_data=shm->read_from_shared_memory();

    shm_data.state_mode=mode;

    double maxvel[10];
    double maxacc[10];
    double maxjer[10];
    double maxpos[10];
    double minpos[10];
    settings->read_settings(maxvel,maxacc,maxjer,maxpos,minpos);

    for(uint i=0; i<10; i++){

        if(shm_data.state_mode==MANUAL){ // Apply jog procent speed.
            shm_data.scd[i].maxvel=maxvel[i]*(shm_data.jog_speed_procent/100);
        } else {
            shm_data.scd[i].maxvel=maxvel[i]*(abs(shm_data.auto_speed_procent)/100);
        }

        shm_data.scd[i].maxacc=maxacc[i];
        shm_data.scd[i].jermax=maxjer[i];
        shm_data.scd[i].maxpos=maxpos[i];
        shm_data.scd[i].minpos=minpos[i];
        shm_data.scd[i].intval=0.001;
    }

    // std::cout<<"gui mode realtime."<<std::endl;
    dro->update_dro(shm_data.pos,
                    shm_data.dtg,
                    shm_data.homed,
                    shm_data.curvel,
                    shm_data.halruntime);

    if(shm_data.state_mode==MANUAL){
        jog->update(shm_data.jog,
                    shm_data.jog_to_zero,
                    shm_data.jog_speed_procent,
                    shm_data.jog_step_enable,
                    shm_data.jog_step_size);

        aut->set_run_mode(cnc_run_mode::STOP);
        aut->load_file=1;
    }
    if(shm_data.state_mode==MDI){

    }
    if(shm_data.state_mode==AUTO){
        aut->update(shm_data.run_mode,
                    shm_data.file_name,
                    shm_data.auto_speed_procent,
                    shm_data.run_from_line);

        shm_data.load_file=aut->load_file;
        aut->load_file=0; // Reset;

        if(shm_data.run_mode!=STOP){ // Enable scroll in gcode editor when stopped.
            editor->highlightLine(shm_data.gcode_line);
        }
    }

    // Update scope.
    scope->update(shm_data.curvel,shm_data.curacc,shm_data.curpos);

    hal->update();

    shm->write_to_shared_memory(shm_data);

    occ->translate_tp_cone(shm_data.pos[0],
            shm_data.pos[1],
            shm_data.pos[2],
            shm_data.pos[3],
            shm_data.pos[4],
            shm_data.pos[5]);

    double tollerance=0.1;
    occ->update_toolpath({shm_data.pos[0],shm_data.pos[1],shm_data.pos[2]},tollerance);
    occ->update_tooldir(occ->get_tooldir_pnt(),tollerance);

    occ->redraw();
}

void MainWindow::on_toolButton_fit_all_pressed()
{
    occ->fit_all();
}

void MainWindow::on_toolButton_view_front_pressed()
{
    occ->set_view_front();
}

void MainWindow::on_toolButton_view_back_pressed()
{
    occ->set_view_back();
}

void MainWindow::on_toolButton_view_top_pressed()
{
    occ->set_view_top();
}

void MainWindow::on_toolButton_view_bottom_pressed()
{
    occ->set_view_bottom();
}

void MainWindow::on_toolButton_view_left_pressed()
{
    occ->set_view_left();
}

void MainWindow::on_toolButton_view_right_pressed()
{
    occ->set_view_right();
}

void MainWindow::on_toolButton_view_3d_pressed()
{
    occ->set_view_3d();
}

void MainWindow::on_toolButton_zoom_min_pressed()
{
    occ->zoom_min();
}

void MainWindow::on_toolButton_zoom_plus_pressed()
{
    occ->zoom_plus();
}

void MainWindow::on_toolButton_view_ortho_toggled(bool checked)
{
    if(checked){
        occ->set_orthographic();
    } else {
        occ->set_perspective();
    }
}

void MainWindow::on_toolButton_manual_pressed()
{
    ui->stackedWidget_mode_manual_auto_mdi->show();
    ui->toolButton_auto->setChecked(0);
    ui->toolButton_mdi->setChecked(0);
    ui->toolButton_settings->setChecked(0);
    ui->toolButton_manual->setDown(1);
    ui->stackedWidget_mode_manual_auto_mdi->setCurrentIndex(0);
    mode=MANUAL;
}


void MainWindow::on_toolButton_auto_pressed()
{
    ui->stackedWidget_mode_manual_auto_mdi->show();
    ui->toolButton_auto->setDown(1);
    ui->toolButton_manual->setChecked(0);
    ui->toolButton_mdi->setChecked(0);
    ui->toolButton_settings->setChecked(0);
    ui->stackedWidget_mode_manual_auto_mdi->setCurrentIndex(1);
    mode=AUTO;
}


void MainWindow::on_toolButton_mdi_pressed()
{
    ui->stackedWidget_mode_manual_auto_mdi->show();
    ui->toolButton_auto->setChecked(0);
    ui->toolButton_manual->setChecked(0);
    ui->toolButton_mdi->setDown(1);
    ui->toolButton_settings->setChecked(0);
    ui->stackedWidget_mode_manual_auto_mdi->setCurrentIndex(2);
    mode=MDI;
}

void MainWindow::on_toolButton_settings_toggled(bool checked)
{
    if(checked){
        ui->stackedWidget_mode_manual_auto_mdi->hide();
        ui->stackedWidget_main->setCurrentIndex(1);
    } else {
        ui->stackedWidget_mode_manual_auto_mdi->show();
        ui->stackedWidget_main->setCurrentIndex(0);
    }
}

void MainWindow::on_toolButton_edit_pressed()
{
    ui->stackedWidget_toplevel->setCurrentIndex(2);
    ui->plainTextEdit_gcode->setPlainText(editor->toPlainText());
}

void MainWindow::on_toolButton_text_edit_home_pressed()
{
    ui->stackedWidget_toplevel->setCurrentIndex(1);
}

void MainWindow::on_toolButton_textedit_save_as_pressed()
{
    std::string file_path=qt_functions::save_file_dialog_get_filename(this);
    std_functions::save_string_to_file(ui->plainTextEdit_gcode->toPlainText().toStdString(),file_path);
}

void MainWindow::on_toolButton_textedit_save_pressed()
{
    std::string file_name=ui->label_current_file->text().toStdString();
    std_functions::save_string_to_file(ui->plainTextEdit_gcode->toPlainText().toStdString(),file_name);
}


void MainWindow::on_toolButton_remove_line_nrs_pressed()
{
    std::string string=ui->plainTextEdit_gcode->toPlainText().toStdString();
    string=std_functions::remove_line_nummers_n_and_value(string);
    string=std_functions::remove_left_white_spaces_lines(string);
    ui->plainTextEdit_gcode->setPlainText(QString::fromStdString(string));
}

void MainWindow::on_toolButton_to_capital_letters_pressed()
{
    std::string string=ui->plainTextEdit_gcode->toPlainText().toStdString();
    string=std_functions::to_capical(string);
    ui->plainTextEdit_gcode->setPlainText(QString::fromStdString(string));
}


void MainWindow::on_toolButton_to_lower_letters_pressed()
{
    std::string string=ui->plainTextEdit_gcode->toPlainText().toStdString();
    string=std_functions::to_lower(string);
    ui->plainTextEdit_gcode->setPlainText(QString::fromStdString(string));
}

void MainWindow::on_toolButton_scope_toggled(bool checked)
{
    if(checked){
        ui->stackedWidget_mode_manual_auto_mdi->setCurrentIndex(3);
    } else {

        if(mode==MANUAL){
            ui->stackedWidget_mode_manual_auto_mdi->setCurrentIndex(0);
        }
        if(mode==AUTO){
            ui->stackedWidget_mode_manual_auto_mdi->setCurrentIndex(1);
        }
        if(mode==MDI){
            ui->stackedWidget_mode_manual_auto_mdi->setCurrentIndex(2);
        }
    }
}

void MainWindow::on_toolButton_clear_toolpath_pressed()
{
    occ->clear_toolpath();
}

void MainWindow::on_spinBox_l0_x_valueChanged(int arg1)
{
    clothoid_test();
}

void MainWindow::on_spinBox_l0_y_valueChanged(int arg1)
{
    clothoid_test();
}

void MainWindow::on_spinBox_l0_z_valueChanged(int arg1)
{
    clothoid_test();
}

void MainWindow::on_spinBox_l1_x_valueChanged(int arg1)
{
    clothoid_test();
}

void MainWindow::on_spinBox_l1_y_valueChanged(int arg1)
{
    clothoid_test();
}

void MainWindow::on_spinBox_l1_z_valueChanged(int arg1)
{
    clothoid_test();
}

