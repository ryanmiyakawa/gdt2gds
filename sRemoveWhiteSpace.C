// Copyright 1995-2005 by Ken Schumack
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>

/***** SREMOVEWHITESPACE ****************************************************/
/* Removes all occurances of white space in a string                 -kvs   */
/****************************************************************************/
char* sRemoveWhiteSpace(char* parent, char* child)
{
    int i, j, length;

    length = strlen(parent);
    for(i=0, j=0; i<length; i++) 
    {
        if (!(parent[i] == ' ' || parent[i] == '\t' || parent[i] == '\n' || parent[i] == '\r')) 
        {
            child[j] = parent[i];
            j++;
        }
    }
    child[j] = '\0';
    return(child);
}

