/*
 * GccApplication2.c
 *
 * Created: 16.10.2024 14:04:49
 * Author : eveneha
 */ 



#include <sam.h>
#include "include/header/time.h"
#include "include/header/can.h"
#include "include/header/delay.h"
#include "include/header/servo.h"
#include "include/header/joystick.h"
#include "include/header/adc.h"
#include "include/header/check_score.h"
#include "include/header/solenoid.h"


int main(void)
{
	// test_can();

	SystemInit();
	uart_init(84000000, 9600);
	WDT -> WDT_MR = WDT_MR_WDDIS;
	can_init((CanInit){ .brp = 41, .phase1 = 6, .phase2 = 5, .propag = 1, .smp = 0, .sjw = 4 }, 0);
	init_servo();
	init_adc();
	init_solenoid();
	test_pin();
	while(!init_joystick()){};
	zero_score();
	int x = 0;
	
	
	while(1){
		int joy = read_joystick();
		if (joy < -100) {
			x = x;
		} else {
			x = joy;
		}
		set_servo(x);
		int score = poll_score();
		printf("score: %i , x: %i \n\r", score, x);
		_delay_ms(10);
	}
    
}

