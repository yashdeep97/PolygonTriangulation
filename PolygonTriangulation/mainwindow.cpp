#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Algorithm/monotone.h"
#include "Algorithm/triangulate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");

    ui->plot->xAxis->setRange(0,100);
    ui->plot->yAxis->setRange(0,100);

    ui->plot->replot();

    // Add points on mouse click
    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(qv_x, qv_y);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::drawLines(std::vector<point> points)
{
    QCPItemLine *line;
    for(unsigned int i = 0; i < (points.size() - 1); i++){
        line= new QCPItemLine(ui->plot);
        line->start->setCoords(points[i].x, points[i].y);
        line->end->setCoords(points[i+1].x, points[i+1].y);
        ui->plot->addItem(line);
    }
    plot();
}

void MainWindow::clearLines()
{
    ui->plot->clearItems();
    plot();
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event->pos();
    addPoint(ui->plot->xAxis->pixelToCoord(point.x()), ui->plot->yAxis->pixelToCoord(point.y()));
    plot();
}

void MainWindow::on_btn_triangulate_clicked()
{
    std::vector<point> polygon;
    for(int i = 0; i < qv_x.size(); i++){
        point p;
        p.x = qv_x[i];
        p.y = qv_y[i];
        polygon.push_back(p);
    }
    // push first point again.
    point p;
    p.x = qv_x[0];
    p.y = qv_y[0];
    polygon.push_back(p);

    drawLines(polygon);
    polygon.pop_back();

    getPolygon(polygon);
    split_into_monotone(this);
    Triangulate::triangulate();

}

void MainWindow::on_btn_clear_clicked()
{
    clearData();
    clearLines();
    plot();
}
