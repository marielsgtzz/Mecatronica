"""
Created on Mon Nov 10 07:01:28 2023
@author: Danya
"""

#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
import sys

def turtle_circle(radio):
    rospy.init_node('turtlesim', anonymous=True)
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    rate = rospy.Rate(1) #1Hz
    vel = Twist()
    while not rospy.is_shutdown():
        vel.linear.x = radio
        vel.linear.y = 0
        vel.linear.z = 0
        vel.angular.x = 0
        vel.angular.y = 0
        vel.angular.z = 1
        rospy.loginfo("Radio = %f", radio)
        pub.publish(vel)
        rate.sleep()

if __name__ == '__main__':
	try:
		turtle_circle(int(sys.argv[1]))
	except rospy.ROSInterruptException:
		pass
