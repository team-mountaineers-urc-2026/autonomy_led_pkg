# autonomy_led_pkg

## Description

This package controls the rover's LEDs during the Autonomous Navigation
mission.

The package includes an Arduino script that should be flashed onto an
Arduino Leonardo connected internally to a LattePanda Sigma.
Additionally, it includes a subscriber node that serially writes to the
Leonardo and can turn the LEDs Red, Blue, or Green.

The node looks for 'autonomous', 'teleop', or 'arrival' on the topic
'autonomy_led_topic' to switch the LEDs to Red, Blue, and Green
respectively.

These modes and the topic name are parameterized and can be changed from
a launch file.

------------------------------------------------------------------------

## Controlling the LED Subscriber Node

SSH into Daedalus (or whatever Arduino has the LED code flashed and is
connected):

``` bash
ssh daedalus@192.168.1.69
```

When in Daedalus:

``` bash
source ros
ros2 run autonomy_led_pkg autonomy_led_subscriber
```

Use `tmux` to split the terminal.

------------------------------------------------------------------------

## Publishing Override Commands

Publish override commands like this:

``` bash
ros2 topic pub --once /led_mode_override std_msgs/msg/String "{data: 'mode'}"
```

### Available Modes

-   autonomous
-   teleop
-   arrival
-   weewoo
-   party
-   wvu
-   rainbow
-   monash

See GitHub for data byte details.

------------------------------------------------------------------------

## Simulating Activation During an Actual Run

### Autonomous Active

``` bash
ros2 topic pub --once /is_autonomous std_msgs/msg/Bool "{data: false}"
```

→ autonomous

``` bash
ros2 topic pub --once /is_autonomous std_msgs/msg/Bool "{data: false}"
```

→ teleop

``` bash
ros2 topic pub --once /goal_alert std_msgs/msg/Bool "{data: true}"
```

→ arrival

**Note:** Must be in autonomous mode for arrival to work.

------------------------------------------------------------------------

You can echo topics as usual in ROS if desired.

## Known Udev Port Issues

Usually the Arduino Controller/LED path is recognized as:

``` bash
self.declare_parameter('device_path', '/dev/ttyACM1')
```

However, lately Daedalus has been setting the Arduino device path to:

``` bash
/dev/ttyACM0
```

This needs to be changed in the udev rules GitHub, but for now, if the
LEDs are not responding but the node is publishing and responding to ROS
commands, check the device paths with:

``` bash
ls /dev
```

Find the current device paths (usually ttyACM0 and ttyACM1) and change
the controller node code to use either one to determine which the
Arduino/LEDs are connected to.

There are also loggers currently commented out in the code to help with
troubleshooting if they need to be enabled.
