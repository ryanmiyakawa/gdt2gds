/*
 ******************************************************************************
 * Copyright 2004,2005,2006 by Ken Schumack
 *
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: 
 *           Ken Schumack (Schumack@cpan.org)
 *
 * Suggestions for improvements may be sent to Ken Schumack.
 ******************************************************************************
*/
//#include <stdio.h>
//#include <iostream.h>
//#include <sstream>
//#include <stdlib.h>
//#include <ostream.h>
//#include <math.h>
//#include <kvstypes.h>
#include "kvsstring_c.h"
#include "gdsStream.h"
#include <iostream>
using namespace std;

extern void print_help();
static const char* gds2gdt_Cwhat = "@(#) Version 1.0 $Id: gds2gdt.C $ $Revision: 10 $ $Date: 2006-10-25 22:03:27 -0500 (Wed, 25 Oct 2006) $";

//////////////////////////////////////////////////////////////////////////////
// M A I N
//////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) 
{
    int     i,
            length,
            haveInputName=0,
            haveOutputName=0,
            inInFileName=0,
            inOutFileName=0,
            inBoundary=0;
    short   Ref, columns, rows, extn, layer, dataType, textType, width,
            year, month, day, hour, min, sec,
            version_num;
    double  userUnits=0.001,
            dataBaseUnits=0.000000001,
            Ang=0.0,
            epsilon=(userUnits/1000.0), //use to "fix" floating point error
            Mag=0.0;
    char    oneChar,
            string512[512];
    stringL inputFile, outputFile, tmpFile;
    stringS strname, xstring, ystring, wstring, tmpString1, tmpString2;
    FILE    *fpOut;
    long    xcoord=0,
            ycoord=0;
            
    cerr << "# ** gds2gdt " << gds2gdt_Cwhat << " **" << endl;
    strcpy(inputFile, "");
    strcpy(outputFile, "");
    for(i=1; i<argc; i++) 
    {
        if((argv[i])[0] == '-') 
        {
            if ((inInFileName) && (! strcmp("-", argv[i])))
            {
                haveInputName = 1;
            }
            else if ((inOutFileName) && (! strcmp("-", argv[i])))
            {
                haveOutputName = 1;
                fpOut = stdout;
            }
            else if (match_string("-help", argv[i], 'm')) 
            {
                print_help();
                exit(0);
            }
            else if (match_string("-infilename", argv[i], 'm')) 
            {
                inInFileName = 1;
            }
            else if (match_string("-outfilename", argv[i], 'm')) 
            {
                inOutFileName = 1;
            }
            else if (match_string("-version", argv[i], 'm') || match_string("-swversion", argv[i], 'm')) 
            {
                exit(0);   // version already printed */
            }
            else
            {
                cerr << "ERROR **** unknown option " << argv[i] << endl;
                exit(2);
            }
        }
        else
        {
            if (inInFileName) 
            {
                haveInputName = 1;
                inInFileName = 0;
                strcpy(inputFile, argv[i]);
            }
            else if (inOutFileName) 
            {
                haveOutputName = 1;
                inOutFileName = 0;
                strcpy(outputFile, argv[i]);
            }
            else if (! haveInputName) 
            {
                haveInputName = 1;
                strcpy(inputFile, argv[i]);
            }
            else if (! haveOutputName) 
            {
                haveOutputName = 1;
                strcpy(outputFile, argv[i]);
            }
        }
    } 

    GDSFILE gds2file(inputFile, 0);
    if (! haveOutputName) 
    {
        fpOut = stdout;
    }
    else if (fpOut != stdout) 
    {
        if (strEqual(gds2file.fileName(),outputFile)) 
        {
            sprintf(outputFile,"%s.gdt",outputFile);
            cerr << "Warning ** you gave the input filename for the output file.  Will use " << outputFile << "instead" << endl;

        }
        if((fpOut = fopen(outputFile,"w")) == NULL) 
        {
            cerr << "ERROR **** unable to create file " << outputFile << endl;
            exit(1);
        }
    }
    // ************* end of command line and menu stuff ***************************

    gds2file.rdstrm();  // header
    version_num = gds2file.getI16();
    fprintf(fpOut, "gds2{%d\n",version_num);
    gds2file.rdstrm();  // bgnlib
        year  = gds2file.getI16(0);
        if (year < 999) year += 1900;
        month = gds2file.getI16(2);
        day   = gds2file.getI16(4);
        hour  = gds2file.getI16(6);
        min   = gds2file.getI16(8);
        sec   = gds2file.getI16(10);
    fprintf(fpOut, "m=%d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,min,sec);
        year  = gds2file.getI16(12);
        if (year < 999) year += 1900;
        month = gds2file.getI16(14);
        day   = gds2file.getI16(16);
        hour  = gds2file.getI16(18);
        min   = gds2file.getI16(20);
        sec   = gds2file.getI16(22);
    fprintf(fpOut, " a=%d-%02d-%02d %02d:%02d:%02d\n",year,month,day,hour,min,sec);
    while (! gds2file.eof()) 
    {
        gds2file.rdstrm();
        if      (gds2file.rectyp() == LIBNAME) 
        {
            gds2file.libName((char*) gds2file.record());
            fprintf(fpOut, "lib '%s'",gds2file.record());
            strcpy(strname, gds2file.record());
        }
        else if (gds2file.rectyp() == BGNSTR) 
        {
            year  = gds2file.getI16(0);
                if (year < 999) year += 1900;
                month = gds2file.getI16(2);
                day   = gds2file.getI16(4);
                hour  = gds2file.getI16(6);
                min   = gds2file.getI16(8);
                sec   = gds2file.getI16(10);
            fprintf(fpOut, "cell{c=%d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,min,sec);
                year  = gds2file.getI16(12);
                if (year < 999) year += 1900;
                month = gds2file.getI16(14);
                day   = gds2file.getI16(16);
                hour  = gds2file.getI16(18);
                min   = gds2file.getI16(20);
                sec   = gds2file.getI16(22);
            fprintf(fpOut, " m=%d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,min,sec);
        }
        else if (gds2file.rectyp() == UNITS) 
        {
            userUnits     = gds2file.getDbl();   // Calma default is 1.0e-3 
            epsilon = (userUnits/1000.0);
            dataBaseUnits = gds2file.getDbl(8);  // Calma default is 1.0e-9 
            fprintf(fpOut, " %g %g\n",userUnits,dataBaseUnits);
            fprintf(fpOut, "# first line needs to stay as is (read by other tools)\n");
            fprintf(fpOut, "# Key: <required> [optional]\n");
            fprintf(fpOut, "# File format:\n");
            fprintf(fpOut, "# gds2{<ver>\n");
            fprintf(fpOut, "# m=<modificationTimeStamp> a=<acessTimeStamp>\n");
            fprintf(fpOut, "# lib '<libName>' <userUnits> <dataUnits>\n");
            fprintf(fpOut, "# <cellDefine>\n");
            fprintf(fpOut, "# }\n");
            fprintf(fpOut, "# - - - - -\n");
            fprintf(fpOut, "# cellDefine is one of more of:\n");
            fprintf(fpOut, "# cell {c=<creationTimeStamp> m=<modificationTimeStamp> '<cellName>'\n");
            fprintf(fpOut, "# <cellStuff>\n");
            fprintf(fpOut, "# }\n");
            fprintf(fpOut, "# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            fprintf(fpOut, "## <cellStuff>\n");
            fprintf(fpOut, "# cellStuff is one or more of:\n");
            fprintf(fpOut, "# boundary:\n");
            fprintf(fpOut, "# b{<layer> [dt<dataType>] xy(<xyList>)}\n");
            fprintf(fpOut, "#\n");
            fprintf(fpOut, "# path:\n");
            fprintf(fpOut, "# p{<layer> [dt<dataType>] [pt<pathType>] [w<real>] [bx<real>] [ex<real>] xy(<xyList>)}\n");
            fprintf(fpOut, "#\n");
            fprintf(fpOut, "# text:\n");
            fprintf(fpOut, "# t{<layer> [tt<textType>] [f<fontType>] [<textJust>] [pt<pathType>] [fx] [w<real>] [m<magification>] [a<angle>] xy(<xyList>) <'text'> }\n");
            fprintf(fpOut, "#\n");
            fprintf(fpOut, "# sref:\n");
            fprintf(fpOut, "# s{<'cellName'> [fx] [a<angle>] xy(<xyList>)}\n");
            fprintf(fpOut, "#\n");
            fprintf(fpOut, "# aref:\n");
            fprintf(fpOut, "# a{<'cellName'> [fx] [a<angle>] cr(<columns> <rows>) xy(<xyList>)}\n");
            fprintf(fpOut, "# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            fprintf(fpOut, "# <textJust> two letter combination of bmt (bottom,middle,top) and rcl (right,center,left) e.g. bl (default is tl)\n");
            fprintf(fpOut, "#\n");
            fprintf(fpOut, "# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            fprintf(fpOut, "# # as first character on a line is a comment\n");
        }
        else if (gds2file.rectyp() == STRNAME) 
        {
            strcpy(strname, gds2file.record());
            fprintf(fpOut, " '%s'\n",strname);
            //cell{c=1998-08-17 14:31:10 m=1998-08-17 14:33:47 'CC1804_R1'  //...}
        }
        else if (gds2file.rectyp() == BOUNDARY)
        {
            inBoundary = 1;
            fprintf(fpOut, "b{");
        }
        else if (gds2file.rectyp() == PATH) 
        {
            fprintf(fpOut, "p{");
        }
        else if ((gds2file.rectyp() == ENDEL) || (gds2file.rectyp() == ENDSTR) || (gds2file.rectyp() == ENDLIB))
        {
            inBoundary = 0;
            fprintf(fpOut, "}\n");
        }
        else if (gds2file.rectyp() == COLROW) 
        {
            columns = gds2file.getI16();
            rows = gds2file.getI16(2);
            fprintf(fpOut," cr(%d %d)",columns,rows);
        } 
        else if (gds2file.rectyp() == PATHTYPE) 
        {
            Ref = gds2file.getI16();
            if (Ref != 0)
            {
                fprintf(fpOut," pt%d",Ref);
            }
        }
        else if (gds2file.rectyp() == STRANS) 
        {
            Ref = gds2file.getI16();
            if (Ref & 0x8000) 
            {
                fprintf(fpOut," fx");
            }
        } 
        else if (gds2file.rectyp() == PRESENTATION) 
        {
            Ref = gds2file.getI16();
            //font number
            if ((Ref & 0x30) == 0x30) 
            {
                fprintf(fpOut," f3");
            }
            else if ((Ref & 0x20) == 0x20) 
            {
                fprintf(fpOut," f2");
            }
            else if ((Ref & 0x10) == 0x10) 
            {
                fprintf(fpOut," f1");
            }
            //else sprintf(tmpString1," f0");

            tmpString1[0] = '\0';
            // bottom middle top
            if ((Ref & 0x8) == 0x8) 
            {
                sprintf(tmpString1,"b");
            }
            else if ((Ref & 0x4) == 0x4) 
            {
                sprintf(tmpString1,"m");
            }
            else
            {
                sprintf(tmpString1,"t");
            }
            // right center left
            if ((Ref & 0x2) == 0x2) 
            {
                strcat(tmpString1,"r");
            }
            else if ((Ref & 0x1) == 0x1) 
            {
                strcat(tmpString1,"c");
            }
            else
            {
                strcat(tmpString1,"l");
            }
            if (strncmp("tl",tmpString1,2)) fprintf(fpOut," %s",tmpString1); //save space - default
        } 
        else if (gds2file.rectyp() == TEXT) 
        {
            fprintf(fpOut, "t{");
        }
        else if (gds2file.rectyp() == SREF) 
        {
            fprintf(fpOut, "s{");
        }
        else if (gds2file.rectyp() == AREF) 
        {
            fprintf(fpOut, "a{");
        }
        else if (gds2file.rectyp() == SNAME) 
        {
            fprintf(fpOut, "'%s'", gds2file.record());
        }
        else if (gds2file.rectyp() == STRING) 
        {
            fprintf(fpOut, " '");
            strncpy(string512,gds2file.record(),512);
            string512[512] = '\0';
            for (i=0; i<strlen(string512); i++)
            {
                oneChar = string512[i];
                if (oneChar == '\r')
                {
                    //fprintf(fpOut, "%c", '\¤'); //do nothing
                }
                else if (oneChar == '\n')
                {
                    fprintf(fpOut, "%c", '\r'); // will print out as ^M char
                }
                else
                {
                    fprintf(fpOut, "%c", oneChar);
                }
            }
            fprintf(fpOut, "'");
        }
        else if (gds2file.rectyp() == XY) 
        {
            length = gds2file.length();
            if (inBoundary) length -= 8; //remove closure
            fprintf(fpOut, " xy(");
            for(i=0; i<length; i+=8)
            {
                xcoord = gds2file.getI32(i);
                ycoord = gds2file.getI32(i+4);
                if (xcoord < 0.0)
                {
                    sprintf(xstring,"%0.5f",(xcoord * userUnits) - epsilon);
                }
                else
                {
                    sprintf(xstring,"%0.5f",(xcoord * userUnits) + epsilon);
                }
                if (ycoord < 0.0)
                {
                    sprintf(ystring,"%0.5f",(ycoord * userUnits) - epsilon);
                }
                else
                {
                    sprintf(ystring,"%0.5f",(ycoord * userUnits) + epsilon);
                }
                fprintf(fpOut,"%s%s %s",i?" ":"",sRemoveTrailingZeros(xstring,tmpString1),sRemoveTrailingZeros(ystring,tmpString2));
            }
            fprintf(fpOut, ")");
        }
        else if (gds2file.rectyp() == LAYER) 
        {
            layer = gds2file.getI16();
            fprintf(fpOut,"%d",layer);
        }
        else if (gds2file.rectyp() == WIDTH)
        {
            width = gds2file.getI32();
            if (width != 0)
            {
                sprintf(wstring,"%0.5f",((double)width * userUnits) + epsilon);
                fprintf(fpOut," w%s",sRemoveTrailingZeros(wstring,tmpString1));
            }
        }
        else if (gds2file.rectyp() == DATATYPE)
        {
            dataType = gds2file.getI16();
            if (dataType != 0) fprintf(fpOut," dt%d",dataType);
        }
        else if (gds2file.rectyp() == TEXTTYPE)
        {
            textType = gds2file.getI16();
            if (textType != 0) fprintf(fpOut," tt%d",textType);
        }
        else if (gds2file.rectyp() == ANGLE) 
        {
            Ang = gds2file.getDbl();
            if (Ang != 0.0)
            {
                sprintf(xstring,"%0.5f",Ang);
                fprintf(fpOut," a%s",sRemoveTrailingZeros(xstring,tmpString1));
            }
        } // end ANGLE
        else if (gds2file.rectyp() == MAG) 
        {
            Mag = gds2file.getDbl();
            if (Mag != 1.0)
            {
                sprintf(xstring,"%0.5f",Mag);
                fprintf(fpOut," m%s",sRemoveTrailingZeros(xstring,tmpString1));
            }
        } // end MAG
        else if (gds2file.rectyp() == BGNEXTN) 
        {
            extn = gds2file.getI16();
            fprintf(fpOut," bx%d",extn);
        }
        else if (gds2file.rectyp() == ENDEXTN) 
        {
            extn = gds2file.getI16();
            fprintf(fpOut," ex%d",extn);
        }
    }
    return(0);
}  // end of main 

// ****************************************************************************
// * print_help()
// ****************************************************************************
void print_help() 
{
    cout << endl;
    cout << "gds2gdt provides you with a tool to convert a binary gds2 files to a textual" << endl;
    cout << "gdt file." << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "    gds2gdt [inputFile] [outputFile] [OPTIONS]" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << " Note: options are case-insensitive and can be shortened as long they remain unique." << endl;
    cout << endl;
    cout << "  -help" << endl;
    cout << "    print this and exit" << endl;
    cout << endl;
    cout << "  -inFilename [inputFile]" << endl;
    cout << "    default is STDIN" << endl;
    cout << "    if inputFile == '-' read from STDIN" << endl;
    cout << endl;
    cout << "  -outFilename [outputFile]  : print this" << endl;
    cout << "    if outputFile == '-' print to STDOUT (screen)" << endl;
    cout << endl;
    cout << "  -version" << endl;
    cout << "    print version of program and quit" << endl;
    cout << endl;
    cout << "Examples:" << endl;
    cout << "  gds2gdt test.gds test.gdt" << endl;
    cout << endl;
    cout << "  zcat test.gds.gz | gds2gdt | grep ^cell" << endl;
    cout << endl;
}

/*

__END__
use pod2html to make web page help
use pod2man to make man page

=pod

=head1 NAME

gds2gdt - tool to convert binary gds2 to textual gdt format 

=head1 SYNOPSIS

gds2gdt [options] [inputFile] [outputFile]

=head1 OPTIONS

Note: options are case-insensitive and can be shortened as long they remain unique.

  -help
    print this and exit

  -inFilename <fileName>
    default is STDIN
    also filename of '-' means STDIN

  -outFilename <fileName>
    default is STDOUT 
    also filename of '-' means STDOUT

  -version
    print version of program and quit

=head1 EXAMPLES

gds2gdt test.gds test.gdt

zcat test.gds.gz | gds2gdt | grep ^cell

=cut
*/

