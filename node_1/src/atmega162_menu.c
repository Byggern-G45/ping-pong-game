/* atmega162_menu.c -- See atmega162_menu.h for info */

#define ATMEGA162_MENU_IMPORT
#include "../include/atmega162_menu.h"

struct menu {
    uint8_t menu;
    uint8_t submenu;
    uint8_t select;
} menu;

// menus
const char* MENU100 PROGMEM = "Menu 1";
const char* MENU200 PROGMEM = "Menu 2";
const char* MENU300 PROGMEM = "Menu 3";

// submenus of menu 1
const char* MENU101 PROGMEM = "Submenu 1 of menu 1";
const char* MENU102 PROGMEM = "Submenu 2 of menu 1";
const char* MENU103 PROGMEM = "Submenu 3 of menu 1";
// submenus of menu 2
const char* MENU201 PROGMEM = "Submenu 1 of menu 2";
const char* MENU202 PROGMEM = "Submenu 2 of menu 2";
const char* MENU203 PROGMEM = "Submenu 3 of menu 2";
// submenus of menu 3
const char* MENU301 PROGMEM = "Submenu 1 of menu 3";
const char* MENU302 PROGMEM = "Submenu 2 of menu 3";
const char* MENU303 PROGMEM = "Submenu 3 of menu 3";

/*
PGM_P const MENU_TABLE PROGMEM = {
    MENU100, 
    MENU200, 
    MENU300
};
*/
const char** MENU_TABLE PROGMEM = {
    MENU100, 
    MENU200, 
    MENU300
};

const char** SUBMENU_TABLE PROGMEM = {
    MENU101, MENU102, MENU103 // submenus of menu 1
    MENU201, MENU202, MENU203 // submenus of menu 2
    MENU301, MENU302, MENU303 // submenus of menu 3
};

const int8_t* MENU_TABLE_SIZE PROGMEM = {
    3, // menus
    3, // submenus of menu 1
    3, // submenus of menu 2
    3  // submenus of menu 3
};

void* MENU_FUNCTION_TABLE PROGMEM = {
    menu100, menu200, menu300, // menu
    back, menu102, menu103, // submenus of menu 1
    back, menu202, menu203, // submenus of menu 2
    back, menu302, menu303  // submenus of menu 3
};

void menu101() {
    
}

void back() {
    menu.select = menu.previous;
}

uint8_t get_menu_index(uint8_t menu, uint8_t submenu) {
	uint8_t p = 0; //points to menu in table of function pointer 
	for(uint8_t i = 0; i < (menu - 1); i++) {
		p += pgm_read_byte(&MENU_TABLE_SIZE[i + 1]);
	}
	return p + submenu - 1;
}

void menu_loop() {
    uint8_t menu_index = 0;
    while 1 {
        if (joystick.direction == UP) {
            if (--menu.select < 0) {
                menu.select = /*MENU_TABLE_SIZE[]*/ - 1; // wrap around
            }
        } else if (joystick.direction == DOWN) {
            if (++menu.select > /*MENU_TABLE_SIZE[]*/) {
                menu.select = 0; // wrap around
            }
        }

        if (joystick_button_read()) {
            pgm_read_word(&MENU_FUNCTION_TABLE[get_menu_index(menu.menu, menu.submenu)])();
            // call function
            //MENU_FUNCTION_TABLE[menu_index][current_menu.child]();
        }


        
        // else if joystick is neutral
        pgm_read_word(&MENU_TABLE_SIZE[0]); // 3
        pgm_read_word(&MENU_TABLE_SIZE[0]); // 3
        // display menu
        // get input
        // call function
    }
    
}
   