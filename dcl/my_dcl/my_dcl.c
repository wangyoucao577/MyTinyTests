/*
* My style dcl program
* Author : wangyoucao577@gmail.com
* Date : 2016.01.19
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>


#define MAXTOKEN 100

enum { 
    NAME = 1, 
    PARENS, 
    BRACKETS };

typedef struct dcl_tag {
    char c_declaration[MAXTOKEN];   /* which is ready to check*/

    char* checking_pos;

    int tokentype;  /* type of last token*/
    char token[MAXTOKEN];   /* last token string*/
    char name[MAXTOKEN];    /* identifier name*/
    char datatype[MAXTOKEN];    /* data type = char, int, etc.*/
    char out[1000];     /* output string*/
} dcl_t;


/* dcl: parse a declarator*/
void dcl(dcl_t * dcl_info);

/* dirdcl: parse a direct declarator*/
void dirdcl(dcl_t * dcl_info);

/* return next token*/
int gettoken(dcl_t * dcl_info);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage : dcl <C declaration>\n");
        printf("  For instance: dcl \'void (*comp)()\'\n");
        goto Exit;
    }
    printf("C declaration ready to check :%s, len:%d\n", argv[1], strlen(argv[1]));

    dcl_t * new_dcl = (dcl_t*)malloc(sizeof(dcl_t));
    assert(NULL != new_dcl);
    memset(new_dcl, 0, sizeof(dcl_t));
    strcpy(new_dcl->c_declaration, argv[1]);
    new_dcl->checking_pos = new_dcl->c_declaration;

    if (gettoken(new_dcl) != '\0') { /* 1st token on line*/
        strcpy(new_dcl->datatype, new_dcl->token);    /* is the data type*/
        new_dcl->out[0] = '\0';
        dcl(new_dcl);  /* parse rest of line */
        if (new_dcl->tokentype != '\0') {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", new_dcl->name, new_dcl->out, new_dcl->datatype);
    }

    if (new_dcl) {
        free(new_dcl);
        new_dcl = NULL;
    }
Exit:
    printf("Press any key to continue...\n");
    getchar(); 
    return 0;
}


#define MY_GETCHAR  (*(dcl_info->checking_pos)++)
#define MY_UNGETCHAR (dcl_info->checking_pos--)

int gettoken(dcl_t * dcl_info)
{
    int c;
    char *p = dcl_info->token;

    //ignore blank and tab
    while ((c = MY_GETCHAR) == ' ' || c == '\t')
    {
        ;
    }

    if (c == '(') {
        if ((c = MY_GETCHAR) == ')') {
            strcpy(dcl_info->token, "()");
            return dcl_info->tokentype = PARENS;
        }
        else {
            MY_UNGETCHAR;
            return dcl_info->tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = MY_GETCHAR) != ']'; ) {
            ;
        }
        *p = '\0';
        return dcl_info->tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = MY_GETCHAR); ) {
            *p++ = c;
        }
        *p = '\0';
        MY_UNGETCHAR;
        return dcl_info->tokentype = NAME;
    }
    else {
        return dcl_info->tokentype = c;
    }
}

void dcl(dcl_t * dcl_info)
{
    int ns;

    for (ns = 0; gettoken(dcl_info) == '*'; )   //count *'s
        ns++;
    dirdcl(dcl_info);
    while (ns-- > 0)
        strcat(dcl_info->out, " pointer to");
}

void dirdcl(dcl_t * dcl_info)
{
    int type;

    if (dcl_info->tokentype == '(') { /* ( dcl ) */
        dcl(dcl_info);
        if (dcl_info->tokentype != ')') {
            printf("error: missing )\n");
        }
    }
    else if (dcl_info->tokentype == NAME) { /* variable name */
        strcpy(dcl_info->name, dcl_info->token);
    }
    else {
        printf("error: expected name or (dcl)\n");
    }

    while ((type = gettoken(dcl_info)) == PARENS || type == BRACKETS)
    {
        if (type == PARENS) {
            strcat(dcl_info->out, " function returning");
        }
        else {
            strcat(dcl_info->out, " array");
            strcat(dcl_info->out, dcl_info->token);
            strcat(dcl_info->out, " of");
        }
    }
}
