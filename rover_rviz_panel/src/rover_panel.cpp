
#include "rover_rviz_panel/rover_panel.hpp"

#include <QVBoxLayout>
#include <rviz_common/display_context.hpp>
#include <pluginlib/class_list_macros.hpp>

namespace rover_rviz_panel
{

RoverPanel::RoverPanel(QWidget* parent)
  : rviz_common::Panel(parent)
{
  auto* layout = new QVBoxLayout(this);

  status_label_ = new QLabel("Teleoperation: Requested OFF");
  teleop_button_ = new QPushButton("Enable Teleoperation");

  layout->addWidget(status_label_);
  layout->addWidget(teleop_button_);
  layout->addStretch();

  connect(
    teleop_button_,
    &QPushButton::clicked,
    this,
    &RoverPanel::toggleTeleop
  );

  teleop_button_->setEnabled(false);
}

void RoverPanel::onInitialize()
{
  node_ptr_ = getDisplayContext()
                ->getRosNodeAbstraction()
                .lock();

  if (!node_ptr_) {
    status_label_->setText("ROS node unavailable");
    return;
  }

  auto node = node_ptr_->get_raw_node();

  teleop_pub_ = node->create_publisher<std_msgs::msg::Bool>(
    "/teleop/enable", 10
  );

  teleop_button_->setEnabled(true);
}

void RoverPanel::toggleTeleop()
{
  if (!teleop_pub_) {
    return;
  }

  teleop_enabled_ = !teleop_enabled_;

  std_msgs::msg::Bool msg;
  msg.data = teleop_enabled_;

  teleop_pub_->publish(msg);

  if (teleop_enabled_) {
    teleop_button_->setText("Disable Teleoperation");
    status_label_->setText("Teleoperation: Requested ON");
  } else {
    teleop_button_->setText("Enable Teleoperation");
    status_label_->setText("Teleoperation: Requested OFF");
  }
}

}  // namespace rover_rviz_panel

PLUGINLIB_EXPORT_CLASS(
  rover_rviz_panel::RoverPanel,
  rviz_common::Panel
)
