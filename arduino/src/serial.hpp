#ifndef SERIAL_ARM_HPP
#define SERIAL_ARM_HPP

#include <string>

class serial_arm {
private:
  std::string location;
  int baudrate, timeout;

public:
  serial_arm()
  {}

  void sendData(mpu6050_diy & bovenarm, mpu6050_diy & onderarm) {
    // bovenarm data
    hwlib::cout << "a"
		<< bovenarm.getGyroX()
		<< ","
		<< bovenarm.getGyroY()
		<< ","
		<< bovenarm.getGyroZ()
		<< "*"
		<< bovenarm.getAccelX()
		<< ","
		<< bovenarm.getAccelY()
		<< ","
		<< bovenarm.getAccelZ();

    // Onderarm data
    hwlib::cout << "b"
		<< onderarm.getGyroX()
		<< ","
		<< onderarm.getGyroY()
		<< ","
		<< onderarm.getGyroZ()
		<< "*"
		<< onderarm.getAccelX()
		<< ","
		<< onderarm.getAccelY()
		<< ","
		<< onderarm.getAccelZ();




    // hwlib::cout << bovenarm.getGyroX;
    // hwlib::cout << ",";
    // hwlib::cout << bovenarm.getGyroY;
    // hwlib::cout << ",";
    // hwlib::cout << bovenarm.getGyroZ;
    // hwlib::cout << "]";


  }
};
#endif
