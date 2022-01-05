
#include "./interpreter.h"

void no_keyboard_input()
{
    asm("nop");
}

void scan(void)
{

    
    KEYBOARD_SIG_ON(no_keyboard_input);


    if(cmpstr(COMMAND,"petris"))
    {
        clearScr();
        tetris();
    }



    else if(cmpstr(COMMAND,"help") || cmpstr(COMMAND,"h"))
    {
        clearScr();
        y = 2;
        x = 0;

        help();   
   }


    else if(cmpstr(COMMAND,"pong"))
    {

        pongStart:

        initPong();

        while(!exitApp)
        {
            updatePong();
        }   
        
        IRQ1_OFF();
        signal.appHandler = nullptr;

        
    }


 

    else if(cmpstr(COMMAND,"cls") || cmpstr(COMMAND,"clear"))
    {
        clearScr();
        exitApp = true;
    }


    else if(cmpstr(COMMAND,"ls") || cmpstr(COMMAND,"dir"))
    {
        ls();
        terminalAppExit = true;
    }

    for(int i = 0; i < 7;i++)
        COMMAND[i] = i;

    
    KEYBOARD_SIG_OFF()

}
