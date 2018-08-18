#include "../interpreter.h"
#include <switch.h>
#include <stdio.h>

#ifndef BUILTIN_MINI_STDLIB
#ifndef NO_FP

void NetcheatSleepMS(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->FP = svcSleepThread(1000000L * Param[0]->Val->Integer);
}

struct LibraryFunction NetcheatFunctions[] =
{
    { NetcheatSleepMS,         "unsigned int sleepMS(int);" },
    { NULL,             NULL }
};

void NetcheatSetupFunc(Picoc *pc)
{

}

#endif /* !NO_FP */
#endif /* !BUILTIN_MINI_STDLIB */
