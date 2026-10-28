import rclpy
from rclpy.node import Node
from controller_manager_msgs.srv import SwitchController


from std_msgs.msg import Bool


class EnableControllers(Node):

    def __init__(self):
        super().__init__('controller_enabler')
        self.subscription = self.create_subscription(
            Bool,
            'teleop/enable',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

        self.client = self.create_client(
                        SwitchController,
                        '/controller_manager/switch_controller'
                    )

    def listener_callback(self, msg):
        if msg.data:
            self.get_logger().info('Controllers enabled')
            if not self.client.wait_for_service(timeout_sec=5.0):
                self.get_logger().error('Controller manager unavailable')
            else:
                request = SwitchController.Request()
                request.deactivate_controllers = []
                request.activate_controllers = ['diff_drive_controller']
                request.strictness = SwitchController.Request.STRICT

                future = self.client.call_async(request)

                if future.result() is not None and future.result().ok:
                    self.get_logger().info('Controller activated')
                else:
                    self.get_logger().error('Failed to activate controller')
        else:
            self.get_logger().info('Controllers disabled')

            if not self.client.wait_for_service(timeout_sec=5.0):
                self.get_logger().error('Controller manager unavailable')
            else:
                request = SwitchController.Request()
                request.deactivate_controllers = ['diff_drive_controller']
                request.activate_controllers = []
                request.strictness = SwitchController.Request.STRICT

                future = self.client.call_async(request)

                if future.result() is not None and future.result().ok:
                    self.get_logger().info('Controller deactivated')
                else:
                    self.get_logger().error('Failed to deactivate controller')




def main(args=None):
    rclpy.init(args=args)

    controller_enabler = EnableControllers()

    rclpy.spin(controller_enabler)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    controller_enabler.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()