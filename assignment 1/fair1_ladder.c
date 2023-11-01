#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int ladder[500][4] = {0,};
int result_count[5] = {0,};

void create_ladder() // 랜덤으로 사다리 만드는 함수
{
    for (int i = 0; i < 500; i++)
        ladder[i][(rand() % 4)] = 1;
}

int move_ladder(int start) // start 에서 사다리를 타고, 나오는 결과가 어디인지 반환하는 함수
{
    int cur = start; // 위치
    for (int i = 0; i < 500; i++)
    {
        if (cur < 4 && ladder[i][cur] == 1)
            cur = cur + 1;
        else if (cur > 0 && ladder[i][cur - 1] == 1)
            cur = cur - 1;
    }
    return cur;
}

void print_ladder() // 만든 사다리를 출력하는 함수
{
    printf("|   |   |   |   |\n");
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("|");
            if (ladder[i][j] == 1) printf("---");
            else printf("   ");
        }
        printf("|\n");
    }
    for (int i = 0; i < 5; i++) printf("%d -> %c ", i + 1, 'A' + move_ladder(i));
    printf("\n\n");
}
void count_result() // 1000번 각기 다른 사다리를 시행해서, 각 결과가 몇 번 나왔는지 count
{
    for (int i = 0; i < 1000; i++)
    {
        create_ladder();
        result_count[move_ladder(0)]++;
        for (int j = 0; j < 2000; j++) ladder[j / 4][j % 4] = 0; // ladder 초기화
    }
}
void print_result() // 1000번 시행을 10번 반복한 결과 출력
{
    for (int i = 0; i < 10; i++)
    {
        count_result();

        printf("%d : ", i + 1);
        for (int j = 0; j < 5; j++)
            printf("%c (%d) ", 'A' + j, result_count[j]); // 각 결과 당 횟수 출력
        printf(" %d\n", result_count[0] + result_count[1] + result_count[2] + result_count[3] + result_count[4]); // 전체 시행 횟수 출력

        for (int j = 0; j < 5; j++) result_count[j] = 0; // result 초기화
    }
}

int main(void)
{
    srand(time(NULL));
    print_result();
    return 0;
}