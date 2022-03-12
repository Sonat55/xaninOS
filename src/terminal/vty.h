

#pragma once

#include <headers/macros.h>
#include <headers/colors.h>
#include <keyboard/keyMap.h>
#include <lib/stdiox.h>
#include <lib/string.h>

#define SCREEN_WIDTH 28
#define SCREEN_HEIGHT 80
#define SCREEN_RESOLUTION (25 * 80)

enum screen_macros
{
    VGA_WIDTH = 80,
    VGA_HEIGHT = 28
};

#define VGA_TEXT_MEMORY 0xb8000

uint16_t* cursor = (uint16_t*)VGA_TEXT_MEMORY + (4*80);


struct key_info_t
{
    uint8_t scan_code;
    char character;
    bool is_shift;
    bool is_ctrl;
    bool is_caps;
    bool is_bspc;
};

typedef struct key_info_t key_info_t;
key_info_t key_info;

struct screen_t
{
    uint16_t** cursor;
    uint8_t x;
    uint8_t y;

};


typedef struct screen_t screen_t;
screen_t screen;

uint16_t* screen_buffer[28];
uint8_t index = 0x0;


static uint8_t y,x;
void setTerminal();
void set_x(uint8_t newVal);
void set_y(uint8_t newVal);
void add_x(uint8_t xadd);
void add_y(uint8_t yadd);
void screen_init(void);

bool no_enter = false;

bool arrows_navigate = false;
bool terminalAppExit = false;
bool cursor_show = false;
char selected_character; 

#define putchar_at_cursor(x) *cursor = (uint16_t)(x | ((black << 4) | white) << 8)

#define remap_key(from, to)\
        if(key == from)\
            key = to


#define key_remap(from, to)\
        if(key_info.character == from)\
            key_info.character = to

bool caps_on = false;
bool print_off = false;
bool key_released = false;
bool lshift_pressed = false;

bool in_graphic_mode = false;

typedef char (*keyboard_handle_input)(char);

keyboard_handle_input keyboard_handle[50];

char keyboard_default_handler(char);

char program_name[40];
char program_parameters[40];
void terminal(void);