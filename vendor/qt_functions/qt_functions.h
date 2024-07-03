#ifndef QT_FUNCTIONS_H
#define QT_FUNCTIONS_H

#include <iostream>
#include <QWidget>

class qt_functions
{
public:
    qt_functions();

    static std::string save_file_dialog_get_filename(QWidget* parent);
    static std::string open_file_dialog_get_text(QWidget* parent);
    static std::string open_file_dialog_get_filename(QWidget* parent);
    static void message_box(QWidget *parent, double duration_ms, std::string message);
};

#endif // QT_FUNCTIONS_H
