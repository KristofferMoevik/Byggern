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
#include "include/header/node_communication.h"
#include "include/header/position_regulator.h"
#include "include/header/tests.h"


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
	init_motor();
	init_position_regulator();
	init_encoder();
	//test_servo_pwm();
	//test_motor();
	//test_solenoid();
	
	while (1)
	{
		// Get score
		int score = poll_score();
		
		printf("score: %i \n\r ", score);
		send_score_to_node1(score);
		commands recieved_commands = get_commands_from_node_1();
		
		if (recieved_commands.reset_score) {
			send_score_to_node1(score);
			printf("zeroed");
			zero_score();
		}
		else {
			// Positon control
			float position_setpoint = recieved_commands.position_setpoint;
			float position = read_encoder_position();
			float output = position_regulator(position_setpoint, position);
			printf("position: %f, setpoint: %f, output: %f \n\r", position, position_setpoint, output);
			set_motor_speed(output);
		
			// Set servo
			float servo_setpoint = recieved_commands.servo_setpoint;
			set_servo(servo_setpoint);
		
			// Shoot solenoid
			int shoot = recieved_commands.shoot_button;
			shoot_solenoid(shoot);
		}
	}
}

