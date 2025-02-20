

#include <lib/stdiox.h>
#include <xin_fs/xin.c>
#include <lib/memory.h>
#include <terminal/interpreter.h>
#include <lib/exit_process.h>
#include <lib/string.h>




void note_input(xchar x)
{

    static uint8_t selected_character;
    

    if(KeyInfo.scan_code == F4_KEY || KeyInfo.scan_code == ESC)
    {
        app_exited = true;
    }

    else if(x.scan_code == BSPC)
    {       
        
        if(!Screen.x && !Screen.y)
            return;

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) + (((black << 4) | white) << 8));

        if(!Screen.x)
        {
            Screen.y--;
            Screen.x = 79;
            return;
        }

        Screen.x--;

        Screen.cursor[Screen.y][Screen.x] = 0x20;
        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) + (((white << 4) | black) << 8));

        KeyInfo.is_bspc = false;
        return;
        letters_refresh(&Screen.cursor[Screen.y][Screen.x]);
    
    }

    else if(x.scan_code == ARROW_UP)
    {

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((black << 4) | white) << 8));
        
        if((uint32_t)&Screen.cursor[Screen.y - 1][Screen.x] >= VGA_TEXT_MEMORY)
            Screen.y--;

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((white << 4) | black) << 8));

    }

    else if(x.scan_code == ARROW_DOWN)
    {

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((black << 4) | white) << 8));
        
        if((uint32_t)&Screen.cursor[Screen.y + 1][Screen.x] <= VGA_TEXT_MEMORY + VGA_SCREEN_RESOLUTION)
            Screen.y++;

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((white << 4) | black) << 8));

    }

    else if(x.scan_code == ARROW_RIGHT)
    {

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((black << 4) | white) << 8));

        Screen.x++;

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((white << 4) | black) << 8));


        if(Screen.x == 80)
        {
            Screen.x = 0x0;
            Screen.y++;
        }

    }

    else if(x.scan_code ==  ARROW_LEFT)
    {

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((black << 4) | white) << 8));
    
        if(Screen.x == 0)
        {
            Screen.x = 80;
            Screen.y--;
        }


        Screen.x--;

        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((white << 4) | black) << 8));


    }

    else if(x.scan_code == ENTER)
    {
        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((black << 4) | white) << 8));
        xprintf("\r\n");
        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((white << 4) | white) << 8));
    }

    else if(x.scan_code == TAB_KEY)
    {
        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((black << 4) | white) << 8));
        Screen.x += 3;
        Screen.cursor[Screen.y][Screen.x] = (uint16_t)((char)(Screen.cursor[Screen.y][Screen.x]) | (((white << 4) | black) << 8));
    }

    else
    {
        if(x.character)
        {
            char character_saved_tmp = (char)Screen.cursor[Screen.y][Screen.x];
            xprintf("%c", getchar());
            letters_refresh_add(&Screen.cursor[Screen.y][Screen.x], character_saved_tmp);
        }
    }  


}

void xin_note(char* file_name)
{
    screen_clear();
    use_backspace = true;

    xin_entry* xin_file = fopen(file_name, "rw");

    if(xin_file == nullptr)
    {
        xprintf("Could not open file: %s\n", file_name);

        while(KeyInfo.scan_code != ENTER);

    }
        
    else
    {

        char* data_pointer = xin_file->starting_sector * SECTOR_SIZE;

        uint16_t* bruh_moment = VGA_TEXT_MEMORY;
        
        for(int i = 0;  i < (VGA_SCREEN_RESOLUTION / 2); i++)
            bruh_moment[i] = (uint16_t) (data_pointer[i] + (((black << 4) | white) << 8));
        

        while(!app_exited)note_input(inputg());

        uint32_t file_data_counter = 0x0;

        data_pointer = (char*)(xin_file->starting_sector * SECTOR_SIZE);

        //if(xin_file->os_specific != XIN_READ_ONLY)
        {

            uint16_t* screen_ptr = (uint16_t*)VGA_TEXT_MEMORY;

            for(int i = 0; i < VGA_SCREEN_RESOLUTION; i++, screen_ptr++)
            {
                fseek(xin_file, i);
                write(xin_file, (char*)screen_ptr, 1);
            }

            xin_file->entry_size = file_data_counter;
        }

    }


    keyboard_handle = nullptr;
    return;
}
