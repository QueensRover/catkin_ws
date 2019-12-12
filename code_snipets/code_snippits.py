import rospy  # this is the module required for all simulation communication

# start of wheel control code
from wheel_control.msg import wheelSpeed  # this is a required module for the drive communication


class WheelController:

    def __init__(self):
        rospy.init_node("wheel_controller")
        self.wheel_pub = rospy.Publisher("/gazebo/wheelSpeedTopic", wheelSpeed, queue_size=1)  # TODO verify topic name

    def drive_wheels(self, left, right):
        # type: (float, float) -> None
        # left and right are numbers between -1 and 1
        msg = wheelSpeed()
        msg.left = left
        msg.right = right
        msg.wheelMode = 0
        self.wheel_pub.publish(msg)


# end of wheel control code

# start of laser scan code
from sensor_msgs.msg import LaserScan


class LaserListener:

    def __init__(self):
        rospy.init_node("laser_listener")
        self.laserSub = rospy.Subscriber("/leddar/data", self.laser_callback, queue_size=1)  # TODO verify this
        self.laserRanges = []

    def laser_callback(self, msg):
        # type: (LaserScan) -> None
        self.laserRanges = msg.ranges


# end of laser scan code access laserRanges for an array of all measured distances from the laser sensors

# start of localization stuff
from sensor_msgs.msg import NavSatFix
from std_msgs.msg import Float32


class LocationHeading:

    def __init__(self):
        rospy.init_node("location_listener")
        self.fixSub = rospy.Subscriber("/fix", self.fix_callback, queue_size=1)  # TODO verify topic name
        self.headingSub = rospy.Subscriber("/heading", self.heading_callback, queue_size=1)  # TODO verify topic name
        self.lat = 0.0
        self.lon = 0.0
        self.heading = 0.0

    def fix_callback(self, msg):
        # type: (NavSatFix) -> None
        self.lat = msg.latitude
        self.lon = msg.longitude

    def heading_callback(self, msg):
        # type: (Float32) -> None
        self.heading = msg.data


# end of localization stuff

# start of destination listening code
from std_msgs.msg import Float32MultiArray


class Destination:

    def __init__(self):
        rospy.init_node("destination_listener")
        self.lat = 0.0
        self.lon = 0.0
        self.destSub = rospy.Subscriber("/destination", Float32MultiArray, self.destination_callback, queue_size=1)

    def destination_callback(self, msg):
        # type: (Float32MultiArray) -> None
        self.lat = msg.data[0]
        self.lon = msg.data[1]


# end of destination listening code

# start of control loop snippet

while not rospy.is_shutdown():
    print("do your controlling here")

# end of control loop snippet
