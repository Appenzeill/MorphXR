#ifndef SERIAL_HPP
#define SERIAL_HPP


class serial {
private:
  mpu6050_diy & mpu6050;

public:
  serial(mpu6050_diy & mpu6050):
    mpu6050_diy(mpu6050)
  {}

  void sendAccelX() {
    //int16_t bovenarm_x = mpu6050.getAccelX();
    //int bovenarm_x_graden = (bovenarm_x + 250) / 2.77777777;
  }
  bool oi() {
    return 1;
  }
};
#endif

    // int16_t bovenarm_x = bovenarm.getAccelX();
    // int bovenarm_x_graden = (bovenarm_x + 250) / 2.77777777;

    // int16_t bovenarm_y = bovenarm.getAccelY();
    // int bovenarm_y_graden = (bovenarm_y + 250) / 2.77777777;

    // int16_t bovenarm_z = bovenarm.getAccelZ();
    // int bovenarm_z_graden = (bovenarm_z + 250) / 2.77777777;

    // int16_t bovenarm_x = bovenarm.getGyroX();
    // int bovenarm_x_graden = (bovenarm_x + 250) / 2.77777777;

    // int16_t bovenarm_y = bovenarm.getGyroY();
    // int bovenarm_y_graden = (bovenarm_y + 250) / 2.77777777;

    // int16_t bovenarm_z = bovenarm.getGyroZ();
    // int bovenarm_z_graden = (bovenarm_z + 250) / 2.77777777;


    // int16_t onderarm_x = onderarm.getAccelX();
    // int onderarm_x_graden = (onderarm_x + 250) / 2.77777777;

    // if (bovenarm_x_graden < 10 && bovenarm_x_graden > 0 ) {
    //   hwlib::cout << "[00" << bovenarm_x_graden << "]";
    // } else if (bovenarm_x_graden < 100  && bovenarm_x_graden > 0) {
    //   hwlib::cout << "[0" << bovenarm_x_graden << "]";
    // } else if (bovenarm_x_graden > 100  && bovenarm_x_graden > 0) {
    //   hwlib::cout << "[" << bovenarm_x_graden << "]";
    // } else if (bovenarm_x_graden < 0) {
    //   hwlib::cout << "[000]";
    // }

    // if (bovenarm_y_graden < 10 && bovenarm_y_graden > 0 ) {
    //   hwlib::cout << "[00" << bovenarm_y_graden << "]";
    // } else if (bovenarm_y_graden < 100  && bovenarm_y_graden > 0) {
    //   hwlib::cout << "[0" << bovenarm_y_graden << "]";
    // } else if (bovenarm_y_graden > 100  && bovenarm_y_graden > 0) {
    //   hwlib::cout << "[" << bovenarm_y_graden << "]";
    // } else if (bovenarm_y_graden < 0) {
    //   hwlib::cout << "[000]";
    // }

    // if (bovenarm_z_graden < 10 && bovenarm_z_graden > 0 ) {
    //   hwlib::cout << "[00" << bovenarm_z_graden << "]";
    // } else if (bovenarm_z_graden < 100  && bovenarm_z_graden > 0) {
    //   hwlib::cout << "[0" << bovenarm_z_graden << "]";
    // } else if (bovenarm_z_graden > 100  && bovenarm_z_graden > 0) {
    //   hwlib::cout << "[" << bovenarm_z_graden << "]";
    // } else if (bovenarm_z_graden < 0) {
    //   hwlib::cout << "[000]";
    // }
