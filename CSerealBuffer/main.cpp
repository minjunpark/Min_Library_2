// CSerealBuffer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include "CSerealBuffer.h"



int main()
{
    CSerealBuffer* CSBuffer = new CSerealBuffer;
    char a = 1;
    double b = 5.14;
    char c = 0;
    double d = 0;
    *CSBuffer << a << b;
    *CSBuffer >> c >> d;
    printf("%d\n", c);
    printf("%f",d);
}