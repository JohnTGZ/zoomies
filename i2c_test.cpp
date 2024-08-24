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
  const int I2C_ADDR = 0x24;

/*  Registers */
	const int MOTOR_PWM_DUTY_REG = 0x20; 	// Sets motor PWM duty (-127 ~ 127)
	const int MOTOR1_ENCODER_REG = 0x30; 	// Motor encoder (Encoder-byte0 + Motor, Encoder-byte1 * 256 + Motor,Encoder-byte2 * 65536 + Motor, Encoder-byte3 * 16777216 )	
	const int MOTOR2_ENCODER_REG = 0x34;

	const int MOTOR_SPEED = 0x40; 		// motor speed (127 ~ 127), Motor encoder increments every 20 ms

	const int MOTOR1_MODE_REG = 0X50;	
	const int MOTOR2_MODE_REG = 0X60;
	const int MOTOR3_MODE_REG = 0X70;
	const int MOTOR4_MODE_REG = 0X80;
	
	const int VIN_CURRENT_FLOAT_REG = 0X90;
	const int VIN_CURRENT_X100_REG = 0xC0;

/* Variables */
int readstat = 0;

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

///* Set motor type */
//int writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_TYPE_REG, 3); 
//printf("Set motor type return: %d\n",writestat);
//usleep(1000000);  // 0.1 s

///* Set motor polarity i.e. direction of rotation */
//writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_POLARITY_REG, 0);
//printf("Set motor polarity return: %d\n",writestat);
//usleep(1000000);

int x = 0;
int mv = -1; // Voltage in millivolts
//int mv_arr[2]; // Voltage in millivolts
//unsigned char enc[16]; // encoder array
int enc[4]; 

unsigned char motor_speed_1[4] = {75, 75, 75, 75}; 
unsigned char motor_speed_3[4] = {25, 25, 25, 25}; 
unsigned char motor_speed_5[4] = {0, 0, 0, 0}; 

while (x<1000) {
	// Read voltage
	printf("Read current");
	mv = i2cReadByteData(i2c_ret, I2C_ADDR, VIN_CURRENT_X100_REG);
//	float v = ((float) mv ) / 1000;
	printf("Current: %d A \n", mv);

	//mv_arr[0] = i2cReadByteData(i2c_ret, I2C_ADDR, ADC_BAT_REG);
	//mv_arr[1] = i2cReadByteData(i2c_ret, I2C_ADDR, ADC_BAT_REG+1);
	//float v_test = (mv_arr[1] << 8) + mv_arr[0];
	//printf("Voltage2: %f mV \n", v_test); jetson 

	// Read motor encoder value
	enc[0] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR1_ENCODER_REG );
	printf("Encoder 1: (%d) \n", enc[0]);
//	enc[1] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG+1 );
//	printf("Encoder 2: (%d) \n", enc[1]);
//	enc[2] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG+2 );
//	printf("Encoder 3: (%d) \n", enc[2]);
//	enc[3] = i2cReadByteData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG+3 );
//	printf("Encoder 4: (%d) \n", enc[3]);

//	printf("Encoder: (%d, %d, %d, %d) \n", enc[0], enc[1], enc[2], enc[3]);


//	readstat = i2cReadArrayData(i2c_ret, I2C_ADDR, MOTOR_ENCODER_TOTAL_REG, enc, 16);
//	if (readstat < 0){
//		printf("Read from motor encoder unsuccessful!\n");	
//	}

//	printf("Encoder: (%d, %d, %d, %d) \n", enc[0], enc[1], enc[2], enc[3]);

//	// Write motor speed value
//	writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG, 16);
//	if (writestat < 0){
//		printf("Write to motor driver unsuccessful!\n");	
//	}	
//	writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG+1, 16);
//	if (writestat < 0){
//		printf("Write to motor driver unsuccessful!\n");	
//	}	
//	writestat = i2cWriteByteData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG+2, 16);
//	if (writestat < 0){
//		printf("Write to motor driver unsuccessful!\n");	
//	}	

//	writestat = i2cWriteArrayData(i2c_ret, I2C_ADDR, MOTOR_FIXED_SPEED_REG, motor_speed_3, 4);
//	if (writestat < 0){
//		printf("Write to motor driver unsuccessful!\n");	
//	}

//	usleep(100000); // 0.1 s
//	usleep(700000); // 0.7 s
	usleep(1000000); // 1 s
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

