
#include <terminal/vty.h>

void keyboard_driver(uint8_t scanCode)
{

    KeyInfo.scan_code = scanCode;


    switch(KeyInfo.scan_code)
    {
        case LSHIFT: {KeyInfo.is_shift = true; return;}
        case LSHIFT_RELEASE: {KeyInfo.is_shift = false; break;}
        case BSPC: 
        {
            
            

            KeyInfo.is_bspc = true; 
            
            if((char)Screen.cursor[Screen.y][Screen.x - 1] == character_blocked && character_blocked != '\0')
            {
                return;
            }


            if(!Screen.x)
            {
                Screen.y--;
                Screen.x = 79;
            }

            Screen.x--;

            if(index)
                index--;

            comBuf[index] = '\0';
            Screen.cursor[Screen.y][Screen.x] = '\0';

            
            return;
        }
        
        case BSPC_RELEASE: {KeyInfo.is_bspc = false; return;}
        case CAPS: 
        {
            KeyInfo.is_caps = KeyInfo.is_caps  ?  false : true; 
        }

        case ARROW_UP: {KeyInfo.is_up = true; return;}
        case ARROW_UP_RELEASE: {KeyInfo.is_up = false; return;}

        case ARROW_DOWN: {KeyInfo.is_down = true; return;}
        case ARROW_DOWN_RELEASE: {KeyInfo.is_down = false; return;}

        case ARROW_RIGHT: {KeyInfo.is_right = true; return;}
        case ARROW_RIGHT_RELEASE: {KeyInfo.is_right = false; return;}

        case ARROW_LEFT: {KeyInfo.is_left = true; return;}
        case ARROW_LEFT_RELEASE: {KeyInfo.is_left = false; return;}

    }

    KeyInfo.character = keyboard_map[scanCode];



    if(KeyInfo.scan_code >= 128)
    {
        KeyInfo.character = 0x0;
    }


    if((KeyInfo.is_caps) || (KeyInfo.is_shift))
    {
        if(KeyInfo.character >= 'a' && KeyInfo.character <= 'z')
        {
            KeyInfo.character -= 32;
        }
    }


    if(KeyInfo.is_shift)
    {
    key_remap('-','_');
    key_remap('1','!');
    key_remap('2', '@');
    key_remap('3','#');
    key_remap('4', '$');
    key_remap('5', '%');
    key_remap('6', '^');
    key_remap('7', '&');
    key_remap('8', '*');
    key_remap('9','(');
    key_remap('0',')');
    key_remap('=', '+');
    key_remap('[', '{');
    key_remap(']', '}');
    key_remap('/', '?');
    key_remap(';', ':');
    key_remap('`','~');
    key_remap(',','<');
    key_remap('.', '>');

    }

    
    if(keyboard_handle != nullptr)
    {
        keyboard_handle();
    }

    return;

          
    
}