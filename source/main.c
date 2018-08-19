/* picoc main program - this varies depending on your operating system and
 * how you're using picoc */

/* include only picoc.h here - should be able to use it with only the external interfaces, no internals from interpreter.h */
#include "picoc.h"

/* platform-dependent code for running programs is in this file */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <switch.h>

#define PICOC_STACK_SIZE (128 * 1024) /* space for the the stack */

int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(NULL);

    Picoc pc;

    PicocInitialise(&pc, PICOC_STACK_SIZE);

    // If picoc fails it will jump here and the check will go through.
    if (!PicocPlatformSetExitPoint(&pc))
    {
        PicocPlatformScanFile(&pc, "/test.c");
        PicocCallMain(&pc, 0, 0);
    }

    PicocCleanup(&pc);

    while (appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }

    gfxExit();
    return pc.PicocExitValue;
}