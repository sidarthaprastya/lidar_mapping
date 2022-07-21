#ifndef MAPPING_H
#define MAPPING_H

#include <QWidget>
#include <QMainWindow>
#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>
#include <mapping/mapping_vect.h>
#include <QtMath>
#include <math.h>
//#include "qcustomplot.h"
//#include <QScatterSeries>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void lidarCallback(const mapping::mapping_vect& msg);
  void plot();


public slots:
  void spinOnce();

private:
  Ui::MainWindow *ui;
  QTimer *ros_timer;
  void addPoint(double x, double y);
  void clearData();
//  QScatt

  ros::NodeHandlePtr nh_;
  ros::Subscriber lidar_sub_;
  ros::Publisher  start_pub_;
  QVector<double> qv_x, qv_y;
//  double x_map[100];
//  double y_map[100];
};

#endif // MAPPING_GUI_H
