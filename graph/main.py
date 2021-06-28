import serial
ser= serial.Serial('/dev/ttyACM0',2400, timeout=1)

def rad():
    return ser.read().decode()

def read(arm):
    tmp = ""
    while(True):
        read = rad()
        if (read == "," or read == "*" or read == "a" or read == "b"):
            break
        else:
            tmp += read
    arm.append(int(tmp))
    return arm
        
        
bovenarm = []
onderarm = []

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


    if (len(bovenarm) != 0):
        print("bovenarm")
        print(bovenarm)
    if (len(onderarm) != 0):
        print("onderarm")
        print(onderarm)

                
