
#define ATMEGA162_OLED_IMPORT
#include "../include/atmega162_oled.h"

volatile char* oled_command = 0x1000;
volatile char* oled_data = 0x1200;


void write_c(uint8_t command){
    oled_command[0] = command;
}

void write_d(uint8_t data){
    oled_data[0] = data;
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
    write_c(0x02);
    write_c(0xdb); //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad); //master configuration
    write_c(0x00);
    write_c(0xa4); //out follows RAM content
    write_c(0xa6); //set normal display
    write_c(0xaf); // display on

    //Print an arrow
	while(1){
		write_d(0b00011000);
		write_d(0b00011000);
		write_d(0b01111110);
		write_d(0b00111100);
		write_d(0b00011000);
	}
}

/*void oled_addressing_mode(mode) {
    write_c(0x20);
    write_c(mode);
}*/

void oled_reset() {

}

void oled_home() {

}

void oled_goto_line(uint8_t line) {

}

void oled_goto_column(uint8_t column) {

}

void oled_clear_line(uint8_t line) {

}

void oled__pos(uint8_t row_column){

}

void oled_print(char* character) {
    
}



