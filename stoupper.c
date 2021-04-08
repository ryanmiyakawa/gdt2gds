// Copyright 1995-2005 by Ken Schumack
#include <kvstypes.h>
#include <kvsstring_c.h>
#include <ctype.h>
/***** STOUPPER **************************************************************/
/* uses toupper repeatedly on a string   -kvs                                */
/*****************************************************************************/
char* stoupper(char* string, char* upstring)
{
    while (*string != '\0') 
    {
        if (islower(*string))  *upstring++ = toupper(*string++);
        else                   *upstring++ = *string++;
    }
    *upstring = '\0';       /* add null back on for end of string */
    return(upstring);
}

