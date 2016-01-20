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

typedef struct dcl_in_tag {
    char c_declaration[MAXTOKEN];   /* which is ready to check*/

    char* checking_pos;
} dcl_in_t;

typedef struct dcl_out_tag {
    char name[MAXTOKEN];    /* identifier name*/
    char datatype[MAXTOKEN];    /* data type = char, int, etc.*/
    char out[1000];     /* output string*/
} dcl_out_t;

typedef struct get_token_out_tag {
    int tokentype;  /* type of last token*/
    char token[MAXTOKEN];   /* last token string*/
} get_token_out_t;

/* dcl: parse a declarator*/
void dcl(dcl_in_t * dcl_info, dcl_out_t * dcl_out_info, get_token_out_t *get_token_out);

/* dirdcl: parse a direct declarator*/
void dirdcl(dcl_in_t * dcl_info, dcl_out_t * dcl_out_info, get_token_out_t * last_get_token_out_info);

/* return next token*/
int gettoken(dcl_in_t * dcl_info, get_token_out_t * out_info);


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage : dcl <C declaration>\n");
        printf("  For instance: dcl \'void (*comp)()\'\n");
        goto Exit;
    }
    printf("C declaration ready to check :%s, len:%d\n", argv[1], strlen(argv[1]));

    dcl_in_t dcl_info;
    strcpy(dcl_info.c_declaration, argv[1]);
    dcl_info.checking_pos = dcl_info.c_declaration;

    get_token_out_t get_token_out_info;
    memset(&get_token_out_info, 0, sizeof(get_token_out_t));

    dcl_out_t dcl_out_info;
    memset(&dcl_out_info, 0, sizeof(dcl_out_t));

    if (gettoken(&dcl_info, &get_token_out_info) != '\0') {        /* 1st token on line, should be datatype*/
        strcpy(dcl_out_info.datatype, get_token_out_info.token);    /* is the data type*/
        dcl_out_info.out[0] = '\0';
        dcl(&dcl_info, &dcl_out_info, &get_token_out_info);  /* parse rest of line */
        if (get_token_out_info.tokentype != '\0') {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", dcl_out_info.name, dcl_out_info.out, dcl_out_info.datatype);
    }

Exit:
    printf("Press any key to continue...\n");
    getchar(); 
    return 0;
}


#define MY_GETCHAR  (*(dcl_info->checking_pos)++)
#define MY_UNGETCHAR (dcl_info->checking_pos--)

int gettoken(dcl_in_t * dcl_info, get_token_out_t * out_info)
{
    int c;
    char *p = out_info->token;

    //ignore blank and tab
    while ((c = MY_GETCHAR) == ' ' || c == '\t')
    {
        ;
    }

    if (c == '(') {
        if ((c = MY_GETCHAR) == ')') {
            strcpy(out_info->token, "()");
            return out_info->tokentype = PARENS;
        }
        else {
            MY_UNGETCHAR;
            return out_info->tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = MY_GETCHAR) != ']'; ) {
            ;
        }
        *p = '\0';
        return out_info->tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = MY_GETCHAR); ) {
            *p++ = c;
        }
        *p = '\0';
        MY_UNGETCHAR;
        return out_info->tokentype = NAME;
    }
    else {
        return out_info->tokentype = c;
    }
}

void dcl(dcl_in_t * dcl_info, dcl_out_t * dcl_out_info, get_token_out_t *get_token_out)
{
    int ns;

    for (ns = 0; gettoken(dcl_info, get_token_out) == '*'; )   //count *'s
        ns++;
    dirdcl(dcl_info, dcl_out_info, get_token_out);
    while (ns-- > 0)
        strcat(dcl_out_info->out, " pointer to");
}

void dirdcl(dcl_in_t * dcl_info, dcl_out_t * dcl_out_info, get_token_out_t * last_get_token_out_info)
{
    int type;

    if (last_get_token_out_info->tokentype == '(') { /* ( dcl ) */
        dcl(dcl_info, dcl_out_info, last_get_token_out_info);
        if (last_get_token_out_info->tokentype != ')') {
            printf("error: missing )\n");
        }
    }
    else if (last_get_token_out_info->tokentype == NAME) { /* variable name */
        strcpy(dcl_out_info->name, last_get_token_out_info->token);
    }
    else {
        printf("error: expected name or (dcl)\n");
    }


    while ((type = gettoken(dcl_info, last_get_token_out_info)) == PARENS || type == BRACKETS)
    {
        if (type == PARENS) {
            strcat(dcl_out_info->out, " function returning");
        }
        else {
            strcat(dcl_out_info->out, " array");
            strcat(dcl_out_info->out, last_get_token_out_info->token);
            strcat(dcl_out_info->out, " of");
        }
    }
}
