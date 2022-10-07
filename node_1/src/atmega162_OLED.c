
#define ATMEGA162_OLED_IMPORT
#include "../include/atmega162_oled.h"


#define OLED_CMD_ADDRESS (volatile char*)0x1000
#define OLED_DATA_ADDRESS (volatile char*)0x1200

static FILE mystdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);

typedef enum{horizontal, vertical, page} memory_addressing_mode_t;

void write_c(uint8_t command){
    *OLED_CMD_ADDRESS = (char)command;
}

void write_d(uint8_t data){
    *OLED_DATA_ADDRESS = (char)data;
}

void oled_init() {
    write_c(0xae); //display off
    write_c(0xa1); //segment remap
    write_c(0xda); //common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8); //common output scan direction:com63~com0
    write_c(0xa8); //multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5); //display divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81); //contrast control
    write_c(0x50);
    write_c(0xd9); //set pre-charge period
    write_c(0x21);
    write_c(0x20); //Set Memory Addressing Mode
    write_c(horizontal);
    write_c(0xdb); //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad); //master configuration
    write_c(0x00);
    write_c(0xa4); //out follows RAM content
    write_c(0xa6); //set normal display
	write_c(0xaf); // display on
}

void oled_addressing_mode(memory_addressing_mode_t mode) {
    write_c(0x20);
    write_c(mode);
}

void oled_reset() {
	for (int line = 0 ; line < 8 ; line++) {
		oled_clear_line(line);
	}
	oled_pos(0, 0);
}

void oled_home() {
	oled_pos(0, 0);
}

void oled_goto_line(uint8_t line) {
	oled_addressing_mode(page);
	//There are 7 lines/pages. chose which one with [0xB0 - 0xB7]
	write_c(0xB0 + line);
	
	oled_addressing_mode(horizontal);
}

void oled_goto_column(uint8_t column) {
	oled_addressing_mode(page);
	//The low column chooses a one of the 16 columns in the block
	int low_column = column % 16;
	//The high column chooses a 16 bit block of the 128 bit columns.
	int high_column = column/16;
	
	//Set lower start column
	write_c(low_column);
	write_c(0x10 + high_column);
	
	oled_addressing_mode(horizontal);
}

void oled_clear_line(uint8_t line) {
	for (int column = 0 ; column < 128 ; column++) {
		oled_pos(line, column);
		write_d(0x00);
	}
	oled_goto_line(line);
}

void oled_pos(uint8_t line, uint8_t column){
	oled_goto_line(line);
	oled_goto_column(column);
}

void oled_print(char* character) {
    
}


int oled_put_char(unsigned char c){
	uint8_t printChar = c-32;
	
	for (int i=0; i < fontSize; i++) {
		write_data(pgm_read_word(&font_8x8[printChar][i]));
		position.col += fontSize;
		oled_is_out_of_bounds();
	}
	
	return 0;



