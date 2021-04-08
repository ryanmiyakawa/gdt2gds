// Copyright 1995-2005 by Ken Schumack
#ifndef __kvstypes__
#define __kvstypes__

#include <stdio.h>

static const char* kvstypes_hwhat = "@(#) $RCSfile: kvstypes.h,v $ $Revision: 1.1 $ $Date: 2005-04-18 00:13:52-05 $";


#define TRUE    1
#define FALSE   0
#define YES     1
#define NO      0
#define ERROR   (-1)
#define ERR     (-1)
#define READ    0
#define WRITE   1

#define LENGTHLSTRING 256
#define LENGTHSSTRING  80

typedef short   Boolean;
typedef char    stringS[LENGTHSSTRING];
typedef char    stringL[LENGTHLSTRING];
typedef double* coordArray;

#define SEEK_CUR 1

#define BUFSIZE     100
#define SIZE_FOREST 37

#define strEqual(s1, s2)   ( ! strcmp(s1, s2) )

typedef struct sort_linest 
{
    char*  strng;
    struct sort_linest* linkr;
} sort_linest;

typedef struct synonymForestMember 
{
    char*    name;
    char*    synonym;
    struct synonymForestMember* linkl;
    struct synonymForestMember* linkr;
}  synonymForestMember;


typedef struct GPO {  
    char*       name;
    char*       synonym;
    Boolean     Switch;
    int         Int;
    double      Double;
    struct GPO* headSynonym;
    struct GPO* linkl;
    struct GPO* linkr;
} GPO;


typedef GPO **GPOforest;
typedef GPO *GPOtree;

#endif

