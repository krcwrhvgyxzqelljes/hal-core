#include "form_auto.h"
#include "ui_form_auto.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"

form_auto::form_auto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_auto)
{
    ui->setupUi(this);

    ui->label_auto_velocity_procent->setText(QString::number(ui->horizontalSlider_auto_velocity_procent->value(),'f',0));

    on_toolButton_stop_pressed();
}

form_auto::~form_auto()
{
    delete ui;
}

void form_auto::on_toolButton_open_pressed()
{
    mainWindow->occ->clear_shapevec();
    mainWindow->editor->clear();

    m_file_name=qt_functions().open_file_dialog_get_filename(this);

    if(m_file_name.size()>0){
        QString gcode=QString::fromStdString(std_functions().read_file_to_string(m_file_name));
        mainWindow->editor->appendPlainText(gcode);

        mainWindow->ui->label_current_file->setText(QString::fromStdString(m_file_name));

        std::vector<gcode_line> gvec;
        gcode_parser().tokenize(m_file_name,gvec,1);
        gcode_parser::process_limits(gvec,m_gcode_limits);

        // Draw the gcode limit box.
        Handle(AIS_Shape) aShape_box = draw_primitives::draw_3d_box(m_gcode_limits.xmax-m_gcode_limits.xmin,
                                                                    m_gcode_limits.ymax-m_gcode_limits.ymin,
                                                                    m_gcode_limits.zmax-m_gcode_limits.zmin);
        aShape_box=draw_primitives::translate_3d(aShape_box,{0,0,0},{m_gcode_limits.xmin,m_gcode_limits.ymin,m_gcode_limits.zmin});
        aShape_box=draw_primitives::colorize(aShape_box,Quantity_NOC_ANTIQUEWHITE,0.98);
        mainWindow->occ->add_shapevec( aShape_box );

        std::vector<shape> svec;
        gcode_parser().tokens_to_shapes(gvec, svec);

        // Code for 5 axis tooldir optimalisation.
        gcode_parser::optimize_tooldir_path(svec,tooldir_fillet); // Adds fillet value.
        int count=0;
        for (auto& i : svec) {
            mainWindow->occ->add_shapevec(i.aShape);
            if(count==0){
                mainWindow->occ->add_shapevec(i.aShape_tooldir_0);
            }
            mainWindow->occ->add_shapevec(i.aShape_tooldir_1);
            if (count % 2 == 0) {
                mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(i.pvec_final_tooldir_path), Quantity_NOC_DARKORCHID2,0) );
            } else {
                mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(i.pvec_final_tooldir_path), Quantity_NOC_CORAL3,0) );
            }
            count++;
        }
        svec.clear();
        load_file=1;
    }
}

void form_auto::on_toolButton_reload_pressed()
{
    m_file_name=mainWindow->ui->label_current_file->text().toStdString();

    if(m_file_name.size()>0){
        mainWindow->occ->clear_shapevec();
        mainWindow->editor->clear();

        QString gcode=QString::fromStdString(std_functions().read_file_to_string(m_file_name));
        mainWindow->editor->appendPlainText(gcode);

        std::vector<gcode_line> gvec;
        gcode_parser().tokenize(m_file_name,gvec,0);
        gcode_parser::process_limits(gvec,m_gcode_limits);

        // Draw the gcode limit box.
        Handle(AIS_Shape) aShape_box = draw_primitives::draw_3d_box(m_gcode_limits.xmax-m_gcode_limits.xmin,
                                                                    m_gcode_limits.ymax-m_gcode_limits.ymin,
                                                                    m_gcode_limits.zmax-m_gcode_limits.zmin);
        aShape_box=draw_primitives::translate_3d(aShape_box,{0,0,0},{m_gcode_limits.xmin,m_gcode_limits.ymin,m_gcode_limits.zmin});
        aShape_box=draw_primitives::colorize(aShape_box,Quantity_NOC_ANTIQUEWHITE,0.98);
        mainWindow->occ->add_shapevec( aShape_box );

        mainWindow->ui->label_current_file->setText(QString::fromStdString(m_file_name));

        std::vector<shape> svec;
        gcode_parser().tokens_to_shapes(gvec,svec);

        double fillet=ui->doubleSpinBox_tooldir_fillet->value();

        int first=0, last=0;
        for(uint i=0; i<svec.size(); i++){
            if ( (svec[i].g_id == 0 || svec[i].g_id == 1 || svec[i].g_id == 2 || svec[i].g_id == 3) && svec[i].lenght>0 ) {
                last=i;
            }
        }

        // Record tooldir path, trim tooldir path.
        int count=0;
        for (auto& i : svec) {
             mainWindow->occ->add_shapevec(i.aShape);
            // mainWindow->occ->add_shapevec(i.aShape_tooldir_1);

            // Recorded tooldir path preview.
            if ( (i.g_id == 0 || i.g_id == 1) && i.lenght>0 ) {
                std::vector<gp_Pnt> pvec = draw_primitives::record_tooldir_path_line(i.p0, i.p1, i.abc0, i.abc1, 15);
                i.pvec_tooldir_path = draw_primitives::trim_recorded_tooldir_path_line_both_sides( pvec, fillet);
                if(!first){
                    i.pvec_tooldir_path[0]=i.p0; // Don't trim the first gcode segment.
                    first=1;
                }
                if(count==last){
                    i.pvec_tooldir_path.back()=i.ta1; // Don't trim the last gcode segment.
                }
            }
            else if ( (i.g_id == 2 || i.g_id == 3) && i.lenght>0 ) {
                std::vector<gp_Pnt> pvec = draw_primitives::record_tooldir_path_arc(i.p0, i.pw, i.p1, i.abc0, i.abc1, 15);
                i.pvec_tooldir_path = draw_primitives::trim_recorded_tooldir_path_line_both_sides( pvec, fillet);
                if(!first){
                    i.pvec_tooldir_path[0]=i.p0;
                    first=1;
                }
                if(count==last){
                    i.pvec_tooldir_path.back()=i.ta1;
                }
            }
            if(i.pvec_tooldir_path.size()>0){ // Draw result.
                 mainWindow->occ->add_shapevec(draw_primitives::draw_3d_line_wire_low_memory_usage( i.pvec_tooldir_path) );
            }
            count++;
        }

        // Draw tooldir path fillets.
        int i=0, j=0;
        for (i = 0; i < svec.size() - 1; i++) {
            if(svec[i].lenght>0){
                for (j = i+1; j < svec.size(); j++) {
                    if(svec[j].lenght>0){

                        // Generate spline waypoints.
                        gp_Pnt p0 = svec[i].pvec_tooldir_path[svec[i].pvec_tooldir_path.size() - 2];
                        gp_Pnt p1 = svec[i].pvec_tooldir_path[svec[i].pvec_tooldir_path.size() - 1];
                        gp_Pnt p2;
                        double dist0=p0.Distance(p1);
                        draw_primitives::offset_3d_point_on_line(p0,p1,dist0+0.001,p2);

                        gp_Pnt p3 = svec[j].pvec_tooldir_path[0];
                        gp_Pnt p4 = svec[j].pvec_tooldir_path[1];
                        gp_Pnt p5;
                        double dist1=p3.Distance(p4);
                        draw_primitives::offset_3d_point_on_line(p4,p3,dist1+0.001,p5);

                        if(p1.Distance(p2)>0 && p5.Distance(p3)>0){
                            // For the spline fillets, store fist set of points in this gcode line, store second set of points in upfollowing gcode line.
                            int numPoints = 20;
                            for (int ii = 0; ii < numPoints; ++ii) {
                                // Calculate parameter corresponding to current point
                                double progress = static_cast<double>(ii) / (2 * (numPoints - 1));  // Adjusted for 0 to 0.5
                                // std::cout << "progress: " << progress << std::endl;
                                gp_Pnt pi;
                                draw_primitives::interpolate_point_on_spline_degree_3({p1, p2, p5, p3}, progress, pi);
                                svec[i].pvec_back_tooldir_path.push_back(pi);
                            }
                            for (int ii = 0; ii < numPoints; ++ii) {
                                // Calculate parameter corresponding to current point
                                double progress = 0.5 + static_cast<double>(ii) / (2 * (numPoints - 1));  // Adjusted for 0.5 to 1.0
                                // std::cout << "progress: " << progress << std::endl;
                                gp_Pnt pi;
                                draw_primitives::interpolate_point_on_spline_degree_3({p1, p2, p5, p3}, progress, pi);
                                svec[j].pvec_front_tooldir_path.push_back(pi);
                            }

                            mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_back_tooldir_path), Quantity_NOC_AZURE,0 ) );
                            mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[j].pvec_front_tooldir_path), Quantity_NOC_CYAN,0 ) );

                            gp_Pnt pi;
                            draw_primitives::interpolate_point_on_spline_degree_3({p1,p2,p5,p3},0.5,pi);

                            svec[i].aShape_tooldir_1=draw_primitives::draw_3d_line(pi,svec[i].p1);
                            svec[i].aShape_tooldir_1=draw_primitives::colorize( svec[i].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
                             mainWindow->occ->add_shapevec(svec[i].aShape_tooldir_1);

                        } else { // If spline fails, draw a line.
                            gp_Pnt p2=draw_primitives::get_line_midpoint(p1,p3);
                            svec[i].pvec_back_tooldir_path={p1,p2};
                            svec[j].pvec_front_tooldir_path={p2,p3};

                            mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_back_tooldir_path), Quantity_NOC_AZURE,0 ) );
                            mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[j].pvec_front_tooldir_path), Quantity_NOC_CYAN,0 ) );

                            svec[i].aShape_tooldir_1=draw_primitives::draw_3d_line( p2 ,svec[i].p1);
                            svec[i].aShape_tooldir_1=draw_primitives::colorize( svec[i].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
                            mainWindow->occ->add_shapevec(svec[i].aShape_tooldir_1);
                        }
                        break;
                    }
                }
            }
        }

        // Tooldir at program start.
        svec[0].aShape_tooldir_0=draw_primitives::draw_3d_line( svec[0].ta0 ,svec[0].p0);
        svec[0].aShape_tooldir_0=draw_primitives::colorize( svec[0].aShape_tooldir_0, Quantity_NOC_DODGERBLUE1,0 );
        // mainWindow->occ->add_shapevec(svec[0].aShape_tooldir_0);

        // Tooldir at program end.
        svec[svec.size()-1].aShape_tooldir_1=draw_primitives::draw_3d_line( svec[svec.size()-1].ta1 ,svec[svec.size()-1].p1);
        svec[svec.size()-1].aShape_tooldir_1=draw_primitives::colorize( svec[svec.size()-1].aShape_tooldir_1, Quantity_NOC_DODGERBLUE1,0 );
        // mainWindow->occ->add_shapevec(svec[svec.size()-1].aShape_tooldir_1);

        // Group final tooldir path to every gcode line. Also cleanup memory.
        for (uint i=0; i<svec.size(); i++) {
            svec[i].pvec_final_tooldir_path.clear();
            for (uint j=0; j<svec[i].pvec_front_tooldir_path.size(); j++) {
                svec[i].pvec_final_tooldir_path.push_back(svec[i].pvec_front_tooldir_path[j]);
            }
            for (uint j=0; j<svec[i].pvec_tooldir_path.size(); j++) {
                svec[i].pvec_final_tooldir_path.push_back(svec[i].pvec_tooldir_path[j]);
            }
            for (uint j=0; j<svec[i].pvec_back_tooldir_path.size(); j++) {
                svec[i].pvec_final_tooldir_path.push_back(svec[i].pvec_back_tooldir_path[j]);
            }

            svec[i].pvec_front_tooldir_path.clear();
            svec[i].pvec_tooldir_path.clear();
            svec[i].pvec_back_tooldir_path.clear();

            // Check if ii is even or odd. Show difference in color output to verify content.
            if (i % 2 == 0) {
                // mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_final_tooldir_path), Quantity_NOC_DARKORCHID2,0) );
            } else {
                // mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(svec[i].pvec_final_tooldir_path), Quantity_NOC_CORAL3,0) );
            }
        }

        // Calculate total lenghts for tooldir path.
        for (uint i=0; i<svec.size(); i++) {
            svec[i].tooldir_final_lenght=0; // Reset.

            if(svec[i].pvec_final_tooldir_path.size()>1){
                for (uint j=0; j<svec[i].pvec_final_tooldir_path.size()-1; j++) {
                    double l=svec[i].pvec_final_tooldir_path[j].Distance(svec[i].pvec_final_tooldir_path[j+1]);
                    svec[i].tooldir_final_lenght+=l;
                }
            }
        }

//        // Code for 5 axis tooldir optimalisation.
//        gcode_parser::optimize_tooldir_path(svec,tooldir_fillet); // Adds fillet value.
//        int count=0;
//        for (auto& i : svec) {
//            mainWindow->occ->add_shapevec(i.aShape);
//            if(count==0){
//                mainWindow->occ->add_shapevec(i.aShape_tooldir_0);
//            }
//            mainWindow->occ->add_shapevec(i.aShape_tooldir_1);
//            if (count % 2 == 0) {
//                mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(i.pvec_final_tooldir_path), Quantity_NOC_DARKORCHID2,0) );
//            } else {
//                mainWindow->occ->add_shapevec( draw_primitives::colorize( draw_primitives::draw_3d_line_wire_low_memory_usage(i.pvec_final_tooldir_path), Quantity_NOC_CORAL3,0) );
//            }
//            count++;
//        }
        svec.clear(); // Clean's memory. Opencascade has still the shapes. Kernel has it's own svec.
        load_file=1;
    }
}

void form_auto::update(cnc_run_mode &run_mode, char (&file_name)[256], double &auto_speed_procent, int &run_from_line)
{
    if(m_run_mode==RUN){

        std::string file_name=mainWindow->ui->label_current_file->text().toStdString();
        if(file_name.size()==0){
            qt_functions::message_box(this,2000,"no file.");
            on_toolButton_stop_pressed();
        } else {
            run_mode=RUN;
            run_from_line=ui->spinBox_run_from_line->value();
        }
    }
    if(m_run_mode==STOP){
        run_mode=STOP;
    }
    if(m_run_mode==PAUSE){
        run_mode=PAUSE;
    }

    std::strncpy(file_name, m_file_name.c_str(), sizeof(file_name) - 1);
    file_name[sizeof(file_name) - 1] = '\0'; // Ensure null-termination

    auto_speed_procent=ui->horizontalSlider_auto_velocity_procent->value();
}

void form_auto::set_run_mode(cnc_run_mode run_mode){

    m_run_mode=run_mode;
    if(m_run_mode==RUN){
        on_toolButton_run_pressed();
    }
    if(m_run_mode==PAUSE){
        on_toolButton_pause_pressed();
    }
    if(m_run_mode==STOP){
        on_toolButton_stop_pressed();
    }
}

void form_auto::on_horizontalSlider_auto_velocity_procent_valueChanged(int value)
{
    ui->label_auto_velocity_procent->setText(QString::number(ui->horizontalSlider_auto_velocity_procent->value(),'f',0));
}

void form_auto::on_toolButton_run_pressed()
{
    ui->toolButton_run->setIcon(QIcon(":/pictures/btn_25_25_in_green.png"));
    ui->toolButton_pause->setIcon(QIcon(":/pictures/btn_25_25.png"));
    ui->toolButton_stop->setIcon(QIcon(":/pictures/btn_25_25.png"));
    m_run_mode=RUN;
}

void form_auto::on_toolButton_pause_pressed()
{
    ui->toolButton_run->setIcon(QIcon(":/pictures/btn_25_25.png"));
    ui->toolButton_pause->setIcon(QIcon(":/pictures/btn_25_25_in_green.png"));
    ui->toolButton_stop->setIcon(QIcon(":/pictures/btn_25_25.png"));
    m_run_mode=PAUSE;
}

void form_auto::on_toolButton_stop_pressed()
{
    ui->toolButton_run->setIcon(QIcon(":/pictures/btn_25_25.png"));
    ui->toolButton_pause->setIcon(QIcon(":/pictures/btn_25_25.png"));
    ui->toolButton_stop->setIcon(QIcon(":/pictures/btn_25_25_in_green.png"));
    m_run_mode=STOP;
}

void form_auto::on_doubleSpinBox_tooldir_fillet_valueChanged(double arg1)
{
   tooldir_fillet=arg1;
   on_toolButton_reload_pressed(); // Reload the file to update tooldir fillets.
}

