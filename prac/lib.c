#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

void expand(const char s1[], char s2[])
{
    int i, j, tmp;

    i = j = 0;

    while (s1[i] != '\0') {
        if (i == 0 || s1[i + 1] == '\0' || s1[i] != '-') {
            s2[j++] = s1[i++];
        } else {
            tmp = s1[i - 1];
            if ((isalpha(tmp) && isalpha(s1[i+1])) ||
                (isdigit(tmp) && isdigit(s1[i+1]))) {
                while (++tmp != s1[i + 1]) {
                    s2[j++] = tmp;
                }   
                ++i;
            } else {
                s2[j++] = s1[i++];
            }
        }
    }
    s2[j] = '\0';
}

int testexpand()
{
    char a1[] = "-a-bc-e0-7--";
    char a2[100] = {0};

    expand(a1, a2);
    printf("%s ->\n%s\n", a1, a2);

    return 0;
}

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int teststrindex()
{
    char line[MAXLINE];
    int found = 0;

    while (getline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    return found;
}

int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

double atof(char [])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); ++i)
        ;
    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        ++i;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        ++i;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

int main()
{
    teststrindex();
}
