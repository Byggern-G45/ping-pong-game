/* atmega162_menu.c -- See atmega162_menu.h for info */

#define ATMEGA162_MENU_IMPORT
#include "../include/atmega162_menu.h"

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

const uint8_t* MENU_TABLE_SIZE PROGMEM = {
    3, // menus
    3, // submenus of menu 1
    3, // submenus of menu 2
    3  // submenus of menu 3
};

void* MENU_FUNCTION_TABLE PROGMEM = {
    menu101, menu102, menu103, // submenus of menu 1
    menu201, menu202, menu203, // submenus of menu 2
    menu301, menu302, menu303  // submenus of menu 3
};

void menu101() {
    
}

void menu_loop() {
    pgm_read_word(&MENU_TABLE_SIZE[0]); // 3
}
   