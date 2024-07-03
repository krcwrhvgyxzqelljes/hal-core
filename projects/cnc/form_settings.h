#ifndef FORM_SETTINGS_H
#define FORM_SETTINGS_H

#include <QDialog>

namespace Ui {
class form_settings;
}

class form_settings : public QDialog
{
    Q_OBJECT

public:
    explicit form_settings(QWidget *parent = nullptr);
    ~form_settings();

    void read_settings();
    void write_settings();
    void read_settings(double (&maxvel)[10],
                       double (&maxacc)[10],
                       double (&maxjer)[10],
                       double (&maxpos)[10],
                       double (&minpos)[10]);

private slots:
    void on_toolButton_save_pressed();

    void on_spinBox_axis_valueChanged(int arg1);

private:
    Ui::form_settings *ui;

    double m_maxvel[10];
    double m_maxacc[10];
    double m_maxjer[10];
    double m_maxpos[10];
    double m_minpos[10];
};

#endif // FORM_SETTINGS_H
