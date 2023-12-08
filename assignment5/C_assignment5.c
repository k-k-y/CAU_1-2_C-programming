#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Word
{
    int length;
    int gather;
    char spell[100];
    char meaning[100];
} Word;

int compareByLength(const void *a, const void *b)
{
    return (((Word *)b)->length - ((Word *)a)->length);
}

int compareByGather(const void *a, const void *b)
{
    return (((Word *)b)->gather - ((Word *)a)->gather);
}

Word Dict[60000];
int dict_len = 0;

void storeWords()
{
    FILE *fp;
    char temp_string[200];
    char t_spell[100];
    char t_meaning[100];

    fp = fopen("dict_test.TXT", "r");
    if (fp == NULL)
    {
        printf("FILE OPEN ERROR\n");
        exit(1);
    }

    for (int i = 0; fgets(temp_string, 200, fp) != NULL; i++)
    {
        int j = 0;
        int k = 0;

        for (; temp_string[j] != ':'; j++) // 문자열 파싱
            t_spell[j] = temp_string[j];
        t_spell[j - 1] = '\0';
        for (; temp_string[j] != '\n'; j++,k++)
            t_meaning[k] = temp_string[j];
        t_meaning[k] = '\0';
     
        Dict[i].length = strlen(t_spell); // 길이
        strcpy(Dict[i].spell, t_spell); // 영어 단어
        strcpy(Dict[i].meaning, t_meaning); // 한글 뜻

        Dict[i].gather = 0; // 모음 개수
        for (int k = 0; t_spell[k] != '\0'; k++)
        {
            char ch = t_spell[k];
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                Dict[i].gather++;
        }

        dict_len++;
    }

    if (fgets(temp_string, 100, fp) == NULL)
        printf("ALL STORED\n");
    else
        printf("NOT ALL STORED\n");

    fclose(fp);

    return;
}
void searchWords()
{
    char t_spell[100];
    while (1)
    {
        printf("단어?(엔터만 입력하면 종료) ");
        fgets(t_spell, 100, stdin);
        if (strcmp(t_spell, "\n") == 0) break; // 엔터만 입력하면 exit

        t_spell[strlen(t_spell) - 1] = '\0'; // 개행 제거
        for (int i = 0; i <= dict_len; i++) // 맞는 단어 찾기
        {
            if (i == dict_len)
                printf("단어를 찾을 수 없습니다.\n");
            else if (strcmp(Dict[i].spell, t_spell) == 0)
            {
                printf("%s %s\n", Dict[i].spell, Dict[i].meaning);
                break;
            }
        }

    }
    
    printf("\n");
    return ;
}
void concludingRemarks()
{
    int idx = (rand() % dict_len);
    int score = 0;
    char last_alpha, first_alpha;
    char first_spell[100];
    char second_spell[100];
    char visited[10][100];
    int visit_index = 0;
    char isVisit = 0;
    char isStored = 0;
    int life = 3;
    strcpy(first_spell, Dict[idx].spell);
    printf("컴퓨터 : %s\n", first_spell);

    for (int i = 0; i < 10; i++)
    {
        last_alpha = first_spell[strlen(first_spell) - 1];
        printf("끝말잇기 단어 : ");
        fgets(second_spell, 100, stdin);
        second_spell[strlen(second_spell) - 1] = '\0';

        first_alpha = second_spell[0];

        for (int j = 0; j < dict_len; j++)
        {
            if (strcmp(Dict[j].spell, second_spell) == 0)
            {
                isStored = 1;
                break;
            }
        }

        for (int j = 0; j <= visit_index; j++)
        {
            if (strcmp(second_spell, visited[j]) == 0)
            {
                printf("이미 나온 단어입니다.\n");
                life--;
                isVisit = 1;
                break;
            }               
        }


        if (strlen(second_spell) > 10 || strlen(second_spell) < 3)
        {
            printf("단어의 길이가 3이상 10 이하가 아닙니다.\n");
            life--;
        }
        else if (isStored == 0)
        {
            printf("단어사전에 없는 단어입니다\n");
            life--;
        }           
        else if (last_alpha != first_alpha)
        {
            printf("끝 글자와 첫 글자가 다릅니다.\n");
            life--;
        }
        else if (last_alpha == first_alpha && isVisit == 0 && isStored == 1)
        {
            score++;
            strcpy(visited[visit_index++], second_spell);
            strcpy(first_spell, second_spell);
        } 
        
        if (life == 0)
        {
            printf("모든 기회를 소진했습니다.\n");
            break;
        }

        printf("현재 점수 %d점\n\n", score); 

        isVisit = 0;
        isStored = 0;
    }

    printf("끝말잇기 종료. 총 점수는 %d점\n\n", score);

    return ;
}
void wordAnalyze()
{

    qsort(Dict, dict_len, sizeof(Dict[0]), compareByLength);
    for (int i = 0; i < 10; i++)
        printf("글자 수 : %d, %s %s\n", Dict[i].length, Dict[i].spell, Dict[i].meaning);
    printf("\n");

    qsort(Dict, dict_len, sizeof(Dict[0]), compareByGather);
    for (int i = 0; i < 10; i++)
        printf("모음 개수: %d, %s %s\n", Dict[i].gather, Dict[i].spell, Dict[i].meaning);
    printf("\n");
    return ;
}
void executeProgram()
{
    srand(time(NULL));
    storeWords();

    int op = 0;
    while (1)
    {
        printf("1 : 단어 찾기, 2 : 끝말 잇기, 3 : 단어 분석, 4 : 종료\n>> ");
        scanf("%d", &op);
        getchar();
        
        if (op == 1)
        {
            searchWords();
        }
        else if (op == 2)
        {
            concludingRemarks();
        }
        else if (op == 3)
        {
            wordAnalyze();
        }
        else if (op == 4)
        {
            break;
        }
        else
            printf("잘못된 입력\n");
    }

    printf("프로그램 종료\n");
    return;
}
int main(void)
{
    executeProgram();

    return 0;
}