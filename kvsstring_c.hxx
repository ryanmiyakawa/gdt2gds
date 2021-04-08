// Copyright 1995-2005 by Ken Schumack
#ifndef _kvsstring
#define _kvsstring
#include <kvstypes.h>

extern "C" {
 void    copy_array(float *a1, float *a2, int n);
 char*   expandPosIntRange(char *input, char *output);
 char*   fillCharArray(char *string, char character, int arr_length);
 int     get_delim_field(char *string, char *field_string, char character, int position);
 int     get_field(char *string, char *field_string, int position);
 char*   get_field_number(char *string, char *field_string, int fieldNumber);
 int     get_field_pos(char *string, int field, int position);
 int     getargs(char *args[][80]);
 void    getbody(char *input, char *output);
 int     gsub(char *match, char *replacement, char *string);
 int     gsubi(char *match, char *replacement, char *string);
 char*   hexstopadedbins(char *string, char *binarystring, int numberofbits);
 int     isdecint(char *string);
 Boolean isfloat(char *string);
 Boolean ishexint(char *string);
 int     itobs(int i, char *bitstring);
 void    legalstring(char *sinput, char *soutput, int maxlength, char fillerc);
 int     lexidex(int y, int *array);
 Boolean match_string(char *master, char *string, char option);
 int     numfields(char *string);
 char*   padCharArray(char *string, char character, int start, int arr_length);
 char*   revstring(char *string, char *reversed);
 char*   sGetWordPart(char *string, char *word, int position, int startOrEnd);
 char*   sRemoveLeadingSpaces(char *parent, char *child);
 char*   sRemoveSpaces(char *parent, char *child);
 char*   sRemoveTrailingSpaces(char *parent, char *child);
 char*   scolumn(char *string, char *control);
 void    sdelcr(char *string);
 char*   sdup(char *string);
 int     sexpcmp(char *s1, char *s2);
 int     sfind(char *string, char *line, char option);
 int     sfindlast(char *string, char *line, char option);
 char**  sget_argvs(char *string);
 int     sgetword(char *string, char *word, int lim);
 int     shexcmp(char *s1, char *s2);
 char*   sintonly(char *parent, char *child);
 int     sislower(char *string);
 int     sisupper(char *string);
 char    slastNonSpacec(char *string);
 char*   smakealnum(char *parent, char *child);
 int     snumc(char *string, char c);
 int     snumcmp(char *s1, char *s2);
 void    sortfile(char *options);
 int     soverlap(char *string1, char *string2);
 int     spatrep(char *string, char *pattern, char *replacement, int num_to_replace, Boolean ignore_case);
 int     spatrepcol(char *string, char *pattern, char *replacement, int start_column, int num_to_replace, Boolean ignore_case, int number_replaced);
 int     sposc(char *string, char c);
 int     sposlastc(char *string, char c);
 int     sposnextc(char *string, char c, int previousPosition);
 char*   sprefix(char *prefix_string, char *string);
 char*   sremovec(char *parent, char *child, char character);
 char*   srepc(char *parent, char *child, char character, char replacement);
 char*   sreppunct(char *parent, char *child, char replacement);
 char*   sspacemin(char *parent, char *child);
 char*   stolower(char *string, char *lowstring);
 char*   stoupper(char *string, char *upstring);
 void    str_qsort(struct sort_linest **v, int left, int right, int (*comparison)(), int start_field, int end_field);
 char*   strip_version(char *input, char *output);
 int     sub(char *match, char *replacement, char *string);
 int     subi(char *match, char *replacement, char *string);
 char*   substring(char *parent, char *child, int start, int end);
 void    swap(void *v[], int i, int j);
 int     wildInLine(char *wildToFind, char *line, Boolean ignore_case);
 int     wild_match(char *string, char *wildstring, int ignore_case);
 void    write_sortfile_help(void);
}

#endif

