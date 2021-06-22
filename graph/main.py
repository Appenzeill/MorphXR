import serial 
ser= serial.Serial('/dev/ttyACM0',2400, timeout=1)
while(True):
    read_ser=ser.read(size=15)
    print(read_ser)
