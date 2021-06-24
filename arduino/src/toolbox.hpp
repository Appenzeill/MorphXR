#ifndef TOOLBOX_HPP
#define TOOLBOX_HPP

class toolbox {
public:
  toolbox()
  {}

  int translateToScreenSize(int graden) {
    return graden / 3;
  }
  
  double difference(int start, int end) {
    return start - end;
  }

  int steps(int start, double end) {
    return start / end;
  }

  int armLength(int accel_y, int arm_length) {
    int pixels = ((accel_y + 90) / 6);
    return pixels;
  }

  int armLengthForearm(int forearm, int forearm_y) {

    float tmp = forearm / 80;
    // 110 tot 30 = 80 tot 0
    // 30 / 80
    // 0.277777 * 50 = 13
    //         30   / 80  * 0 tot 80
    return tmp * forearm_y;
  }
};

#endif
