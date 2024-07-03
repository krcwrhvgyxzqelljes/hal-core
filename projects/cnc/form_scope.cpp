#include "form_scope.h"
#include "ui_form_scope.h"

form_scope::form_scope(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_scope)
{
    ui->setupUi(this);

    m_CustomPlot = new QCustomPlot(this);
    ui->gridLayout_scope_tp->addWidget(m_CustomPlot);

    // Set the background color to dark
    m_CustomPlot->setBackground(QColor(42, 42, 42));

    // Configure the axis background and grid colors
    m_CustomPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    m_CustomPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    m_CustomPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    m_CustomPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    m_CustomPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_CustomPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    m_CustomPlot->xAxis->setTickLabelColor(Qt::white);
    m_CustomPlot->yAxis->setTickLabelColor(Qt::white);
    m_CustomPlot->xAxis->setLabelColor(Qt::white);
    m_CustomPlot->yAxis->setLabelColor(Qt::white);
    m_CustomPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 1, Qt::DotLine));
    m_CustomPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 1, Qt::DotLine));
    m_CustomPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_CustomPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_CustomPlot->xAxis->grid()->setSubGridVisible(true);
    m_CustomPlot->yAxis->grid()->setSubGridVisible(true);
    m_CustomPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_CustomPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    m_CustomPlot->addGraph();
    m_CustomPlot->addGraph();
    m_CustomPlot->addGraph();

    // Tell the plot widget to display the x axis values as a time
    // instead of numbers
    m_CustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    // Set the x axis time string format
    m_CustomPlot->xAxis->setDateTimeFormat("");
    m_CustomPlot->xAxis->setAutoTickStep(true);
    m_CustomPlot->yAxis->setAutoTickStep(true);

    // Allocate memory for the text item that will display the current value as a text.
    m_ValueIndex = new QCPItemText(m_CustomPlot);
    // Set the font of the text item
    m_ValueIndex->setFont(QFont(font().family(), 8)); // make font a bit larger
    // Add the text item to the plot widget
    m_CustomPlot->addItem(m_ValueIndex);

    // Change the color of the graphs
    QColor brushClr = Qt::green;
    brushClr.setAlphaF(.5);
    m_CustomPlot->graph(0)->setBrush(brushClr);
    m_CustomPlot->graph(0)->setPen(QColor());

    QColor brushClr1 = Qt::yellow;
    brushClr1.setAlphaF(.5);
    m_CustomPlot->graph(1)->setBrush(brushClr1);
    m_CustomPlot->graph(1)->setPen(QColor());

    QColor brushClr2 = Qt::blue;
    brushClr2.setAlphaF(.5);
    m_CustomPlot->graph(2)->setBrush(brushClr2);
    m_CustomPlot->graph(2)->setPen(QColor());

    // Setup a timer and start it.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_plot()));
    timer->start(20);
}

form_scope::~form_scope()
{
    delete ui;
}

void form_scope::update(double v0, double v1, double v2){
    m_v0=v0;
    m_v1=v1;
    m_v2=v2;
}

void form_scope::update_plot() {
    // Increment time and append data
    m_time += 0.020;
    m_XData.append(m_time);

    m_YData.append(m_v0 * ui->doubleSpinBox_scale_v0->value());
    m_YData1.append(m_v1 * ui->doubleSpinBox_scale_v1->value());
    m_YData2.append(m_v2 * ui->doubleSpinBox_scale_v2->value());

    // Ensure data buffers size is under the limit specified by the user
    int bufferSize = ui->doubleSpinBox_bufsize->value();
    if (m_XData.size() > bufferSize) {
        m_XData.remove(0);
        m_YData.remove(0);
        m_YData1.remove(0);
        m_YData2.remove(0);
    }

    // Update graph data
    m_CustomPlot->graph(0)->setData(m_XData, m_YData);
    m_CustomPlot->graph(1)->setData(m_XData, m_YData2);
    m_CustomPlot->graph(2)->setData(m_XData, m_YData1);

    // Calculate the range for x and y axes
    double xMin = *std::min_element(m_XData.begin(), m_XData.end());
    double xMax = *std::max_element(m_XData.begin(), m_XData.end());

    /*
    double yMin = std::min({*std::min_element(m_YData.begin(), m_YData.end()),
                            *std::min_element(m_YData1.begin(), m_YData1.end()),
                            *std::min_element(m_YData2.begin(), m_YData2.end())});*/

    /*
    double yMax = std::max({*std::max_element(m_YData.begin(), m_YData.end()),
                            *std::max_element(m_YData1.begin(), m_YData1.end()),
                            *std::max_element(m_YData2.begin(), m_YData2.end())});*/

    double yMin=ui->doubleSpinBox_range_y_min->value();
    double yMax=ui->doubleSpinBox_range_y_max->value();

    // Set the ranges for the axes
    m_CustomPlot->xAxis->setRange(xMin, xMax);
    m_CustomPlot->yAxis->setRange(yMin, yMax);

    // Update the plot widget
    m_CustomPlot->replot();
}
