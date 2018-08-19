#include "../interpreter.h"
#include <switch.h>
#include <stdio.h>

#ifndef BUILTIN_MINI_STDLIB
#ifndef NO_FP

void NetcheatSleepMS(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->UnsignedInteger = svcSleepThread(1000000L * Param[0]->Val->Integer);
}

const char NetcheatDefs[] = "\
typedef unsigned char u8; \
typedef unsigned short u16; \
typedef unsigned int u32; \
typedef unsigned long u64; \
";

struct LibraryFunction NetcheatFunctions[] =
{
    { NetcheatSleepMS,         "u32 sleepMS(int);" },
    { NULL,             NULL }
};

void NetcheatSetupFunc(Picoc *pc)
{

}

#endif /* !NO_FP */
#endif /* !BUILTIN_MINI_STDLIB */
