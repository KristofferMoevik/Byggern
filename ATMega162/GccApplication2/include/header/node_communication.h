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
	int position_setpoint;
	int shoot_button;
	int servo_setpoint;
	int reset_score;
} commands;

int send_score_to_node1(int score){
	CanMsg m; 
	m.id = 3;
	m.length = 1;
	m.byte[0] = score;
	can_tx(m);
	return 1;
}

commands get_commands_from_node_1(){
	CanMsg msg_recieve;
	int success = can_rx(&msg_recieve);
	printf("msg_id: %i ", msg_recieve.id);
	commands recieved_commands;
	if (msg_recieve.id == 0) {
		float max_value = 255;
		
		recieved_commands.reset_score = 0;
	
		float position_setpoint = msg_recieve.byte[3];
		position_setpoint = (position_setpoint/255.0) * 100.0;
		recieved_commands.position_setpoint = position_setpoint;
	
		float servo_setpoint = msg_recieve.byte[1];
		servo_setpoint = ((servo_setpoint/255) * 200) - 100;
		recieved_commands.servo_setpoint = servo_setpoint;
	
		float shoot_button = msg_recieve.byte[2];
		if (shoot_button > 200){
			recieved_commands.shoot_button = 1;
		} 
		else {
			recieved_commands.shoot_button = 0;	
		}
	
		if (success){
			//printf("commands: %i, %i, %i, %i \n\r", msg_recieve.byte[0], msg_recieve.byte[1], msg_recieve.byte[2], msg_recieve.byte[3]);
		}
	}
	if (msg_recieve.id == 3){
		printf("score reset");
		recieved_commands.reset_score = 1;
	}
	
	return recieved_commands;
}



#endif /* NODE_COMMUNICATION_H_ */