/*
 * external_memory_bus.h
 *
 * Created: 02.10.2024 11:05:46
 *  Author: eveneha
 */ 


#ifndef EXTERNAL_MEMORY_BUS_H_
#define EXTERNAL_MEMORY_BUS_H_

void init_external_memory_bus(){
	MCUCR = (1 << SRE);
	EMCUCR = (1 << SRW01);
	SFIOR = (1 << XMM2);
}



#endif /* EXTERNAL_MEMORY_BUS_H_ */