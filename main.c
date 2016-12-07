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
/*
	All imports here
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int grid_of_nodes[48][48];

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

void motion_pin_config (void)
{
 DDRA = DDRA | 0x0F; //set direction of the PORTA 3 to PORTA 0 pins as output
 PORTA = PORTA & 0xF0; // set initial value of the PORTA 3 to PORTA 0 pins to logic 0
 DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
 PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM
}

//Function used for setting motor's direction
void motion_set (unsigned char Direction)
{
 unsigned char PortARestore = 0;

 Direction &= 0x0F; 			// removing upper nibbel as it is not needed
 PortARestore = PORTA; 			// reading the PORTA's original status
 PortARestore &= 0xF0; 			// setting lower direction nibbel to 0
 PortARestore |= Direction; 	// adding lower nibbel for direction command and restoring the PORTA status
 PORTA = PortARestore; 			// setting the command to the port
}


void forward (void) //both wheels forward
{
  motion_set(0x06);
}

void back (void) //both wheels backward
{
  motion_set(0x09);
}

void left (void) //Left wheel backward, Right wheel forward
{
  motion_set(0x05);
}

void right (void) //Left wheel forward, Right wheel backward
{
  motion_set(0x0A);
}

void soft_left (void) //Left wheel stationary, Right wheel forward
{
 motion_set(0x04);
}

void soft_right (void) //Left wheel forward, Right wheel is stationary
{
 motion_set(0x02);
}

void soft_left_2 (void) //Left wheel backward, right wheel stationary
{
 motion_set(0x01);
}

void soft_right_2 (void) //Left wheel stationary, Right wheel backward
{
 motion_set(0x08);
}

void stop (void) //hard stop
{
  motion_set(0x00);
}

/*
	End definitions for motion
*/

/*
	Start ADC definitions
*/
void adc_pin_config (void)
{
 DDRF = 0x00; 
 PORTF = 0x00;
 DDRK = 0x00;
 PORTK = 0x00;
}

void adc_init()
{
	ADCSRA = 0x00;
	ADCSRB = 0x00;		//MUX5 = 0
	ADMUX = 0x20;		//Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
	ACSR = 0x80;
	ADCSRA = 0x86;		//ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0
}

/*
	ACD CH.	PORT	Sensor
			  0			PF0		Battery Voltage
			  1			PF1		White line sensor 3
			  2			PF2		White line sensor 2
			  3			PF3		White line sensor 1
			  4			PF4		IR Proximity analog sensor 1*****
			  5			PF5		IR Proximity analog sensor 2*****
			  6			PF6		IR Proximity analog sensor 3*****
			  7			PF7		IR Proximity analog sensor 4*****
			  8			PK0		IR Proximity analog sensor 5
			  9			PK1		Sharp IR range sensor 1
			  10		PK2		Sharp IR range sensor 2
			  11		PK3		Sharp IR range sensor 3
			  12		PK4		Sharp IR range sensor 4
			  13		PK5		Sharp IR range sensor 5
			  14		PK6		Servo Pod 1
			  15		PK7		Servo Pod 2
*/

unsigned char ADC_Conversion(unsigned char Ch) 
{
	unsigned char a;
	if(Ch>7)
	{
		ADCSRB = 0x08;
	}
	Ch = Ch & 0x07;  			
	ADMUX= 0x20| Ch;	   		
	ADCSRA = ADCSRA | 0x40;		//Set start conversion bit
	while((ADCSRA&0x10)==0);	//Wait for conversion to complete
	a=ADCH;
	ADCSRA = ADCSRA|0x10; //clear ADIF (ADC Interrupt Flag) by writing 1 to it
	ADCSRB = 0x00;
	return a;
}

/*
	End ADC definitions
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

void add_edge(int i, int j, int weight){
	grid_of_nodes[i][j] = grid_of_nodes[j][i] = weight; 
}

void remove_edge(int i, int j){
	grid_of_nodes[i][j] = grid_of_nodes[j][i] = 0;
}

void add_edges_to_graph(){
	add_edge(0,1,1);
	add_edge(1,2,1);
	add_edge(2,3,1);
	add_edge(3,4,1);
	add_edge(4,5,1);
	add_edge(5,6,1);
	add_edge(6,7,1);
	add_edge(7,8,1);
	add_edge(8,9,1);
	add_edge(9,10,1);
	add_edge(10,11,1);	
	add_edge(11,12,1);
	add_edge(12,13,1);

	add_edge(13,14,1);
	add_edge(14,15,1);
	add_edge(15,16,1);
	add_edge(16,17,1);
	add_edge(17,18,1);
	add_edge(18,19,1);
	add_edge(19,20,1);
	add_edge(20,21,1);
	add_edge(21,22,1);
	add_edge(22,23,1);
	add_edge(23,1,1);
	add_edge(2,26,1);
	add_edge(2,25,1);

	add_edge(25,26,1);
	add_edge(6,28,1);
	add_edge(6,29,1);
	add_edge(10,31,1);
	add_edge(10,32,1);
	add_edge(31,32,1);
	add_edge(14,34,1);
	add_edge(14,35,1);
	add_edge(18,37,1);
	add_edge(18,38,1);
	add_edge(37,38,1);
	add_edge(22,40,1);
	add_edge(22,41,1);

	add_edge(24,25,1);
	add_edge(24,41,1);
	add_edge(27,26,1);
	add_edge(27,28,1);
	add_edge(30,29,1);
	add_edge(30,31,1);
	add_edge(33,32,1);
	add_edge(33,34,1);
	add_edge(36,35,1);
	add_edge(36,37,1);
	add_edge(39,38,1);
	add_edge(39,40,1);
	add_edge(24,42,1);

	add_edge(42,43,1);
	add_edge(43,27,1);
	add_edge(30,44,1);
	add_edge(44,45,1);
	add_edge(45,33,1);
	add_edge(36,46,1);
	add_edge(46,47,1);
	add_edge(47,39,1);
	add_edge(39,24,2);
	add_edge(27,30,2);
	add_edge(33,36,2);
}

void init_grid_of_nodes(){
	int i,j;
	for(i = 0; i< NUM_NODES; i++)
		for(j = 0; j < NUM_NODES; j++)
			grid_of_nodes[i][j] = 0;
	add_edges_to_graph();
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

