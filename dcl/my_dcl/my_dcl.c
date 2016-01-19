/*
* My style dcl program
* Author : wangyoucao577@gmail.com
* Date : 2016.01.19
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* dcl: parse a declarator*/
void dcl();

/* dirdcl: parse a direct declarator*/
void dirdcl();

/* return next token*/
int gettoken();

#define MAXTOKEN 100

enum { 
    NAME = 1, 
    PARENS, 
    BRACKETS };

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage : dcl <C declaration>\n");
        printf("  For instance: dcl \'void (*comp)()\'\n");
        goto Exit;
    }
    char * p_declaration = argv[1];
    printf("C declaration ready to check :%s\n", p_declaration);

    //TODO: add functions to check the declaration

Exit:
    printf("Press any key to continue...\n");
    getchar(); 
    return 0;
}
