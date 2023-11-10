#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char str[10000];
    char operator_check[10000] = {0,};
    char *tok;
    int index = 0;
    long long result = 0;

    printf("input operation > ");
    fgets(str, 10000, stdin);
    str[strlen(str) - 1] = '\0'; // 개행 제거

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '+') operator_check[index++] = 1;
        else if (str[i] == '-') operator_check[index++] = -1;
    }

    tok = strtok(str, "+-");
    index = 0;
    result += atoll(tok);

    while (tok != NULL)
    {
        tok = strtok(NULL, "+-");


        if (operator_check[index] == 1) result += atoll(tok);
        else if (operator_check[index] == -1) result -= atoll(tok);
        index++;
    }

    printf("= %lld", result);

    return 0;
}