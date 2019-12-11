import rospy
from geometry_msgs.msg import Twist
from wheel_control.msg import wheelSpeed



rospy.init_node("controler")
pub = rospy.Publisher("/gazebo_wheelControl/wheelSpeedTopic", wheelSpeed, queue_size=1)
def cmdCallBack(msg):
	global pub
	scale = msg.linear.x
	left = scale + msg.angular.z * -2
	right = scale + msg.angular.z * 2
	wheel = wheelSpeed()
	wheel.wheelMode = 0
	wheel.left = left * scale
	wheel.right = right*scale
	pub.publish(wheel)

rospy.Subscriber("/cmd_vel", Twist, cmdCallBack)
rospy.spin()
