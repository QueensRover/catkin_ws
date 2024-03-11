from qset_lib import Rover, AngleReader
from time import sleep
import signal
import math

def main():
    rover = Rover() # this line starts the connection to the rover and gives access to the rover data
    angle_reader = AngleReader()

    # This line allows for the KeyboardInterrupt to worl
    signal.signal(signal.SIGINT, signal.default_int_handler)
    i = 0

    gpsX = 10
    gpsY = 5
    dx = gpsX - rover.x
    dy = gpsY - rover.y
    angle = math.atan2(abs(dy), abs(dx))*(180 / math.pi) #THIS IS JUST ZERO IDK WHY NEED TO FIX

        

    left_side_speed = 1
    right_side_speed = 1
    isTooClose = False
    try:
        while not isTooClose or True:
            print(" ANGLE: " + str(angle_reader.read_angle))
            # this line prints the current location and heading of the rover
            print("X: " + str(rover.x) + " Y: " + str(rover.y) + " Heading: " + str(rover.heading))
            # the below lines iterate through all the laser scan lines and prints if the distance is less than 0.5 meters

            if(gpsX > 0 and gpsY > 0):
                headingDirection = angle-90
                while rover.heading > headingDirection:
                    left_side_speed = 1
                    right_side_speed = -1
            if(gpsX > 0 and gpsY < 0):
                while rover.heading > (-180 + angle):
                    left_side_speed = 1
                    right_side_speed = -1
                    rover.send_command(left_side_speed, right_side_speed)
            if(gpsX < 0 and gpsY < 0):
                while rover.heading < (90 + angle):
                    left_side_speed = -1
                    right_side_speed = 1
                    rover.send_command(left_side_speed, right_side_speed)
            if(gpsX < 0 and gpsY < 0):
                while rover.heading < (90 - angle):
                    left_side_speed = -1
                    right_side_speed = 1
                    rover.send_command(left_side_speed, right_side_speed)
            
            
            left_side_speed = 1
            right_side_speed = 1
            rover.send_command(left_side_speed,right_side_speed)


            for dist in rover.laser_distances:
                if dist < 5:
                    print("TOO CLOSE")
                    isTooClose = True
                    if rover.heading > -17:
                        left_side_speed = 1
                        right_side_speed = 0.5
                        print("HEADING LESS THAN 17")
                    else:
                        left_side_speed = 1
                        right_side_speed = 1
                        print("GO STRAIGHT AGAIN")
                    break
            # the below line sends a command to the rover (simulation) 
            rover.send_command(left_side_speed, right_side_speed)
            i = i + 1
            sleep(0.5)

    except KeyboardInterrupt:
        pass

    rover.send_command(0, 0)

if __name__ == "__main__":
    main()