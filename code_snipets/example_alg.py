#start of code snippets


import rospy  # this is the module required for all simulation communication

# start of wheel control code
from wheel_control.msg import wheelSpeed  # this is a required module for the drive communication

rospy.init_node("controller")

class WheelController:

    def __init__(self):
        self.wheel_pub = rospy.Publisher("/gazebo_wheelControl/wheelSpeedTopic", wheelSpeed, queue_size=1)

    def drive_wheels(self, left, right):
        # type: (float, float) -> None
        # left and right are numbers between -1 and 1
        msg = wheelSpeed()
        msg.left = left
        msg.right = right
        msg.wheelMode = 0
        self.wheel_pub.publish(msg)
        #print(msg)


# end of wheel control code

# start of laser scan code
from sensor_msgs.msg import LaserScan


class LaserListener:

    def __init__(self):
        self.laserSub = rospy.Subscriber("/leddar/leddarData", LaserScan, self.laser_callback, queue_size=1)
        self.laserRanges = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]

    def laser_callback(self, msg):
        # type: (LaserScan) -> None
        self.laserRanges = msg.ranges


# end of laser scan code access laserRanges for an array of all measured distances from the laser sensors

# start of localization stuff
from geometry_msgs.msg import Point
from std_msgs.msg import Float32


class LocationHeading:

    def __init__(self):
        self.fixSub = rospy.Subscriber("/fix/metres", Point, self.fix_callback, queue_size=1)
        self.headingSub = rospy.Subscriber("/heading",Float32, self.heading_callback, queue_size=1)
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0
        self.heading = 0.0

    def fix_callback(self, msg):
        # type: (Point) -> None
        self.x = msg.x
        self.y = msg.y
        self.z = msg.z

    def heading_callback(self, msg):
        # type: (Float32) -> None
        self.heading = msg.data


# end of localization stuff


#initiallize classes to get and send data to gazebo
locHead  = LocationHeading()
laser = LaserListener()
wheel = WheelController()
#end of initialization

# start of control loop snippet

while not rospy.is_shutdown():
    minRange = 99

    for x in range(0, 15):
        if laser.laserRanges[x] < minRange:
            minRange = laser.laserRanges[x]
    if minRange < 3:
        wheel.drive_wheels(1, -1)
    else:
        wheel.drive_wheels(1, 1)
    if laser.laserRanges[0] is not None:
        print("Current Heading: ", locHead.heading, "Current x val: ", locHead.x, "RightMostLaser: ", laser.laserRanges[0])

# end of control loop snippet
