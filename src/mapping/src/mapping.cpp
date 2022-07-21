#include "mapping.h"
#include "ui_mapping.h"

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->plot->addGraph();
  ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
  ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->plot->graph(0)->rescaleAxes();
  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
//  ui->plot->yAxis->setRange(0, 300);
//  ui->plot->xAxis->setRange(-300, 300);

  nh_.reset(new ros::NodeHandle("~"));

  // setup the timer that will signal ros stuff to happen
  ros_timer = new QTimer(this);
  connect(ros_timer, SIGNAL(timeout()), this, SLOT(spinOnce()));
  ros_timer->start(100);  // set the rate to 100ms  You can change this if you want to increase/decrease update rate


  lidar_sub_ = nh_->subscribe("/map_lidar", 180, &MainWindow::lidarCallback, this);


//  // publish a message on the channel specified by ~/hello_topic param
//  std::string hello_topic;
//  nh_->param<std::string>("hello_topic",hello_topic,"chatter");
//  start_pub_ = nh_->advertise<std_msgs::String>(hello_topic,1);
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
//    qDebug()<<QString("%l").arg((float)msg.mapping[j]);

  }
  else
      QApplication::quit();
}


void MainWindow::lidarCallback(const mapping::mapping_vect& msg){
//  auto qstring_msg = QString::fromStdString( msg->data.c_str() );
  for(int j=0; j<180; j++){
    qv_x.append((double)msg.map_vect[j]*cos(j*3.14/180));
    qv_y.append((double)msg.map_vect[j]*sin(j*3.14/180));
//    qDebug()<<msg.mapping[j];
//    qDebug()<<sin(j);

  }

//  ui->chatter->setText(qstring_msg);
}

void MainWindow::plot(){
  ui->plot->graph(0)->setData(qv_x, qv_y);
  ui->plot->replot();
  ui->plot->update();
}

//void MappingGUI::on_hi_button_clicked()
//{
//  std_msgs::String msg;
//  std::stringstream ss;
//  ss << "hello world " << ui->hi_num->value();
//  msg.data = ss.str();

//  hello_pub_.publish(msg);

//  ui->hi_num->setValue(ui->hi_num->value()+1);
//}
