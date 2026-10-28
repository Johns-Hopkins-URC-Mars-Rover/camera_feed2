
#ifndef ROVER_RVIZ_PANEL__ROVER_PANEL_HPP_
#define ROVER_RVIZ_PANEL__ROVER_PANEL_HPP_

#include <rviz_common/panel.hpp>
#include <rviz_common/ros_integration/ros_node_abstraction_iface.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <QPushButton>
#include <QLabel>
#include <memory>

namespace rover_rviz_panel
{

class RoverPanel : public rviz_common::Panel
{
  Q_OBJECT

public:
  explicit RoverPanel(QWidget* parent = nullptr);
  void onInitialize() override;

private:
  void toggleTeleop();

  std::shared_ptr<
      rviz_common::ros_integration::RosNodeAbstractionIface
  > node_ptr_;

  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr teleop_pub_;

  QPushButton* teleop_button_;
  QLabel* status_label_;

  bool teleop_enabled_ = false;
};

}  // namespace rover_rviz_panel

#endif
