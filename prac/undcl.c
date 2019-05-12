#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUTLEN 1000
#define BUFLEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

char buf[BUFLEN];
int sp = 0;
int getch(void);
void ungetch(int c);

int gettoken(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUTLEN];

int main()
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type == gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        }
    }

    return 0;
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else 
        return tokentype = c;
}

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';)
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}



int getch(void)
{
    return sp > 0 ? buf[--sp] : getchar();
}

void ungetch(int c)
{
    if (sp == BUFLEN)
        printf("The buffer is full\n");
    else
        buf[sp++] = c;
}
