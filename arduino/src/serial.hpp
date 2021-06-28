#ifndef SERIAL_ARM_HPP
#define SERIAL_ARM_HPP

#include <string>

/// \brief
/// serial_arm class
/// \details
/// Deze class is verantwoordelijk om de armen de data van de armen over serial weg te schrijven.
/// De klas is afhankelijk van de hwlib::cout.
class serial_arm {
private:
  std::string location;
  int baudrate, timeout;

public:
  /// \brief
  /// Constructor van serial_arm.
  /// \details
  /// Deze constructer heeft geen input.
  serial_arm()
  {}

  /// \brief
  /// Verstuurt data over serial. 
  /// \details
  /// Deze constructer gebruikt 2 mpu6050_diy instances en schrijft deze weg over serial met hulp van hwlib::cout.
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
		<< bovenarm.getAccelZ()
		<< "x";

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
		<< onderarm.getAccelZ()
		<< "x";
  }
};
#endif
