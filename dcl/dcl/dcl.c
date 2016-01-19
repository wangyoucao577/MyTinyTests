/*
* Reference from <C Programming Language> Chapter 5.12
*
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


int tokentype;  /* type of last token*/
char token[MAXTOKEN];   /* last token string*/
char name[MAXTOKEN];    /* identifier name*/
char datatype[MAXTOKEN];    /* data type = char, int, etc.*/
char out[1000];     /* output string*/

enum { 
    NAME = 1, 
    PARENS, 
    BRACKETS };

int main(int argc, char *argv[])
{
    while (gettoken() != EOF) { /* 1st token on line*/
        strcpy(datatype, token);    /* is the data type*/
        out[0] = '\0';
        dcl();  /* parse rest of line */
        if (tokentype != '\r') {    /*on windows, should check whether \r first. on linux here should be \n*/
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; )   //count *'s
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl()
{
    int type;

    if (tokentype == '(') { /* ( dcl ) */
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
        }
    }
    else if (tokentype == NAME) { /* variable name */
        strcpy(name, token);
    }
    else {
        printf("error: expected name or (dcl)\n");
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if (type == PARENS) {
            strcat(out, " function returning");
        }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

int gettoken()
{
    int c;

    char *p = token;

    while ((c = getche()) == ' ' || c == '\t')
    {
        ;
    }

    if (c == '(') {
        if ((c = getche()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getche()) != ']'; ) {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getche()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else {
        return tokentype = c;
    }
}

