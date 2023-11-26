#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct city
{
    int owner; // 0: 비어있음, 1: player1, 2: player2, 3: START
    int place;
    char name[20];
} City;

typedef struct player
{
    int money;
    int place;
    int num;
} Player;

// 주사위를 굴리고 플레이어를 이동시킴
int roleDice(Player *player)
{
    int dice = rand() % 6 + 1;
    if (player->place + dice > 9)
        player->place += -9 + dice;
    else
        player->place += dice;

    return dice;
}

// 도시에 도착한 플레이어가 도시의 상태에 따라 행동
// owner = 0 && money >= 300 -> 도시를 산다
// 주인이 있는데 자신이 아님 -> money -= 600
void Action(Player *cur_player, Player *other_player, City *city, int dice)
{
    printf("player %d의 주사위 : %d\n", cur_player->num, dice);
    printf("%s ", city->name);
    if (city->owner == 0)
        printf("(주인 없음)\n");
    else if (city->owner == 1 || city->owner == 2)
        printf("(%d)\n", city->owner);

    switch (city->owner)
    {
    case 0: // 주인 없음
        if (cur_player->money >= 300)
        {
            cur_player->money -= 300;
            city->owner = cur_player->num;
            printf("player %d이 %s 구매\n", cur_player->num, city->name);
            printf("player %d의 잔고 %d\n", cur_player->num, cur_player->money);
        }
        else
        {
            printf("%s을 구매할 수 없음", city->name);
            printf("player %d의 잔고 %d\n", cur_player->num, cur_player->money);
        }
        break;
    case 3: // start 시점
        printf("player %d의 잔고 %d\n", cur_player->num, cur_player->money);
        break;
    default: // 주인 있음
        if (city->owner == other_player->num)
        {
            cur_player->money -= 600;
            other_player->money += 600;

            printf("player %d이 player %d의 도시를 방문, 통행료 지불\n", cur_player->num, other_player->num);
            if (cur_player->money >= 0)
                printf("player %d의 잔고 %d\n", cur_player->num, cur_player->money);
            else
                printf("player %d의 잔고 0\n", cur_player->num);
        }
        else
        {
            printf("player %d이 자신의 도시 방문\n", cur_player->num);
            printf("player %d의 잔고 %d\n", cur_player->num, cur_player->money);
        }
        break;
    }
    printf("\n");
}

void playTurn(City cities[10], Player *player1, Player *player2, int *turn)
{
    int dice;
    printf("<turn %d>\n", *turn);

    dice = roleDice(player1);
    Action(player1, player2, &cities[player1->place], dice);
    if (player1->money < 0)
        return;

    dice = roleDice(player2);
    Action(player2, player1, &cities[player2->place], dice);

    (*turn)++;
}

int isEnd(int turn, Player player1, Player player2)
{
    if (turn > 30 || player1.money < 0 || player2.money < 0)
        return 1;
    else
        return 0;
}

void printBoard(City cities[10], int turn)
{
    // 6 ~ 10 번째 도시 출력
    for (int i = 5; i <= 9; i++)
        printf("--------------------  ");
    printf("\n");

    for (int i = 5; i <= 9; i++)
        printf("|                  |  ");
    printf("\n");

    for (int i = 5; i <= 9; i++)
    {
        char str[21] = "|                  |";
        int start = (20 - strlen(cities[i].name)) / 2;

        for (int k = 0; cities[i].name[k] != '\0'; k++)
            str[start + k] = cities[i].name[k];

        printf("%s  ", str);
    }
    printf("\n");

    for (int i = 5; i <= 9; i++)
    {
        if (cities[i].owner == 1)
            printf("|        (1)       |  ");
        else if (cities[i].owner == 2)
            printf("|        (2)       |  ");
        else
            printf("|                  |  ");
    }
    printf("\n");

    for (int i = 5; i <= 9; i++)
        printf("|                  |  ");
    printf("\n");

    for (int i = 5; i <= 9; i++)
        printf("--------------------  ");
    printf("\n");

    for (int i = 0; i < 51; i++)
        printf(" ");
    printf("----->\n");
    printf("\n\n");
    for (int i = 0; i < 51; i++)
        printf(" ");
    printf("<-----\n");

    // 1 ~ 5 번째 도시 출력
    for (int i = 4; i >= 0; i--)
        printf("--------------------  ");
    printf("\n");

    for (int i = 4; i >= 0; i--)
        printf("|                  |  ");
    printf("\n");

    for (int i = 4; i >= 0; i--)
    {
        char str[21] = "|                  |";
        int start = (20 - strlen(cities[i].name)) / 2 + 1;

        for (int k = 0; cities[i].name[k] != '\0'; k++)
            str[start + k] = cities[i].name[k];

        printf("%s  ", str);
    }
    printf("\n");

    for (int i = 4; i >= 0; i--)
    {
        if (cities[i].owner == 1)
            printf("|        (1)       |  ");
        else if (cities[i].owner == 2)
            printf("|        (2)       |  ");
        else
            printf("|                  |  ");
    }
    printf("\n");

    for (int i = 4; i >= 0; i--)
        printf("|                  |  ");
    printf("\n");

    for (int i = 4; i >= 0; i--)
        printf("--------------------  ");
    printf("\n\n");
}

int main(void)
{
    srand(time(NULL));
    City cities[10] = {{3, 0, "START"}, {0, 1, "Seoul"}, {0, 2, "Tokyo"}, {0, 3, "Sydney"}, {0, 4, "LA"}, {0, 5, "Cairo"}, {0, 6, "Phuket"}, {0, 7, "New delhi"}, {0, 8, "Hanoi"}, {0, 9, "Paris"}};
    Player player1 = {5000, 0, 1}, player2 = {5000, 0, 2};

    int turn = 1;
    while (1)
    {
        playTurn(cities, &player1, &player2, &turn);
        printBoard(cities, turn);
        if (isEnd(turn, player1, player2) == 1)
            break;

        Sleep(1000);
    }

    printf("게임이 종료되었습니다. ");
    if (player1.money > player2.money)
        printf("player 1 승리!\n");
    else if (player1.money < player2.money)
        printf("player 2 승리!\n");
    else
        printf("무승부!\n");

    return 0;
}