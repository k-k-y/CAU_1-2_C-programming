#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ladder[1000][16][4];
int visited[1000] = {0,}; // 뽑은 사다리를 표시하는 visited 배열
int result_count[5] = {0,};

void print_ladder(int n) // 만든 사다리를 출력하는 함수
{
    printf("|   |   |   |   |\n");
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("|");
            if (ladder[n][i][j] == 1) printf("---");
            else printf("   ");
        }
        printf("|\n");
    }
    printf("\n");
}
void create_ladder(int n) // n번째 사다리 배열에 새로운 사다리 만들기
{
    for (int i = 0; i < 16; i++)
        ladder[n][i][rand() % 4] = 1;
}
int move_ladder(int n, int start) // start 번째에서 사다리를 타고, 나오는 결과가 어디인지 반환하는 함수
{
    int cur = start; // 위치
    for (int i = 0; i < 16; i++)
    {
        if (cur < 4 && ladder[n][i][cur] == 1)
            cur = cur + 1;
        else if (cur > 0 && ladder[n][i][cur - 1] == 1)
            cur = cur - 1;
    }
    return cur;
}
int is_ladder(int n, int dest) // 맞는 사다리인지 확인
{
    for (int i = 0; i < 5; i++)
        if (move_ladder(n, i) != (dest + i) % 5) return 0; // 5개 중 하나라도 맞지 않으면 false
    return 1; // 모두 맞으면 true
}
// 1 2 3 4 5에 대응하는 결과값이  12345, 23451, 34512, 45123, 51234인 사다리 각각 200개씩 만들기
void create_1000_ladder()
{
    int n;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 200; j++)
        {
            n = i * 200 + j;
            create_ladder(n);
            if (is_ladder(n, i) == 0) // 사다리가 조건에 맞지 않으면 다시 만들기
            {
                j--;
                for (int k = 0; k < 64; k++) ladder[n][k / 4][k % 4] = 0; // ladder 초기화
            }
        }
}
void count_result()
{
    int count = 0;
    while (count < 1000)
    {
        int num = rand() % 1000;
        if (visited[num] == 0)
        {
            // print_ladder(num);
            result_count[move_ladder(num, 0)]++; // count번째 사다리의, 1번째 출발지점에서 출발
            visited[num] = 1; // 방문 표시
            count++;
        }
    }
}
void print_result() // 사다리 타기 1000번 시행한 결과 출력
{
    for (int i = 0; i < 5; i++)
        printf("%c (%d) ", 'A' + i, result_count[i]); // 각 결과 당 횟수 출력
    printf("%d\n", result_count[0] + result_count[1] + result_count[2] + result_count[3] + result_count[4]); // 전체 시행 횟수 출력
}

int main(void)
{
    srand(time(NULL));
    create_1000_ladder();
    count_result();
    print_result();
    return 0;
}