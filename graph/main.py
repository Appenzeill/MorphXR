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
            # angle = 180 - onderarm[3] - 90
            # print(angle)
            with open("arm.txt", "wb") as fp: 
                pickle.dump(arm, fp)

def graph():
    while(True):
        time.sleep(0.01)
        with open('arm.txt', 'rb') as file:
            # Call load method to deserialze
            myvar = pickle.load(file)
        print(myvar)

def animate(i):
    

thread_a = threading.Thread(target=write)
thread_b = threading.Thread(target=graph)

thread_a.start()
thread_b.start()
