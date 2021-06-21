#include "hwlib.hpp"
#include "../submodules/ipass-mpu6050/ipass-mpu6050.hpp"
#include <vector>
#include "oled_arm.hpp"
#include "toolbox.hpp"
//#include "serial.hpp"

int main( void ){	
  hwlib::wait_ms( 500 );   
  
  namespace target = hwlib::target;
  
  auto scl     = target::pin_oc( target::pins::scl );
  auto sda     = target::pin_oc( target::pins::sda );
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
  
  mpu6050_diy onderarm = mpu6050_diy(i2c_bus, 0x68);
  mpu6050_diy bovenarm = mpu6050_diy(i2c_bus, 0x69);

  bovenarm.wakeup();
  onderarm.wakeup();

  oled_arm arm = oled_arm(i2c_bus, 0x3c);

  for(;;) {
    //arm.drawArm(bovenarm,onderarm);
    arm.printArm(bovenarm,onderarm);
  }
}
