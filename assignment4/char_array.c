#include <stdio.h>
#pragma warning(disable : 4996)
#define CRT_SECURE_NO_WARNINGS

int main(void)
{
    char space[50];

    int index = 0;
    int op;
    int num_data = 0;
    char *ptr;

    while (index < 50)
    {
        printf("= %d바이트 남음\n> ", 50 - index);
        scanf("%d", &op);

        if (op == 1) // char
        {
            if (index + 1 > 49)
                break;

            space[index++] = op;
            scanf("%hhd", &space[index]);

            index += 1;
        }
        else if (op == 2) // short
        {
            if (index + 2 > 49)
                break;

            space[index++] = op;
            scanf("%hd", &space[index]);

            index += 2;
        }
        else if (op == 3) // int
        {
            if (index + 4 > 49)
                break;

            space[index++] = op;
            scanf("%d", &space[index]);

            index += 4;
        }
        else if (op == 4) // long long
        {
            if (index + 8 > 49)
                break;

            space[index++] = op;
            scanf("%lld", &space[index]);

            index += 8;
        }
        num_data++;
    }

    printf("= 저장 공간이 가득 찼습니다.\n");
    printf("%d\n", num_data);

    ptr = (char *)space;

    for (int i = 0; i < num_data; i++)
    {
        if (*ptr == 1)
        {
            ptr++;
            printf("%dC ", *(ptr));
            ptr++;
        }
        else if (*ptr == 2)
        {
            ptr++;
            printf("%dS ", *(short *)(ptr));
            ptr += 2;
        }
        else if (*ptr == 3)
        {
            ptr++;
            printf("%dI ", *(int *)(ptr));
            ptr += 4;
        }
        else if (*ptr == 4)
        {
            ptr++;
            printf("%lldLL ", *(long long *)(ptr));
            ptr += 8;
        }
    }

    printf("\n");
    return 0;
}