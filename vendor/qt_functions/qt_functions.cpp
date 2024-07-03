#include "qt_functions.h"
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>
#include <fstream>
#include <sstream>
#include <string>

qt_functions::qt_functions()
{

}

std::string qt_functions::save_file_dialog_get_filename(QWidget* parent){

    QString fileName = QFileDialog::getSaveFileName(parent, QObject::tr("Save File"), "",
                                                    QObject::tr("Text Files (*.ngc);;G-code Files (*.txt)"));

    if (fileName.isEmpty()) {
        QMessageBox::warning(parent, QObject::tr("Error"), QObject::tr("Could not open file"));
    }

    // std::cout<<"filetext:"<<filetext<<std::endl;
    return fileName.toStdString();
}

std::string qt_functions::open_file_dialog_get_text(QWidget* parent){

    std::string filetext;
    QString fileName = QFileDialog::getOpenFileName(parent, QObject::tr("Open File"), "",
                                                    QObject::tr("Text Files (*.ngc);;G-code Files (*.txt)"));

    if (!fileName.isEmpty()) {
        std::ifstream file(fileName.toStdString());
        if (file) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            filetext = buffer.str();
        } else {
            QMessageBox::warning(parent, QObject::tr("Error"), QObject::tr("Could not open file"));
        }
    }

    // std::cout<<"filetext:"<<filetext<<std::endl;
    return filetext;

}

std::string qt_functions::open_file_dialog_get_filename(QWidget* parent){

    QString fileName = QFileDialog::getOpenFileName(parent, QObject::tr("Open File"), "",
                                                    QObject::tr("Text Files (*.ngc);;G-code Files (*.txt)"));

    if (fileName.isEmpty()) {
        QMessageBox::warning(parent, QObject::tr("Error"), QObject::tr("Could not open file"));
    }

    // std::cout<<"filetext:"<<filetext<<std::endl;
    return fileName.toStdString();
}

void qt_functions::message_box(QWidget *parent, double duration_ms, std::string message){
    // Create a message box
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setStyleSheet(parent->styleSheet());
    msgBox->setText(QString::fromStdString(message));

    // Create a timer to close the message box after 3 seconds
    QTimer::singleShot(duration_ms, msgBox, &QMessageBox::close);

    // Show the message box
    msgBox->exec();
}
