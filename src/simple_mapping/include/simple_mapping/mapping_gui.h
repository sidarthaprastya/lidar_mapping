#ifndef MAPPING_GUI_H
#define MAPPING_GUI_H

#include <QWidget>
#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>

namespace Ui {
class MappingGUI;
}

class MappingGUI : public QWidget
{
  Q_OBJECT

public:
  explicit MappingGUI(QWidget *parent = nullptr);
  ~MappingGUI();
  void chatterCallback(const std_msgs::String::ConstPtr& msg);

public slots:
  void spinOnce();

private:
  Ui::MappingGUI *ui;
  QTimer *ros_timer;

  ros::NodeHandlePtr nh_;
  ros::Subscriber lidar_sub_;
  ros::Publisher  start_pub_;
};

#endif // MAPPING_GUI_H
