Connecting to Hokuyo: https://github.com/mrsd16teamd/loco_car/wiki/Localization

Install following ROS packages (git clone):
- Laser_proc: https://github.com/ros-perception/laser_proc
- Urg_node: https://github.com/ros-drivers/urg_node 
- Urg_c node: https://github.com/ros-drivers/urg_c


To set your computer’s subnet to work with the hokuyo:
`cd /etc/network`
Edit “interfaces”: → have to do "sudo nano interfaces" to override admin
```
# interfaces(5) file used by ifup(8) and ifdown(8)
auto lo
iface lo inet loopback

allow-hotplug enxa0cec808aa14
iface enxa0cec808aa14 inet static
address 192.168.0.15
netmask 255.255.255.0 
```
**enxa0cec808aa14 is my USB port name, I think everyone's should be the same, but you may need to check in ifconfig while USB plugged in. If using ethernet port, will have to use different configuration. (Should only be Chris)**
-----------------------------
NOW, if you have an older computer like Chris that has an ether jack, do this instead:
add the following to the interface file:
```
auto eth0:0
iface eth0:0 inet static
address 192.168.0.15
netmask 255.255.255.0
```
The rest are the same #LIT

note, even though the address is set to 192.168.0.15 in the interface file, you still launch the LIDAR with the address 192.168.0.10

#EVENMORELIT
------------------------------

May need to restart computer after changing interfaces file

Edit launch file "urg_lidar.launch" under urg_node/launch
Add on line '<param name="ip_address" value=""/>' the ip address value to be '<param name="ip_address" value="192.168.0.10"/>'
```
roscore
roslaunch urg_node urg_lidar.launch
```
Rviz -> make fixed frame “/laser” (will have to type out, not shown on pull down menu) and add "LaserScan" under "topic" tab from “/scan”

To create LIDAR map:
Install the following ROS packages:
hector_slam: git@github.com:tu-darmstadt-ros-pkg/hector_slam.git

```
Roscore
roslaunch urg_node urg_lidar.launch
roslaunch hector_slam_launch tutorial.launch
```
Push CaBot slowly down desired mapping route (should see map start to form in rviz)

After you've reached the end of the mapped route, run:
```
rosrun map_server map_saver -f desired_map_name
```

This command will save a .png and .yaml file of your map that can be used on the navigation stack. 



