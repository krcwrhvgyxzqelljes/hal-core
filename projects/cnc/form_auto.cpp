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
        gcode_parser().tokenize(m_file_name,gvec,0);

        std::vector<shape> svec;
        gcode_parser().tokens_to_shapes(gvec, svec);
        for (const auto& i : svec) {
            mainWindow->occ->add_shapevec(i.aShape);
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

        mainWindow->ui->label_current_file->setText(QString::fromStdString(m_file_name));

        std::vector<shape> svec;
        gcode_parser().tokens_to_shapes(gvec,svec);
        for (const auto& i : svec) {
            mainWindow->occ->add_shapevec(i.aShape);
        }
        svec.clear();

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

