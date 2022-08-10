#include "mapping.h"
#include "ui_mapping.h"

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Setup Scatter plot properties
  ui->plot->addGraph();
  ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
  ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->plot->graph(0)->rescaleAxes();
  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  ui->plot->yAxis->setRange(0, 500);
  ui->plot->xAxis->setRange(-500, 500);

  nh_.reset(new ros::NodeHandle("~"));

  // setup the timer that will signal ros stuff to happen
  ros_timer = new QTimer(this);
  connect(ros_timer, SIGNAL(timeout()), this, SLOT(spinOnce()));
  ros_timer->start(100);  // set the rate to 100ms

  lidar_sub_ = nh_->subscribe("/map_lidar", 180, &MainWindow::lidarCallback, this);

}

MainWindow::~MainWindow()
{
  delete ui;
  delete ros_timer;
}

void MainWindow::spinOnce(){
  if(ros::ok()){
    plot();
    qv_x.clear();
    qv_y.clear();
    ros::spinOnce();
  }
  else
      QApplication::quit();
}

void MainWindow::lidarCallback(const mapping::mapping_vect& msg){
  for(int j=0; j<180; j++){
    qv_x.append((double)msg.map_vect[j]*cos(j*3.14/180));
    qv_y.append((double)msg.map_vect[j]*sin(j*3.14/180));

  }
}

void MainWindow::plot(){
  ui->plot->graph(0)->setData(qv_x, qv_y);
  ui->plot->replot();
  ui->plot->update();
}

