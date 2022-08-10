#include <QApplication>
#include <QIcon>
#include "mapping.h"


int main(int argc, char *argv[])
{

  ros::init(argc, argv, "mapping_gui_node",ros::init_options::AnonymousName);
  QApplication a(argc, argv);

  MainWindow w;

  // set the window title as the node name
  w.setWindowTitle(QString::fromStdString(
                       ros::this_node::getName()));

  w.show();
  return a.exec();
}
