#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

/// Structure for defining a point using its x and y coordinates
struct point
{
    /// x-coordinate
    double x;
    /// y-coordinate
    double y;
};


namespace Ui {
class MainWindow;
}

/// Class to create GUI and handle events
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * Add a point from the GUI to the vectors.
     * @param x : x coordinate
     * @param y : y coordinate
    */
    void addPoint(double x, double y);

    /**
     * Clear the vectors that store the coordinates for the points.
    */
    void clearData();

    /**
     * Plot all the points in the GUI.
    */
    void plot();

    /**
     * Draw lines by connecting the points in the points vector serially
     * @param points : vector of points
    */
    void drawLines(std::vector<point> points);

    /**
     * Clear all the lines from the GUI.
    */
    void clearLines();

private slots:
    /**
     * Handles mouse click event
     * @param event : mouse event
    */
    void clickedGraph(QMouseEvent *event);

    void on_btn_triangulate_clicked();

    /**
     * Handles click event for Clear button.
    */
    void on_btn_clear_clicked();

private:
    /// GUI object
    Ui::MainWindow *ui;

    /// Vector of Points
    QVector<double> qv_x, qv_y;
};

#endif // MAINWINDOW_H
