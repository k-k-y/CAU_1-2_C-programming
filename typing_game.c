#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generateStr(char[], char[]);
int evalTyping(char[], char[], double); // 타자 속도를 반환하고, 오타의 위치를 표시해줌.

int main(void)
{
    srand(time(NULL));

    clock_t start, finish;
    double duration;

    char sentence[52] = "\0";
    char input_str[1000];
    char word[11];
    int score;
    int total_score = 0;

    printf("게임을 시작합니다.\n");

    for (int tc = 0; tc < 5; tc++)
    {
        printf("(%d/5) 다음을 입력하세요\n", tc + 1);

        generateStr(sentence, word);

        printf("= %s\n= ", sentence);
        
        start = clock();

        fgets(input_str, 1000, stdin);
        input_str[strlen(input_str) - 1] = '\0'; // 개행 없애주기
        
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;

        score = evalTyping(sentence, input_str, duration);
        printf("%d타/분\n", score);
        total_score += score;

        sentence[0] = '\0'; // 문장 초기화
    }

    printf("당신의 점수는 %d점 입니다.\n", total_score);
    return 0;
}

void generateStr(char sentence[], char word[])
{
    int word_num;
    int len = 0;
    while (1)
    {
        word_num = (rand() % 7) + 4; // 글자 개수 랜덤으로 정하기(4 ~ 10)

        if (strlen(sentence) + word_num > 50)
        {
            sentence[len] = '\0'; // 마지막 자리 공백 없애기
            break;
        }

        for (int i = 0; i < word_num; i++) // 랜덤 단어 만들기(A ~ Z)
        {
            int which_char = (rand() % 26);
            word[i] = 'A' + which_char;
        }
        word[word_num] = '\0';

        len = strlen(sentence) + word_num;

        strcat(sentence, word);
        sentence[len] = ' ';
        sentence[len + 1] = '\0';  
    }
    word[0] = '\0'; // word 초기화
}

int evalTyping(char sentence[], char input_str[], double duration)
{
    int score = 0;
    printf("  ");

    // 둘 중 하나만 null이어도 exit
    for (int i = 0; sentence[i] != '\0' && input_str[i] != '\0'; i++) // 점수 계산 및 위치 표시
    {
        if (sentence[i] == input_str[i])
        {
            score++;
            printf(" ");
        }
        else
            printf("^");
    }
    if (strlen(input_str) < strlen(sentence))
    {
        for (int i = strlen(input_str); sentence[i] != '\0'; i++) // input_str보다 sentence가 더 길다면, input_str 뒤의 문자들은 모두 틀림.
            printf("^");
        printf("\n");
    }   
    else
    {
        for (int i = strlen(sentence); input_str[i] != '\0'; i++) // sentence보다 input_str이 더 길다면, sentence 뒤의 문자들은 모두 틀림.
            printf("^");
        printf("\n");
    }
        

    score = round(((double)score / duration * 60.0));
    return score;
}