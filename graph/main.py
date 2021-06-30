import serial
import math
import time
import pickle
import threading

import numpy as np

import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation
import matplotlib.pyplot as plt

ser= serial.Serial('/dev/ttyACM0',2400, timeout=1)

def rad():
    return ser.read().decode()

def read(arm):
    tmp = ""
    while(True):
        read = rad()
        if (read == "," or read == "*" or read == "x" ):
            break
        else:            tmp += read
    arm.append(int(tmp))
    return arm
        
def write():
    while(True):
        tmp = ""
        bovenarm = []
        onderarm = []

        if (rad() == 'a'):
            bovenarm = read(bovenarm)
            bovenarm = read(bovenarm)
            bovenarm = read(bovenarm)
            bovenarm = read(bovenarm)
            bovenarm = read(bovenarm)
            bovenarm = read(bovenarm)
        
        if (rad() == 'b'):
            onderarm = read(onderarm)
            onderarm = read(onderarm)
            onderarm = read(onderarm)
            onderarm = read(onderarm)
            onderarm = read(onderarm)
            onderarm = read(onderarm)

        if (len(onderarm) != 0 and len(bovenarm) != 0):
            arm = [bovenarm,onderarm]
            with open("arm.txt", "wb") as fp: 
                pickle.dump(arm, fp)

def read_arm():
    time.sleep(0.001)
    with open('arm.txt', 'rb') as file:
        read_arm = pickle.load(file)
    return read_arm

# matplotlib data
fig = plt.figure()
ax = plt.axes(projection ='3d')

# waarden van axes
ax.set_xlim(0, 100)
ax.set_ylim(0, 100)
ax.set_zlim(0, 100)

def graph():
    while(True):
        graph_data = read_arm()
        print(graph_data)


def animate(i):
    graph_data = read_arm()
    arm_length = 50

    print(graph_data)
    # onderarm
    onderarm_angle = (180 - graph_data[1][3]) - 90 
    onderarm_sine_degrees = math.sin(math.radians(onderarm_angle))
    if (onderarm_sine_degrees != 0):
        onderarm_divider = 1 / onderarm_sine_degrees
    else:
        onderarm_divider = 1 / 0.0001

    onderarm_z = (arm_length / onderarm_divider)

    onderarm_len_a = arm_length*arm_length
    onderarm_len_b = onderarm_z*onderarm_z
    onderarm_y = math.sqrt(onderarm_len_a - onderarm_len_b)

    # x_start = 180
    # x_end = 150
    # x_total = x_start - x_end

    
    # # onderarm_x = (90 / x_total) * (graph_data[1][4] - x_end)

    # onderarm_x = (90 / x_total) * (graph_data[1][4] - (x_end + 15))
    # onderarm_x = 0


    
    
    # bovenarm
    bovenarm_angle = (180 - graph_data[0][3]) - 90 
    bovenarm_sine_degrees = math.sin(math.radians(bovenarm_angle))
    if (bovenarm_sine_degrees != 0):
        bovenarm_divider = 1 / bovenarm_sine_degrees
    else:
        bovenarm_divider = 1 / 0.0001

    bovenarm_z = (arm_length / bovenarm_divider)

    bovenarm_len_a = arm_length*arm_length
    bovenarm_len_b = bovenarm_z*bovenarm_z
    bovenarm_y = math.sqrt(bovenarm_len_a - bovenarm_len_b)

    bovenarm_z = bovenarm_z + 50
    
    X = [50,50, 50]
    Y = [0, bovenarm_y, bovenarm_y+onderarm_y]
    Z = [50,bovenarm_z ,bovenarm_z+onderarm_z]
    
    ax.clear()
    ax.set_xlim(0, 100)
    ax.set_ylim(0, 100)
    ax.set_zlim(0, 100)

    ax.plot3D(X,Y,Z)

thread_a = threading.Thread(target=write)
thread_a.start()

ani = animation.FuncAnimation(fig, animate, interval=100)
plt.show()
