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
        if(!gcode_parser().tokenize(m_file_name,gvec,0)){
            std::cout<<"tokenize error."<<std::endl;
        } else {
            std::cout<<"tokenize ok."<<std::endl;
        }
        if(!gcode_parser::process_limits(gvec,m_gcode_limits)){
            std::cout<<"process limit error."<<std::endl;
        } else {
            std::cout<<"process limit ok."<<std::endl;
        }

        // Draw the gcode limit box.
        Handle(AIS_Shape) aShape_box = draw_primitives::draw_3d_box(m_gcode_limits.xmax-m_gcode_limits.xmin,
                                                                    m_gcode_limits.ymax-m_gcode_limits.ymin,
                                                                    m_gcode_limits.zmax-m_gcode_limits.zmin);
        aShape_box=draw_primitives::translate_3d(aShape_box,{0,0,0},{m_gcode_limits.xmin,m_gcode_limits.ymin,m_gcode_limits.zmin});
        aShape_box=draw_primitives::colorize(aShape_box,Quantity_NOC_ANTIQUEWHITE,0.98);
        mainWindow->occ->add_shapevec( aShape_box );

        std::vector<shape> svec;
        if(!gcode_parser().tokens_to_shapes(gvec,svec)){
            std::cout<<"tokens to shape error."<<std::endl;
        } else {
            std::cout<<"tokens to shape ok."<<std::endl; 
            for (auto& i : svec) {
                mainWindow->occ->add_shapevec(i.aShape);
            }
        }

        // Code for 5 axis tooldir optimalisation.
        std::vector<Handle(AIS_Shape)> aisvec;
        if(!gcode_parser::optimize_tooldir_path(svec,tooldir_fillet,aisvec)){  // Adds fillet value.
               std::cout<<"optimize tooldir path error."<<std::endl;
        } else {
            std::cout<<"optimize tooldir path ok."<<std::endl;
            for (auto& i : aisvec) {
                mainWindow->occ->add_shapevec(i);
            }
        }

        svec.clear(); // Clean up memory, the kernel has it's own svec.
        aisvec.clear();
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
        if(!gcode_parser().tokenize(m_file_name,gvec,0)){
            std::cout<<"tokenize error."<<std::endl;
        } else {
            std::cout<<"tokenize ok."<<std::endl;
        }
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
        if(!gcode_parser().tokens_to_shapes(gvec,svec)){
            std::cout<<"tokens to shape error."<<std::endl;
        } else {
            std::cout<<"tokens to shape ok."<<std::endl;
            for (auto& i : svec) {
                mainWindow->occ->add_shapevec(i.aShape);
            }
        }

        std::vector<Handle(AIS_Shape)> aisvec;
        if(!gcode_parser::optimize_tooldir_path(svec,tooldir_fillet,aisvec)){
            std::cout<<"optimize tooldir path error."<<std::endl;
        } else {
            std::cout<<"optimize tooldir path ok."<<std::endl;
            for (auto& i : aisvec) {
                mainWindow->occ->add_shapevec(i);
            }
        }

        svec.clear(); // Clean's memory. Opencascade has still the shapes. Kernel has it's own svec.
        aisvec.clear();;
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

void form_auto::on_checkBox_tangential_override_toggled(bool checked)
{
    if(checked){
        tangential_knife_override=1;
    } else {
        tangential_knife_override=0;
    }
}

void form_auto::on_doubleSpinBox_tool_angle_x_valueChanged(double arg1)
{
    tangential_angle_x=arg1;
}

void form_auto::on_doubleSpinBox_tool_angle_y_valueChanged(double arg1)
{
    tangential_angle_y=arg1;
}

