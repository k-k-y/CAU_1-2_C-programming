#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define max(a, b) ((a) > (b)) ? (a) : (b)

void reverseStr(char *str, int len);
int compareStr(char *str1, char *str2); // 두 숫자 문자열의 크기 비교 str1 > str2 이면 1, = 이면 0, < 이면 -1 반환(역순으로 저장된 문자열 기준)
void Add(char *a, char *b, char *c); // a + b = c
void Subtract(char *a, char *b, char *c); // a - b = c;

// 124513453245 + 121524523434 = 246037976679
// 124513453245 - 121524523434 = 2988929811
// 131412412 + 96374573457 = 96505985869
// 131412412 - 96374573457 = -96243161045
// 1 + 999999999999999 = 1000000000000000
// 1 - 999999999999999 = -999999999999998


int main(void)
{
    char operand1[81];
    char operand2[81];
    char result[82];

    while (1)
    {
        printf("input X. ");
        fgets(operand1, 81, stdin);
        operand1[strlen(operand1) - 1] = '\0'; // 개행 처리
        reverseStr(operand1, strlen(operand1)); // 역순으로 저장해야 계산이 쉬워짐. 배열의 마지막에 추가하면 되므로

        rewind(stdin); // 입력 버퍼를 안 비우면 사용자가 80개 넘게 입력했을 때 버퍼에 남아있는게 다음 fgets로 넘어감

        printf("input Y. ");
        fgets(operand2, 81, stdin);
        operand2[strlen(operand2) - 1] = '\0';
        reverseStr(operand2, strlen(operand2));

        if (strcmp(operand1, "\0") == 0 && strcmp(operand2, "\0") == 0) break; // exit condition

        rewind (stdin);

        printf("\n");

        Add(operand1, operand2, result);
        reverseStr(result, strlen(result));
        printf("X + Y = %s\n", result);

        Subtract(operand1, operand2, result);
        reverseStr(result, strlen(result));
        printf("X - Y = %s\n", result);

        printf("\n");
    }
}

void reverseStr(char *str, int len)
{
    char temp;

    for (int i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int compareStr(char *str1, char *str2)
{
    if (strlen(str1) > strlen(str2)) return 1;
    else if (strlen(str1) < strlen(str2)) return -1;
    else // 길이 같음
    {
        int len = strlen(str1);
        for (int i = len - 1; i >= 0; i--)
        {
            if (str1[i] > str2[i]) return 1;
            else if (str1[i] < str2[i]) return -1;
        }

        return 0; // str1 == str2
    }
}

void Add(char *op1, char *op2, char *result)
{
    int digit1, digit2;
    int carry = 0;
    int sum = 0;
    int len1 = strlen(op1);
    int len2 = strlen(op2);
    int maxlen = max(len1, len2);

    for (int i = 0; i < maxlen; i++)
    {
        digit1 = (i < len1) ? op1[i] - '0' : 0; // 길이 차이가 나면, 짧은 부분의 숫자를 0으로 봄
        digit2 = (i < len2) ? op2[i] - '0' : 0;

        sum = digit1 + digit2 + carry;

        if (sum > 9) // carry 발생
        {
            carry = 1;
            sum -= 10;
        }
        else
            carry = 0;

        result[i] = sum + '0'; // char 자료형으로 바꿔서 저장
    }
    
    if (carry == 1)
    {
        result[maxlen] = '1';
        result[maxlen + 1] = '\0';
    }
    else
        result[maxlen] = '\0';
}

void Subtract(char *op1, char *op2, char *result)
{
    int digit1, digit2;
    int borrow = 0;
    int sub = 0;
    char *bigOp, *smallOp;

    if (compareStr(op1, op2) > 0) // op1 > op2 (결과값이 양수)
    {
        bigOp = op1;
        smallOp = op2;
    }
    else if (compareStr(op1, op2) < 0) // op1 < op2 (결과값이 음수)
    {
        bigOp = op2;
        smallOp = op1;
    }
    else // 둘이 같으면 연산할 필요 x
    {
        strcpy(result, "0");
        return;
    }

    int big_len = strlen(bigOp);
    int small_len = strlen(smallOp);

    for (int i = 0; i < big_len; i++)
    {
        digit1 = (i < big_len) ? bigOp[i] - '0' : 0; 
        digit2 = (i < small_len) ? smallOp[i] - '0' : 0;

        int sub = digit1 - digit2 - borrow;

        if (sub < 0)
        {
            sub += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        
        result[i] = sub + '0';
    } 
    result[big_len] = '\0';
    
    for (int i = big_len - 1; i > 0 && result[i] == '0'; i--) // 필요없는 0 지우기
        result[i] = '\0';

    if (compareStr(op1, op2) < 0) // 결과값이 음수이면 -를 붙인다.
    {
        big_len = strlen(result);
        result[big_len] = '-';
        result[big_len + 1] = '\0';
    }
}


