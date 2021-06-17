#include "hwlib.hpp"
#include "../submodules/ipass-mpu6050/ipass-mpu6050.hpp"
#include <vector>

int main( void ){	
  hwlib::wait_ms( 500 );   
  
  namespace target = hwlib::target;
  
  auto scl     = target::pin_oc( target::pins::scl );
  auto sda     = target::pin_oc( target::pins::sda );
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
  
  auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 
  auto mpu6050_a = mpu6050_diy(i2c_bus, 0x68);
  auto mpu6050_b = mpu6050_diy(i2c_bus, 0x69);

  auto font    = hwlib::font_default_8x8();
  auto display = hwlib::terminal_from( oled, font );
  
  mpu6050_a.wakeup();
  mpu6050_b.wakeup();

  for(;;) {
    int16_t x_complete_a = mpu6050_a.getAccelX();
    int16_t y_complete_a = mpu6050_a.getAccelY();
    int16_t z_complete_a = mpu6050_a.getAccelZ();

    int16_t x_complete_b = mpu6050_b.getAccelX();
    int16_t y_complete_b = mpu6050_b.getAccelY();
    int16_t z_complete_b = mpu6050_b.getAccelZ();

    hwlib::cout << "test";
    display 
      << "\f" << "x: " << x_complete_a
      << "\n" << "y: " << y_complete_a
      << "\t0002" << "z: " << z_complete_a

      << "\t0004" << "x: " << x_complete_b
      << "\t0005" << "y: " << y_complete_b
      << "\t0006" << "z: " << z_complete_b
      
      << hwlib::flush;
  }  
}
