import rospy
from sensor_msgs.msg import LaserScan
from wheel_control.msg import wheelSpeed

closestDistance = 1000000
leddar = "go"
def leddarCallBack(msg):
    global closestDistance, leddar
    closestDistance = 1000000
    count = 0
    for dist in msg.ranges:
        if dist < closestDistance:
            closestDistance = dist
            if count < 8 :
                leddar = "left"
            else:
                leddar = "right"
        count += 1
    if closestDistance > 2.5: leddar = "go"
    elif closestDistance < 0.75 : leddar = "stop"



rospy.init_node("leddarTest")
wheelPub = rospy.Publisher("/gazebo_wheelControl/wheelSpeedTopic", wheelSpeed, queue_size=1)
rospy.Subscriber("/leddar/leddarData",LaserScan,leddarCallBack)


while not rospy.is_shutdown():
    msg = wheelSpeed()
    if leddar == "go":
        msg.left = 1.0
        msg.right = 1.0
    elif leddar == "stop":
        msg.left = 0.0
        msg.right = 0
    elif leddar == "left":
        msg.right = 1.0
        msg.left = -1.0
    elif leddar == "right":
        msg.right = -1.0
        msg.left = 1.0
    msg.wheelMode = 0
    wheelPub.publish(msg)
    #print(msg)