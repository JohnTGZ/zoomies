/* Usage example of the JETGPIO library
 * Compile with: g++ -Wall -o i2c_test i2c_test.cpp -ljetgpio && sudo ./i2c_test
 * Execute with: sudo ./i2c_test
 */

#include <iostream>
#include <unistd.h>
#include <jetgpio.h>

int setMotorSpeed( int* motor_speeds){
}

int main(int argc, char *argv[])
{
  int Init;

/*  I2C address of motor driver */
  const int I2C_ADDR = 0x34;

/*  Registers */
  const int ADC_BAT_REG = 0; // Voltage address
  const int MOTOR_TYPE_REG = 0x20; // Sets motor type
  const int MOTOR_ENCODER_POLARITY_REG = 0x21; // sets encode direction polarity
  const int MOTOR_FIXED_PWM_REG = 0x31;		// Fixed PWM control (open loop control)
  const int MOTOR_FIXED_SPEED_REG = 0x51;	// Fixed speed control, it is closed loop control
  const int MOTOR_ENCODER_TOTAL_REG = 0x60;	// Total pulse value of 4 encode motors
  
  const int MOTOR_TYPE_WITHOUT_ENCODER = 0; 	// Magnetic ring generates 44 pulses per revolution, combined with a gear reduction ratio of 90
  const int MOTOR_TYPE_TT = 1;			// TT encoder motor
  const int MOTOR_TYPE_N20 = 2;			// N20 encoder motor
  const int MOTOR_TYPE_JGB37_520_12V_110RPM = 3; // Magnetic ring generates 44 pulses per revolution, combined with a gear reduction ratio of 90

/* Initialize GPIO */
Init = gpioInitialise();

if (Init < 0)
{
	/* jetgpio initialisation failed */
	printf("Jetgpio initialisation failed. Error code:  %d\n", Init);
	exit(Init);
}
else
{
	/* jetgpio initialised okay*/
	printf("Jetgpio initialisation OK. Return code:  %d\n", Init);
}	

/* Opening the connection to the I2C slave */
int i2c_ret = i2cOpen(0,0);

if (i2c_ret >=  0)
{
	/* Opening I2C port OK*/
	printf("Open I2C port OK. Return code:  %d\n", i2c_ret);
	printf("i2c_ret number handler:  %d\n", i2c_ret);
}
else
{
	/* Problems opening I2C port*/
	printf("Open I2C port failed. Quitting i2c_ret Error code:  %d\n", i2c_ret);
}
std::cout << "before writing" << std::endl;

/* Set motor type */
int writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_TYPE_REG, MOTOR_TYPE_TT); 
printf("write return: %d\n",writestat);
usleep(100000);  // 0.1 s

/* Set motor polarity i.e. direction of rotation */
writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_POLARITY_REG, 0x01);
printf("write return: %d\n",writestat);
usleep(100000);

int x = 0;
int mv = 0; // Voltage in millivolts
int mv_arr[2]; // Voltage in millivolts
int enc[4]; 

int motor_speed_1[4] = {50, 50, 50, 50}; 
int motor_speed_2[4] = {-50, -50, -50, -50}; 
int motor_speed_3[4] = {5, 5, 5, 5}; 
int motor_speed_4[4] = {-2, -2, -2, -2}; 
int motor_speed_5[4] = {0, 0, 0, 0}; 

std::cout << "before loop" << std::endl;

while (x<1000) {
	// Read voltage
	mv = i2cReadWordData(i2c_ret, I2C_ADDR, ADC_BAT_REG);
	float v = ((float) mv ) / 1000;
	printf("Voltage: %f V \n", v);

	//mv_arr[0] = i2cReadByteData(i2c_ret, I2C_ADDR, ADC_BAT_REG);
	//mv_arr[1] = i2cReadByteData(i2c_ret, I2C_ADDR, ADC_BAT_REG+1);
	//float v_test = (mv_arr[1] << 8) + mv_arr[0];
	//printf("Voltage2: %f mV \n", v_test); jetson 

	// Read motor encoder value
	enc[0] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG);
	enc[1] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG+1);
	enc[2] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG+2);
	enc[3] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG+3);

	printf("Encoder: (%d, %d, %d, %d) \n", enc[0], enc[1], enc[2], enc[3]);

	// Write motor speed value
	
	writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG, motor_speed_3[0]);
	writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG+1, motor_speed_3[1]);
	writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG+2, motor_speed_3[2]);
	writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG+3, motor_speed_3[3]);

	usleep(100000);
	x++;
  }

  /* Closing i2c connection */
  int i2cstat = i2cClose(i2c_ret);

  if (i2cstat >=  0)
    {
      /* I2C port closed OK*/
      printf("Closing I2C port OK. Return code:  %d\n", i2cstat);
    }
  else
    {
      /* Not possible to close I2C port */
      printf("Closing I2C port failed. Quitting i2c_0 thread Error code:  %d\n", i2cstat);
    }

  /* Terminating library */
  gpioTerminate();
  exit(0);
	
}

