/*
 * sram.c
 *
 * Created: 05.09.2024 19:18:47
 *  Author: eveneha
 */ 
#include "sram.h"
#include "../header/addresses.h"

void SRAM_test(void){
	volatile char *ext_ram = (char *) ADDR_BASE + ADDR_OFFSET_SRAM; // Start address for the SRAM
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
	
    // Immediately check that the correct value was stored
    srand(seed);
	write_loop: 
		for (uint16_t i = 0; i < ADDR_SPACE_SRAM; i++) {
			uint8_t write_value = rand();
			ext_ram[i] = write_value;
			uint8_t retreived_value = ext_ram[i];
			if (retreived_value != write_value) {
				printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, write_value);
				write_errors++;
			}
		}
		
    // Check that no values were changed during or after the write phase
    srand(seed);
	retrieval_loop:
		for (uint16_t i = 0; i < ADDR_SPACE_SRAM; i++) {
			uint8_t read_value = rand();
			uint8_t retreived_value = ext_ram[i];
			if (retreived_value != read_value) {
				printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, read_value);
				retrieval_errors++;
			}
		}
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}


void test_sram_latch(){
	DDRE = 0xFF;
	DDRA = 0xFF;
	PORTA |= (1 << PA0);
	PORTE |= (1 << PE1);


	while (1) {
		PORTA |= (1 << PA0);
		//PORTE |= (1 << PE1);
		_delay_ms(5000);
		PORTE &= ~(1 << PE1);  // Clear PE1 bit to 0 (set low)
		PORTA &= ~(1 << PA0);
		_delay_ms(500);
	}
}