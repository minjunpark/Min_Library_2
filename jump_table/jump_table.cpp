// jump_table.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

int main()
{
    char bytpe;

    scanf_s("%c",&bytpe);

    switch (bytpe)
    {
        case 1:
            printf("1\n");
            break;
        case 10:
            printf("10\n");
            break;
        case 20:
            printf("20\n");
            break;
        case 24:
            printf("24\n");
            break;
        case 27:
            printf("27\n");
            break;
        case 29:
            printf("29\n");
            break;
        case 30:
            printf("30\n");
            break;
        case 33:
            printf("33\n");
            break;
        case 44:
            printf("44\n");
            break;
        case 60:
            printf("60\n");
            break;
    }
}
