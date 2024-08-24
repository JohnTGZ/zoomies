# zoomies
Vroom

# Hardware
## Servo
- LD-1501MG Digital Servo 17KG 180 Degree

Operating voltage: DC 6V ~ 7.4V

Running angle of approximately 165° over a servo pulse range of 800 µs to 2200 µs

Stall torque: 13kg.cm @6V; 15kg.cm @6.5V; 17kg.cm @7V

Frequency: 50 Hz

## Motors
- JGB37-520R30-12
- Rated voltage: 12V
- Reduction 1:30
- Encoder: AB dual phase encoder
- Output shaft: 6mm diameter eccentric D-shaped shaft
- Interface: PH2.0-6PIN

## Jetson nano
- 27: SDA
- 28: SCL

## 4EncoderMotor
- 21: SDA
- 22: SCL
- Address: 0x24

## Diagnosi
```bash
sudo i2cdetect -y -r 1
```

# References
1. [4encodermotor](https://docs.m5stack.com/en/module/Module_4EncoderMotor_V1.1)
2. [Jetson Nano](https://developer.nvidia.com/embedded/learn/jetson-nano-2gb-devkit-user-guide)

# Test scripts
```bash
g++ -Wall -o i2c_test i2c_test.cpp -ljetgpio && sudo ./i2c_test
g++ -Wall -o pwm_test pwm_test.cpp -ljetgpio && sudo ./pwm_test
```
