// Logger.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CLOG.h"
using namespace std;
int main()
{
    char test[200];

    for (int i=0;i<200;i++) 
    {
        test[i] = i;
    }
    CLOG::GetInstance()->LOG_SET_DIRECTORY(L"TEST");
    CLOG::GetInstance()->LOG_SET_LEVEL(CLOG::LOG_LEVEL_DEBUG);
    CLOG::GetInstance()->LOG_HEX(L"Battle", CLOG::LOG_LEVEL_SYSTEM,
    reinterpret_cast<BYTE*>(test),200, L"[DBAcc]:%u [Slot]:%d [GameAcc]:%d d [RandKey]:%d");
    
    //std::cout << "Hello World!\n";
    ////CLOG::GetInstance()->;
    //CLOG::GetInstance()->LOG(L"Battle", CLOG::LOG_LEVEL_SYSTEM,
    //    L"[DBAcc]:%u [Slot]:%d [GameAcc]:%d d [RandKey]:%d");
    //CLOG::GetInstance()->LOG(L"Battle", CLOG::LOG_LEVEL_SYSTEM,
    //    L"[DBAcc]:%u [Slot]:%d [GameAcc]:%d d [RandKey]:%d");
    //CLOG::GetInstance()->LOG(L"Battle", CLOG::LOG_LEVEL_DEBUG,
    //    L"[DBAcc]:%u [Slot]:%d [GameAcc]:%d d [RandKey]:%d");
    //CLOG::GetInstance()->LOG(L"Battle", CLOG::LOG_LEVEL_SYSTEM,
    //    L"TLQKF");

    //CLOG::GetInstance()->LOG_SET_LEVEL(CLOG::LOG_LEVEL_SYSTEM);
    //CLOG::GetInstance()->LOG(L"Battle", CLOG::LOG_LEVEL_SYSTEM,
    //    L"[DBAcc]:%u [Slot]:%d [GameAcc]:%d d [RandKey]:%d");
    //CLOG::GetInstance()->LOG(L"Battle", CLOG::LOG_LEVEL_DEBUG,
    //    L"[DBAcc]:%u [Slot]:%d [GameAcc]:%d d [RandKey]:%d");
    //CLOG::GetInstance()->LOG(L"Battle", CLOG::LOG_LEVEL_SYSTEM,
    //    L"TLQKF");

    return 0;
}
