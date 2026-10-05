# Camera Publisher Quick Start

ROS 2 node for publishing a USB camera to `/image_raw` using OpenCV.

Assumes **ROS 2 Humble is already installed**.

## 1. Check Camera

```bash
ls /dev/video*
```

The camera should appear as `/dev/video0`.

You can also check:

```bash
lsusb
```

## 2. Install Dependencies

```bash
sudo apt update
sudo apt install python3-opencv ros-humble-cv-bridge
```

Optional camera debugging tools:

```bash
sudo apt install v4l-utils ffmpeg
```

## 3. Build

From the ROS 2 workspace:

```bash
source /opt/ros/humble/setup.bash

colcon build --packages-select camera_pub

source install/setup.bash
```

## 4. Run Camera Publisher

```bash
ros2 run camera_pub camera_node
```

The camera should now publish to:

```text
/image_raw
```

## 5. Verify Camera Topic

Open another terminal:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
```

Check that the topic exists:

```bash
ros2 topic list
```

Check the publishing rate:

```bash
ros2 topic hz /image_raw
```

## 6. View Camera in RViz

```bash
rviz2
```

In RViz:

1. Click **Add**
2. Select **Image**
3. Set the topic to `/image_raw`

The live camera feed should appear.

## WSL Users

The USB camera must be passed through to WSL before starting the ROS node.

Verify that WSL can see it:

```bash
lsusb
ls /dev/video*
```

The camera should appear as:

```text
/dev/video0
```

## New Terminal Setup

Whenever you open a new terminal:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
```

Then the camera node can be started with:

```bash
ros2 run camera_pub camera_node
```