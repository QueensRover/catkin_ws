import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Polygon



def laserCallBack(msg):
    global points
    points = msg.ranges
    #your code goes here


def sendPoints(data):
    global pointsPub
    msg = Polygon()
    msg.data = data
    pointsPub.publish(msg)


rospy.init_node("object_avoid")
pointsPub = ropsy.Pubisher("/objects", Polygon, queue_size=1)

rospy.Subscriber("/leddar/scan", LaserScan, laserCallBack)

rospy.spin()


