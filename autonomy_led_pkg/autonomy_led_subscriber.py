import rclpy
from rclpy.node import Node
import serial
from std_msgs.msg import String, Bool


class AutonomyLEDSubscriber(Node):

    def __init__(self):
        super().__init__('autonomy_led_subscriber')

        self.declare_parameter('drive_auto_param', 'is_autonomous')
        self.declare_parameter('auto_goal_param', 'goal_alert')
        self.declare_parameter('device_path', '/dev/ttyACM0')
        self.declare_parameter('topic_parameter', 'led_color_topic')
        self.declare_parameter('autonomous_parameter', 'autonomous')
        self.declare_parameter('teleop_parameter', 'teleop')
        self.declare_parameter('arrival_parameter', 'arrival')

        self.create_subscription(
            Bool,
            self.get_parameter('drive_auto_param').get_parameter_value().string_value,
            self.update_main,
            10
        )

        self.create_subscription(
            Bool,
            self.get_parameter('auto_goal_param').get_parameter_value().string_value,
            self.update_auto,
            10
        )

        #Chase's Led overide mode
        self.override_sub = self.create_subscription(
            String,
            '/led_mode_override',
            self.override_mode,
            10
        )
        # self.create_subscription(
        #     STargetedBool,
        #     'override_leds',
        #     self.override_mode,
        #     10)

        self.create_timer(
            0.1,
            self.update_loop
        )        
        
        self.is_autonomous = False
        self.is_goal = False
        self.override = False
        self.forced_mode = ""

    def update_loop(self):
        if self.override:
            self.send_mode(self.forced_mode)
            return #if in forced mode skip rest of loop.

        if not self.is_autonomous:
            self.send_mode('teleop')

        elif self.is_goal:
            self.send_mode('arrival')

        else:
            self.send_mode('autonomous')

    # Are we in drive or autonomy
    def update_main(self, bool_msg : Bool):
        self.is_autonomous = bool_msg.data

    # Are we in autonomy or have we reached the goal
    def update_auto(self, bool_msg : Bool):
        self.is_goal = bool_msg.data
    
    # Send the data to the port
    def send_mode(self, mode : str):
        data = ""
        match mode:
            case 'autonomous':
                data = "0"

            case 'teleop':
                data = "1"

            case 'arrival':
                data = "2"

            case 'weewoo':
                data = "3"

            case 'party':
                data = "4"

            case 'wvu':
                data = "5"

            case 'rainbow':
                data = "6"

            case 'monash':
                data = "7"

            case _:
                self.get_logger().error(f'Provided data "{mode}" was not valid for any of three modes')
                return

        #FIRST DEBUG LOGGER (BEFORE CONVERSION)
        #self.get_logger().info(f"send_mode hit: mode='{mode}', data='{data}'")
        data = bytes(data, 'utf-8')
        port = self.get_parameter('device_path').get_parameter_value().string_value
        ser = serial.Serial(port, 9600)

        #SECOND DEBUG LOGGER (RAW DATA)
        #self.get_logger().info(f"send_mode hit: port='{port}', hex-data='{data}', serial= '{ser}'")
        ser.write(data)
        ser.close()

    #Overide Mode Code.#####################
    def override_mode(self, msg: String):
        if msg.data.strip() == "":
            self.override = False
            self.forced_mode = ""
            #self.get_logger().info("LED override cleared")
        else:
            self.override = True
            self.forced_mode = msg.data.strip()
            #self.get_logger().info(f"LED override set to {self.forced_mode}")
    #########################

def main(args=None):
    rclpy.init(args=args)

    autonomy_led_subscriber = AutonomyLEDSubscriber()

    rclpy.spin(autonomy_led_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    autonomy_led_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()