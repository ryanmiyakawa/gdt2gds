// Copyright 1995-2005 by Ken Schumack
//#include <string>
#include <string.h>
#include <kvstypes.h>
#include <kvsstring_c.h>

/***** sRemoveTrailingZeros *********************************************/
/* Remove zeros at the end of a real number                        -kvs */
/************************************************************************/
char* sRemoveTrailingZeros(char* parent, char* child)
{
    int i, done, length;
    done = 0;
    length = strlen(parent);
    strcpy(child,parent);
    
    for(i=length; (i>0) && (! done); i--) 
    {
        if (parent[i] == '.')
        {
            done = 1;
            child[i] = '\0';
        }
        else if ((parent[i] != '0') && (parent[i] != '\0'))
        {
            done = 1;
        }
        else
        {
            child[i] = '\0';
        }
    }
    return(child);
}

