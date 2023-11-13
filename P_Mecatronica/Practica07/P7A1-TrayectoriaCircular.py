"""
Created on Fri Nov 10 07:01:28 2023
@author: Danya
"""

#!/usr/bin/env python3

# Importa las bibliotecas necesarias de ROS y mensajes para controlar la tortuga
import rospy
from geometry_msgs.msg import Twist
import sys

def turtle_circle(radio):
    rospy.init_node('turtlesim', anonymous=True) # Inicializa el nodo ROS con el nombre 'turtlesim' y modo anónimo
    
    # Crea un publicador que envía comandos de velocidad a la tortuga en el tópico '/turtle1/cmd_vel'
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    
    rate = rospy.Rate(1) # Establece la frecuencia de publicación en 1 Hz
    
    vel = Twist() # Crea un objeto Twist para representar los comandos de velocidad lineal y angular
	
    while not rospy.is_shutdown():
        vel.linear.x = radio # Configura la velocidad lineal en el eje x con el valor del radio dado
        
        # Configura las demás velocidades como cero, ya que solo nos interesa el movimiento circular
        vel.linear.y = 0
        vel.linear.z = 0
	    
        vel.angular.x = 0
        vel.angular.y = 0
        
        # Configura la velocidad angular en el eje z con un valor de 1 rad/s para lograr el movimiento circular
        vel.angular.z = 1
        
        rospy.loginfo("Radio = %f", radio) # Imprime el radio actual para información de registro
        pub.publish(vel)
        
        rate.sleep() # Espera según la frecuencia establecida

if __name__ == '__main__':
    try:
        # Llama a la función turtle_circle con el radio proporcionado como argumento de línea de comandos
        turtle_circle(int(sys.argv[1]))
    except rospy.ROSInterruptException:
        pass

