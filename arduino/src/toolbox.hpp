#ifndef TOOLBOX_HPP
#define TOOLBOX_HPP

/// \brief
/// toolbox class
/// \details
/// Toolbox is gemaakt als functies los te koppelen van de arduino als dit nodig is.
/// Toolbox is primair bedoeld voor korte simpele functies die getest moeten kunnen worden zonder een arduino.
class toolbox {
public:

  /// \brief
  ///  Toolbox constructor
  /// \details
  /// Deze functie heeft geen parameters.
  toolbox()
  {}
  
  /// \brief
  /// Functie om graden te converten naar pixels voor het oled scherm.
  /// \details
  /// Deze funtie returned de hoeveelheid pixels in verhouding met graden terug voor het oled scherm.
  int translateToScreenSize(int graden) {
    return graden / 3;
  }
  
  /// \brief
  /// Functie om het verschil tussen 2 ints uit te rekenen.
  /// \details
  /// Deze funtie returned het verschill tussen int start en int end.
  double difference(int start, int end) {
    return start - end;
  }

  /// \brief
  /// Functie om start en end met elkaar te delen.
  /// \details
  /// Deze funtie returned int start gedeeld door double end.
  int steps(int start, double end) {
    return start / end;
  }

  /// \brief
  /// Functie om uit te rekenen hoelang een arm is.
  /// \details
  /// Deze funtie returned de de lengte van een arm doormiddel van int accel_y en int arm_length
  int armLength(int accel_y, int arm_length) {
    int pixels = ((accel_y + 90) / 6);
    return pixels;
  }
};
#endif
