#ifndef OLED_ARM_HPP
#define OLED_ARM_HPP

#include "../submodules/ipass-mpu6050/ipass-mpu6050.hpp"
#include "toolbox.hpp"


class oled_arm {
private:
  hwlib::i2c_bus & i2c_bus;
  uint8_t i2c_address;
  hwlib::glcd_oled display = hwlib::glcd_oled( i2c_bus, i2c_address );  

  hwlib::font_default_8x8 font    = hwlib::font_default_8x8();
  hwlib::terminal_from terminal_display = hwlib::terminal_from( display, font );

  int private_arm_length = 30;


public:
  oled_arm(hwlib::i2c_bus & i2c_bus, uint_fast8_t i2c_address ):
    i2c_bus( i2c_bus ),
    i2c_address( i2c_address)
  {}

  void drawArm(mpu6050_diy & bovenarm, mpu6050_diy & onderarm ) {
    int start_x_onderarm;
    int bovenarm_lengte = 30;
    
  toolbox toolbox;
    int bovenarm_x_graden = bovenarm.getAccelX();
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
    int capture_x_onderarm = onderarm_x_graden / 3;
    int onderarm_lengte = 30;
    double tussen_x_onderarm = capture_x_onderarm - start_x_bovenarm;
    double tmp_x_onderarm = onderarm_lengte / tussen_x_onderarm;

    int tussen_x_onderarm_stap = round(tmp_x_onderarm);


    if (tussen_x_onderarm_stap >= 0) {
      for (int i = 0; i <= onderarm_lengte; i++) {
        step_x_bovenarm++;
        if (step_x_bovenarm == tussen_x_onderarm_stap) {
        step_x_bovenarm = 0;
        stap_x_bovenarm++;
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
          onderarm_lengte--;
        }
        display.write( hwlib::xy( i + bovenarm_lengte , start_x_bovenarm + stap_x_bovenarm));
      }
    }
    display.flush();
  }

  void printArm(mpu6050_diy & bovenarm, mpu6050_diy & onderarm) {
    toolbox toolbox;
    int bovenarm_y_graden = bovenarm.getGyroY();
    int arm_lengte = 30; 
    int arm_beweging = toolbox.armLength(bovenarm_y_graden, arm_lengte);
    // if (arm_beweging >= 30) {
    //   private_arm_length += arm_beweging;
    // } else {
    //   private_arm_length -= arm_beweging;
    // }

    // if ( arm_beweging < 29 ) {
    //   if (private_arm_length >= 0) {
    // 	int tmp = arm_lengte - arm_beweging;
    // 	private_arm_length -= tmp;
    //   }
    // } else if (arm_beweging < 31) {
    //   if (private_arm_length <= arm_lengte) {
    // 	int tmp = arm_lengte - arm_beweging;
    // 	private_arm_length += tmp;
    //   }
    // }    

    // if ( arm_beweging < 29 ) {
    //   if (private_arm_length >= 0) {
    // 	int tmp = arm_lengte - arm_beweging;
    // 	private_arm_length -= tmp;
    //   }
    // } else if (arm_beweging < 31) {
    //   if (private_arm_length <= arm_lengte) {
    // 	int tmp = arm_lengte - arm_beweging;
    // 	private_arm_length += tmp;
    //   }
    // }    

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
};

#endif
