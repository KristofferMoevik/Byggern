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
#include "include/header/motor.h"


int main(void)
{
	SystemInit();
	uart_init(84000000, 9600);
	printf("jhsfdhsfd \n\r");
	WDT -> WDT_MR = WDT_MR_WDDIS;
	can_init((CanInit){ .brp = 41, .phase1 = 6, .phase2 = 5, .propag = 1, .smp = 0, .sjw = 4 }, 0);
	init_servo();
	init_adc();
	init_solenoid();
	
	test_encoder();
}

