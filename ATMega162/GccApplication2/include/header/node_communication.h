/*
 * node_communication.h
 *
 * Created: 13.11.2024 15:23:42
 *  Author: eveneha
 */ 


#ifndef NODE_COMMUNICATION_H_
#define NODE_COMMUNICATION_H_

typedef struct
{
	int joystick_up_down;
	int joystick_left_right;
	int shoot_button;
	int slider_right;
} commands;

int send_score_to_node1(int score){
	CanMsg m; 
	m.id = 2;
	m.length = 1;
	m.byte[0] = score;
	can_tx(m);
	return 1;
}

commands get_commands_from_node_1(){
	CanMsg msg_recieve;
	int success = can_rx(&msg_recieve);
	float max_value = 255;
	commands recieved_commands;
	recieved_commands.joystick_up_down = msg_recieve.byte[0];
	recieved_commands.joystick_left_right = msg_recieve.byte[1]; 
	recieved_commands.shoot_button = msg_recieve.byte[2];
	recieved_commands.slider_right = msg_recieve.byte[3];
	
	if (success){
		//printf("commands: %i, %i, %i, %i \n\r", recieved_commands.joystick_up_down, recieved_commands.joystick_left_right, recieved_commands.shoot_button, recieved_commands.slider_right);
	}
	
	return recieved_commands;
}



#endif /* NODE_COMMUNICATION_H_ */