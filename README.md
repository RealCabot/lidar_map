# A tool of building up the map

## Lidar configuration

Refer to the [wiki page](https://github.com/RealCabot/lidar_map/wiki/Lidar-configuration).

## Package dependencies

Install following ROS packages in your catkin workspace:
- [Laser_proc](https://github.com/ros-perception/laser_proc)
- [Urg_node](https://github.com/ros-drivers/urg_node)
- [Urg_c node](https://github.com/ros-drivers/urg_c)
- [hector_slam](https://github.com/tu-darmstadt-ros-pkg/hector_slam)

## How to use me
```
roslaunch lidar_map urg_lidar.launch
roslaunch lidar_map build_map.launch
```
Push CaBot slowly down desired mapping route (should see map start to form in rviz)

After you've reached the end of the mapped route, run:
```
rosrun map_server map_saver -f desired_map_name
```

This command will save a `.pgm` and `.yaml` file of your map that can be used on the navigation stack. 