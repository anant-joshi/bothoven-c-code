#ifndef LINE_FOLLOWING_HEADER
#define LINE_FOLLOWING_HEADER 

#include "motor_movement.h"
#include "analog_to_digital.h"
	#ifndef BLACK_THRESHOLD
	#define BLACK_THRESHOLD 0x14
	#endif

	#ifndef NUDGE_AHEAD_DELAY
	#define NUDGE_AHEAD_DELAY 10
	#endif

char bot_is_on_node(){
	left = ADC_Conversion(3);
	right = ADC_Conversion(2);
	centre = ADC_Conversion(1);
	return (left > BLACK_THRESHOLD && right > BLACK_THRESHOLD && centre > BLACK_THRESHOLD);
}

char bot_is_on_line(){
	left = ADC_Conversion(3);
	right = ADC_Conversion(2);
	centre = ADC_Conversion(1);
	return (left < BLACK_THRESHOLD && centre > BLACK_THRESHOLD && right < BLACK_THRESHOLD);
}

char bot_is_veering_left(){
	left = ADC_Conversion(3);
	right = ADC_Conversion(2);
	centre = ADC_Conversion(1);
	return (left < BLACK_THRESHOLD && right > BLACK_THRESHOLD);
	//(experimental): centre intentionally not specified to improve responsiveness
}

char bot_is_veering_right(){
	left = ADC_Conversion(3);
	right = ADC_Conversion(2);
	centre = ADC_Conversion(1);
	return (left > BLACK_THRESHOLD && right < BLACK_THRESHOLD);
	//(experimental): centre intentionally not specified to improve responsiveness
}

void follow_black_line(){
	while(!bot_is_on_node()){
		if(bot_is_on_line()){
			forward();
			velocity(150,150);
		}else if(bot_is_veering_left()){
			forward()
			velocity(130,50);
		}else if(bot_is_veering_right()){
			forward();
			velocity(50,130);
		}
		_delay_ms(2);	
	}
	velocity(0,0);
}

void nudge_ahead(){
	forward();
	velocity(150,150);
	_delay_ms(NUDGE_AHEAD_DELAY);
	velocity(0,0);
}

void turn_to_path(int path_number){
	int count = path_number;
	int flag = 0;
	if(path_number < 0){
		while(count != 0){
			right();
			if(bot_is_on_line()){
				if(flag == 0) count++;
				flag = 1;
			}else{
				flag = 0;
			}
			_delay_ms(1);
		}
	}else{
		while(count != 0){
			left();
			if(bot_is_on_line()){
				if(flag == 0)	count--;
				flag = 1;
			}else{
				flag = 0;
			}
			_delay_ms(1);
		}
	}
	stop();
}

#endif