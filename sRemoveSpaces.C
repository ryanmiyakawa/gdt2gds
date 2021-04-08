// Copyright 1995-2005 by Ken Schumack
//#include <string>
#include <string.h>
#include <kvstypes.h>
#include <kvsstring_c.h>

/***** SREMOVESPACES ********************************************************/
/* Removes all occurances of a spaces & tabs in a string             -kvs   */
/****************************************************************************/
char* sRemoveSpaces(char* parent, char* child)
{
    int i, j, length;

    length = strlen(parent);
    for(i=0, j=0; i<length; i++) 
    {
        if (!(parent[i] == ' ' || parent[i] == '\t')) 
        {
            child[j] = parent[i];
            j++;
        }
    }
    child[j] = '\0';
    return(child);
}

