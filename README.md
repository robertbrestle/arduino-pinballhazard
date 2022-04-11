# Arduino Pinball Hazard
This code controls an Arduino to trigger a servo when an ultrasonic sensor detects something within a specified range.

# Components
- Arduino UNO R3 x1  
  - with power source  
- Breadboard(s)  
- Button x1  
- HC-SR04 Ultrasonic Sensor x1  
- LED x1  
- LCD1602A LCD Module x1  
- Potentiometer x1  
- 1K Resistor x2  
- SG90 Servo Motor x1  
- Wires  

# Setup
TODO

## Pins
| PIN | PURPOSE |
|---|---|
| D2 | Button |
| D3 | LED |
| D8 | Ultrasonic ECHO |
| D9 | Ultrasonic TRIG |
| D4 | Display DATA7 |
| D5 | Display DATA6 |
| D6 | Display DATA5 |
| D7 | Display DATA4 |
| D11 | Display EN |
| D12 | Display RS |
| D13 | Servo |
| A5 | Potentiometer |

## Variables
| VARIABLE | PURPOSE | NOTES |
|---|---|
| SERVO_DELAY | delay of the servo between angle changes in milliseconds | default 10 |
| SERVO_INCREMENT | the servo increment/decrement angle | default 5 |
| LOOP_DELAY | delay of the loop in milliseconds |  default 100 |
| swingCounterMax | number of swings when servo activated |  default 3 |

# References
- [Resistor Color Codes](https://www.arrow.com/en/research-and-events/articles/resistor-color-code)
- [Arduino UNO Pinout Diagram]( https://images.prismic.io/circuito/8e3a980f0f964cc539b4cbbba2654bb660db6f52_arduino-uno-pinout-diagram.png?auto=compress,format)
- [Make a Simple LED Circuit](https://create.arduino.cc/projecthub/rowan07/make-a-simple-led-circuit-ce8308)
- [Servo: Arduino Basics](https://create.arduino.cc/projecthub/glowascii/servo-arduino-basics-cb9266)
- [Interfacing LCD1602 with Arduino](https://create.arduino.cc/projecthub/najad/interfacing-lcd1602-with-arduino-764ec4)
- [Ultrasonic Sensor HC-SR04 with Arduino Tutorial](https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6)
- [Arduino Potentiometer – Complete Tutorial](https://roboticsbackend.com/arduino-potentiometer-complete-tutorial/)

&nbsp;