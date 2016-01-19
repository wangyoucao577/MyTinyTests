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

    return 0;
}
