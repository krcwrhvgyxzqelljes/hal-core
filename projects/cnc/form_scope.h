#ifndef FORM_SCOPE_H
#define FORM_SCOPE_H

#include <QDialog>
#include <qcustomplot.h>

namespace Ui {
class form_scope;
}

class form_scope : public QDialog
{
    Q_OBJECT

public:
    explicit form_scope(QWidget *parent = nullptr);
    ~form_scope();

    void update(double v0, double v1, double v2);

private slots:
    void update_plot();

private:
    Ui::form_scope *ui;

    // Our custom plot widget
    QCustomPlot * m_CustomPlot;
    // This object will hold the current value as a text
    // that will appear at the extreme right of the plot,
    QCPItemText *m_ValueIndex;

    // The time between each update, this
    // will be  used by the timer to call "updatePlot" slot
    qreal timeInterval;

    // Data buffers
    QVector<qreal> m_YData;
    QVector<qreal> m_YData1;
    QVector<qreal> m_YData2;
    QVector<qreal> m_XData;

    QTimer *timer;
    double m_time;

    qreal m_value;
    double m_v0, m_v1, m_v2;
    double m_scale_v0, m_scale_v1, m_scale_v2;
};

#endif // FORM_SCOPE_H
