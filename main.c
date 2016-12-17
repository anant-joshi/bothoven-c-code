/*
 * pathfinder.c
 *
 * Created: 04-12-2016 23:32:28
 * Author : anant_000
 */ 
/*
	All defined macros here
*/
#define F_CPU 14746500L
#define NUM_NODES 48
#define BUF_SIZE 100
/*
	All imports here
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
	Start Definitions for buzzer
*/
void buzzer_pin_config (void)
{
	DDRC = DDRC | 0x08;		//Setting PORTC 3 as output
	PORTC = PORTC & 0xF7;		//Setting PORTC 3 logic low to turnoff buzzer
}

void buzzer_on (void)
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore | 0x08;
	PORTC = port_restore;
}

void buzzer_off (void)
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore & 0xF7;
	PORTC = port_restore;
}

/*
	End definitions for buzzer
*/


/*
	Start definitons for motion
*/



/*
	Start SHARP, proximity sensors
*/

//MOSFET switch port configuration
void MOSFET_switch_config (void)
{
 DDRH = DDRH | 0x0C; //make PORTH 3 and PORTH 1 pins as output
 PORTH = PORTH & 0xF3; //set PORTH 3 and PORTH 1 pins to 0

 DDRG = DDRG | 0x04; //make PORTG 2 pin as output
 PORTG = PORTG & 0xFB; //set PORTG 2 pin to 0
}

void turn_on_all_proxy_sensors (void) // turn on Sharp 2, 3, 4, red LED of the white line sensors
									  // Sharp 1, 5 and IR proximity sensor
{
 PORTH = PORTH & 0xF3; //set PORTH 3 and PORTH 1 pins to 0
 PORTG = PORTG & 0xFB; //set PORTG 2 pin to 0
}

void turn_off_all_proxy_sensors (void) // turn off Sharp 2, 3, 4, red LED of the white line sensors
									  // Sharp 1, 5 and IR proximity sensor
{
 PORTH = PORTH | 0x0C; //set PORTH 3 and PORTH 1 pins to 1
 PORTG = PORTG | 0x04; //set PORTG 2 pin to 1
}

unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading)
{
	float distance;
	unsigned int distanceInt;
	distance = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
	distanceInt = (int)distance;
	if(distanceInt>800)
	{
		distanceInt=800;
	}
	return distanceInt;
}

/*
	End SHARP, proximity sensors
*/

/*
	Initialize ports
*/
void port_init (void)
{
	buzzer_pin_config();
	motion_pin_config();
	adc_pin_config();
}

/*
	Initialize devices
*/
void init_devices (void)
{
	cli(); //Clears the global interrupts
	port_init();
	sei(); //Enables the global interrupts
}


/*
	Function Name:	is_a_node
	Input:			No parameters, ADC Input from white line sensors
	Output:			Returns 1 if the current position is a node, zero otherwise
	Logic:			If the central, and either of the left or right white line sensors
					give a false value, then the current position is a node
	Example Call:	is_a_node() (Generally in a conditional statement)	
*/

char is_a_node(){
	left_white_line = ADC_Conversion(3);
	centre_white_line = ADC_Conversion(2);
	right_white_line = ADC_Conversion(1);

	if(centre_white_line > 0x28 && (right_white_line > 0x28 || left_white_line > 0x28)){
		return 1;
	}else{
		return 0;
	}
}

/*
	Function Name:	follow_line
	Input:			No parameters, ADC input from the White line sensors
	Output: 		None. (Moves motors)
	Logic:			If the central white line sensor is high, then the robot is on the black line
					if the left sensor is high, then the robot must curve left
					if the right sensor is high, then the robot must curve right
	Example Call:	follow_line() (It is just an imperative statement)
*/
void follow_line(){
	Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
	Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
	Right_white_line = ADC_Conversion(1);	//Getting data of Right WL Sensor				

	if(Center_white_line > 0x28)
	{
			forward();
			velocity(150,150);
	}

		if((Left_white_line > 0x28))
		{
			forward();
			velocity(130,50);
		}

		if((Right_white_line > 0x28))
		{
			forward();
			velocity(50,130);
		}

		// TODO: Check later
		// if(Center_white_line>0x28 && Left_white_line>0x28 && Right_white_line>0x28)
		// {
		// 	forward();
		// 	velocity(0,0);
		// }
}


int main(void)
{
    while (1){
		buzzer_on()
		_delay_ms(1000);
		buzzer_off();
		_delay_ms(1000);
    }
}

