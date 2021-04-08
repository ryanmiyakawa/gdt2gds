// Copyright 1995-2005 by Ken Schumack
#include <kvstypes.h>
#include <kvsstring_c.h>
#include <ctype.h>
#include <string.h>

/***** MATCH STRING **********************************************************/
/* Compares string to master and returns 1 for match, 0 for not matched      */
/* ie. if master was 'help' and string was 'He' it would match with the      */
/* A (abbreviated) option, but if string was 'Gelp' or 'HELPG' it would not. */
/* Case is ignored when doing comparisions.                                  */
/* On the other hand if the F (full) option is used the string must contain  */
/* the same number of characters as the master.  F (full) is the default     */
/* option.                                                                   */
/*     match_string(qwe,asd,'M')                                             */
/*     match_string(qwe,asd,'F')                  -KVS                       */
/*****************************************************************************/
Boolean match_string(char* master, char* string, char option)
{
    char cs,cp;
    int     x,
            master_len,
            string_len; 

    master_len = strlen(master);
    string_len = strlen(string);

    if (option == 'm' || option == 'M') 
    { 
        if(master_len < string_len || string_len == 0) return(FALSE);
        for (x=0;x<string_len;x++) 
        {
            if ((cs = *string++) == (cp = *master++) || tolower(cs) == cp ||
                                                         toupper(cs) == cp)  ;
            else return(FALSE);
        } 
        return(TRUE); 
    }
    else 
    {
        if(master_len != string_len) return(FALSE);
        for (x=0;x<string_len;x++) 
        {
            if ((cs = *string++) == (cp = *master++) || tolower(cs) == cp ||
                                                         toupper(cs) == cp)  ;
            else return(FALSE);
        } 
        return(TRUE); 
    }
}

