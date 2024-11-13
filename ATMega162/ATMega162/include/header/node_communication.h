/*
 * node_communication.h
 *
 * Created: 13.11.2024 14:32:49
 *  Author: eveneha
 */ 


#ifndef NODE_COMMUNICATION_H_
#define NODE_COMMUNICATION_H_

void send_commands_to_node_2_can(){
	adc_channels adc_values = read_channels();
	int joystick_x_value = adc_values.joystick_left_right;
	int joystick_y_value = adc_values.joystick_up_down;
	int shoot_button = adc_values.shoot_button;
	int slider_value = adc_values.slider_right;
	
	can_message msg_send;
	msg_send.id_lower =  0b00000000;
	msg_send.id_higher = 0b00000000;
	msg_send.message_length_bytes = 4;
	msg_send.data[0] = joystick_x_value;
	msg_send.data[1] = joystick_y_value;
	msg_send.data[2] = shoot_button;
	msg_send.data[3] = slider_value;
	
	//printf("joystick sent x %i , y %i , shoot_button: %i, slider: %i \n\r", joystick_x_value, joystick_y_value, shoot_button, slider_value);
	
	can_send_message(msg_send);
}




#endif /* NODE_COMMUNICATION_H_ */