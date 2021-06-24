#ifndef OLED_ARM_HPP
#define OLED_ARM_HPP

#include "../submodules/ipass-mpu6050/ipass-mpu6050.hpp"
#include "toolbox.hpp"
#include <math.h>
#include <string>
#include <cstring>

/// \brief
/// oled_arm class
/// \details
/// Deze class is verantwoordelijk om de armen te schrijven op de oled.
/// De klas is afhankelijk van de hwlib::glcd_oled class.
class oled_arm {
private:
  hwlib::i2c_bus & i2c_bus;
  uint8_t i2c_address;
  hwlib::glcd_oled display = hwlib::glcd_oled( i2c_bus, i2c_address );  

  hwlib::font_default_8x8 font    = hwlib::font_default_8x8();
  hwlib::terminal_from terminal_display = hwlib::terminal_from( display, font );

  int private_arm_length = 30;


public:
  /// \brief
  /// Constructor van oled_arm.
  /// \details
  /// Deze constructer neemt 2 inputs, i2c_bus van hwlib en een uint_fast8_t address voor de i2c minion.
  /// De klas is afhankelijk van de hwlib::glcd_oled class.
  oled_arm(hwlib::i2c_bus & i2c_bus, uint_fast8_t i2c_address ):
    i2c_bus( i2c_bus ),
    i2c_address( i2c_address)
  {}

  /// \brief
  /// Functie om de arm te tekenen op het oled scherm.
  /// \details
  /// De functie schrijft 2 armen naar het scherm. Hij pakt hiervoor de graden van de oled, en vertaalt deze naar pixels.
  void drawArm(mpu6050_diy & bovenarm, mpu6050_diy & onderarm ) {
    int start_x_onderarm;
    int bovenarm_lengte = 30;
    
    toolbox toolbox;
    int bovenarm_x_graden = bovenarm.getAccelX();

    // 110 is arm recht, 40 is arm naar binnen.
    // int onderarm_z_graden = bovenarm.getAccelZ();

    
    int start_x_bovenarm = 31;
    int capture_x_bovenarm   = toolbox.translateToScreenSize(bovenarm_x_graden);
    double tussen_x_bovenarm = toolbox.difference(capture_x_bovenarm, start_x_bovenarm);
    int tmp_x_bovenarm    = toolbox.steps(bovenarm_lengte, tussen_x_bovenarm); //bovenarm_lengte / tussen_x_bovenarm;
    int step_x_bovenarm = 0;
    int tussen_x_bovenarm_stap = round(tmp_x_bovenarm);
    int stap_x_bovenarm = 1;

    display.clear();
    if (tussen_x_bovenarm_stap >= 0) {
      for (int i = 0; i <= bovenarm_lengte; i++) {
        step_x_bovenarm++;
        if (step_x_bovenarm == tussen_x_bovenarm_stap) {
        step_x_bovenarm = 0;
        stap_x_bovenarm++;
        bovenarm_lengte--;
        }
	if (i == bovenarm_lengte) {
	  start_x_onderarm = start_x_bovenarm + stap_x_bovenarm;
	}
        display.write( hwlib::xy( i, start_x_bovenarm + stap_x_bovenarm));
      }
    } else {
      for (int i = 0; i <= bovenarm_lengte; i++) {
        step_x_bovenarm--;
        if (step_x_bovenarm == tussen_x_bovenarm_stap) {
          step_x_bovenarm = 0;
          stap_x_bovenarm--;
          bovenarm_lengte--;
        }
	if (i == bovenarm_lengte) {
	  start_x_onderarm = start_x_bovenarm + stap_x_bovenarm;
	}
        display.write( hwlib::xy( i, start_x_bovenarm + stap_x_bovenarm));
      }
    }

    int onderarm_x_graden = onderarm.getAccelX();
    int onderarm_z_graden = onderarm.getAccelZ();
    int awnser = 0.375 * (onderarm_z_graden - 30);

    int onderarm_lengte = 30;


    int capture_x_onderarm = toolbox.translateToScreenSize(onderarm_x_graden);
    double tussen_x_onderarm =  toolbox.difference(capture_x_onderarm, start_x_bovenarm);
    double tmp_x_onderarm = toolbox.steps(onderarm_lengte, tussen_x_onderarm);

    int tussen_x_onderarm_stap = round(tmp_x_onderarm);

    if (tussen_x_onderarm_stap >= 0) {
      for (int i = 0; i <= onderarm_lengte; i++) {
        step_x_bovenarm++;
        if (step_x_bovenarm == tussen_x_onderarm_stap) {
	  step_x_bovenarm = 0;
	  stap_x_bovenarm++;
	  if (awnser < 30) {
	    onderarm_lengte = awnser;
	  }
	  onderarm_lengte--;
	}
        display.write( hwlib::xy( i + bovenarm_lengte , start_x_bovenarm + stap_x_bovenarm));
      }
    } else {
      for (int i = 0; i <= onderarm_lengte; i++) {
        step_x_bovenarm--;
        if (step_x_bovenarm == tussen_x_onderarm_stap) {
          step_x_bovenarm = 0;
          stap_x_bovenarm--;
	  if (awnser < 30) {
	    onderarm_lengte = awnser;
	  }
          onderarm_lengte--;
        }
	display.write( hwlib::xy( i + bovenarm_lengte , start_x_bovenarm + stap_x_bovenarm));
      }
    }
    display.flush();
  }

  /// \brief
  /// Functie om tekst met de waarde van een arm af te drukken.
  /// \details
  /// Deze functie
  /// De klas is afhankelijk van de hwlib::glcd_oled class.
  void printArm(mpu6050_diy & bovenarm, mpu6050_diy & onderarm) {
    toolbox toolbox;
    int bovenarm_y_graden = bovenarm.getGyroY();
    int arm_lengte = 30; 
    int arm_beweging = toolbox.armLength(bovenarm_y_graden, arm_lengte);

    if (arm_beweging < 29) {
      private_arm_length -= (arm_lengte - arm_beweging);
    } else if ( arm_beweging > 31) {
      private_arm_length += (arm_lengte - arm_beweging);
    }

    terminal_display 
      << "\f" << toolbox.armLength(bovenarm_y_graden, arm_lengte)
      << "\n" << arm_lengte
      << "\t0003" << bovenarm_y_graden
      << "\t0004" << private_arm_length

      << hwlib::flush;   
  }

  /// \brief
  /// Functie gyroscoop waarden van een mpu6050 sensor op een oled te printen.
  /// \details
  /// Deze functie print de X, Y en Z waarden van de gyroscoop uit.
  void printArmGyro(mpu6050_diy & arm) {
    int arm_x_gyro = arm.getGyroX();
    int arm_y_gyro = arm.getGyroY();
    int arm_z_gyro = arm.getGyroZ();

    terminal_display 
      << "\f" << arm_x_gyro
      << "\n" << arm_y_gyro
      << "\t0003" << arm_z_gyro
      << hwlib::flush;   
  }
  
  /// \brief
  /// Functie acceleromater waarden van een mpu6050 sensor op een oled te printen.
  /// \details
  /// Deze functie print de X, Y en Z waarden uit van de acceleromater uit.
  void printArmAccel(mpu6050_diy & arm) {
    int arm_x_accel = arm.getAccelX();
    int arm_y_accel = arm.getAccelY();
    int arm_z_accel = arm.getAccelZ();

    terminal_display 
      << "\f" << arm_x_accel
      << "\n" << arm_y_accel
      << "\t0003" << arm_z_accel
      << hwlib::flush;   
  }
  
  /// \brief
  /// Functie om arm lengte van de onderarm uit te printen.
  /// \details
  /// Deze functie de lengte van de onderarm uit.
  void printArmLength(mpu6050_diy & arm) {
    int arm_z_accel = arm.getAccelZ();
    
    toolbox toolbox;
    int awnser = 0.375 * (arm_z_accel - 30);
    terminal_display 
      << "\f" << awnser
      << hwlib::flush;   
  }

};

#endif
