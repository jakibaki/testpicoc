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

    //Initialize console. Using NULL as the second argument tells the console library to use the internal console structure as current one.
    consoleInit(NULL);


    int ParamCount = 1;
    int DontRunMain = FALSE;
    int StackSize = getenv("STACKSIZE") ? atoi(getenv("STACKSIZE")) : PICOC_STACK_SIZE;
    Picoc pc;

    PicocInitialise(&pc, StackSize);

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

/*
int main(int argc, char **argv)
{
    int ParamCount = 1;
    int DontRunMain = FALSE;
    int StackSize = getenv("STACKSIZE") ? atoi(getenv("STACKSIZE")) : PICOC_STACK_SIZE;
    Picoc pc;
    
    if (argc < 2)
    {
        printf("Format: picoc <csource1.c>... [- <arg1>...]    : run a program (calls main() to start it)\n"
               "        picoc -s <csource1.c>... [- <arg1>...] : script mode - runs the program without calling main()\n"
               "        picoc -i                               : interactive mode\n");
        exit(1);
    }
    
    PicocInitialise(&pc, StackSize);
    
    if (strcmp(argv[ParamCount], "-s") == 0 || strcmp(argv[ParamCount], "-m") == 0)
    {
        DontRunMain = TRUE;
        PicocIncludeAllSystemHeaders(&pc);
        ParamCount++;
    }
        
    if (argc > ParamCount && strcmp(argv[ParamCount], "-i") == 0)
    {
        PicocIncludeAllSystemHeaders(&pc);
        PicocParseInteractive(&pc);
    }
    else
    {
        if (PicocPlatformSetExitPoint(&pc))
        {
            PicocCleanup(&pc);
            return pc.PicocExitValue;
        }
        
        for (; ParamCount < argc && strcmp(argv[ParamCount], "-") != 0; ParamCount++)
            PicocPlatformScanFile(&pc, argv[ParamCount]);
        
        if (!DontRunMain)
            PicocCallMain(&pc, argc - ParamCount, &argv[ParamCount]);
    }
    
    PicocCleanup(&pc);
    return pc.PicocExitValue;
}
*/