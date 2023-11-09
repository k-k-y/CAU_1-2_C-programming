#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find(const char word[][30], const char input[], int wordCnt) // 단어가 있는지 없는지 여부(있으면 1 반환)
{
    for (int i = 0; i < wordCnt; i++)
        if (strcmp(word[i], input) == 0) return 1;
    
    return 0; // 단어가 없으면 0 반환
}
int compare(const void* first, const void* second)
{
    if (strcmp((char*)first, (char*)second) > 0)
        return 1;
    else if (strcmp((char*)first, (char*)second) < 0)
        return -1;
    else
        return 0;
}

int main(void)
{
    char str[100]; // 각각의 문장 전체 
    char word[100][30]; // 모든 문장의 단어 저장
    char *tok;
    int strCnt = 0, input_wordCnt = 0, wordCnt = 0;

    for (;;)
    {
        printf("> ");
        fgets(str, 1000, stdin);
        str[strlen(str) - 1] = '\0'; // 개행 없애기

        if (strcmp(str, "end") == 0) break; // exit condition
        strCnt++;

        tok = strtok(str, " ");
        while (tok != NULL)
        {
            input_wordCnt++;

            if (!find(word, tok, wordCnt)) // 단어가 없으면 집어넣기
            {
                strcpy(word[wordCnt], tok); 
                wordCnt++;
            }
            tok = strtok(NULL, " ");
        }

    }
    
    printf("\n%d %d %d\n\n", strCnt, input_wordCnt, wordCnt);

    qsort(word, wordCnt, sizeof(word[0]), compare);
    for (int i = 0; i < wordCnt; i++) printf("%s\n", word[i]);

    return 0;
}