from qset_lib import Rover
from time import sleep

def main():
    rover = Rover() # this line starts the connection to the rover and gives access to the rover data

    i = 0

    left_side_speed = 1
    right_side_speed = 1

    while i < 1000:
        print("X: " + str(rover.x) + " Y: " + str(rover.y) + " Heading: " + str(rover.heading)) # this line prints the current location and heading of the rover

        # the below lines iterate through all the laser scan lines and prints if the distance is less than 0.1 meters
        for dist in rover.laser_distances:
            if dist < 0.1:
                print("TOO CLOSE")

        # the below line sends a command to the rover (simulation) 
        rover.send_command(left_side_speed, right_side_speed)

        i = i + 1
        sleep(0.01)


if __name__ == "__main__":
    main()
