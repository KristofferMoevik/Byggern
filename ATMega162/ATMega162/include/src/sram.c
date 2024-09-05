/*
 * sram.c
 *
 * Created: 05.09.2024 19:18:47
 *  Author: eveneha
 */ 

#include "sram.h"

// Function to reverse bits in a 8-bit value
uint8_t reverse_bits(uint8_t num) {
    uint8_t rev = 0;
    for (uint8_t i = 0; i < 8; i++) {
        rev <<= 1;
        rev |= (num & 1);
        num >>= 1;
    }
    return rev;
}


void SRAM_test(void) {
    volatile char *ext_ram = (char *) 0x1800;  // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");

    uint16_t seed = rand();
    srand(seed);

    // Write phase: immediately check that the correct value was stored
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t reversed_index = reverse_bits(i);  // Reverse the address bits
        uint8_t some_value = rand();
        ext_ram[reversed_index] = some_value;
        uint8_t retreived_value = ext_ram[reversed_index];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", reversed_index, retreived_value, some_value);
            write_errors++;
        }
    }

    // Retrieval phase: check that no values were changed
    srand(seed);  // Reset the PRNG to the state it had before the write phase
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t reversed_index = reverse_bits(i);  // Reverse the address bits
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[reversed_index];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", reversed_index, retreived_value, some_value);
            retrieval_errors++;
        }
    }

    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}


void test_sram_latch(){
	DDRE = 0xFF;
	DDRA = 0xFF;
	PORTA |= (1 << PA0);
	PORTE |= (1 << PE1); // Enable

	

	while (1) {
		
		PORTA |= (1 << PA0);
		//PORTE |= (1 << PE1);
		_delay_ms(5000);
		PORTE &= ~(1 << PE1);  // Clear PE1 bit to 0 (set low)
		PORTA &= ~(1 << PA0);
		_delay_ms(500);
	}
}