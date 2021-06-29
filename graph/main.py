import serial
import math
import time
import pickle

import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
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
        

# clear file voor nieuwe data
with open("arm.txt", 'r+') as f:
    f.truncate(0)

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

        

                
