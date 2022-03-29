
#include <lib/hal.h>
#include <lib/stdiox.h>
#include <xin_fs/xanin_fs_saver.c>

void shutdown(void)
{

    real_mode_enter(0x800);


    outdwIO(0x604, 0x2000);  /* QEMU */
    outdwIO(0xB004, 0x2000); /* BOCHS AND OLD QEMU */
    outdwIO(0x4004, 0x3400); /* VIRTUALBOX */

    screen_clear();

    xprintf("goodbye :))\n\n");

    xprintf("Your computer status:\n\n");



    reg_dump();



    asm("cli");
    asm("hlt");

}
