// Spinlock.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

LONG a = 0;

class SpinLock
{
public:
    void Lock()
    {
        int retLock;
        while (1)
        {
            retLock = InterlockedExchange(&this->Flag, 1);
            if (retLock == 0)
            {
                break;
            }
        }

    }


    void Unlock()
    {
        InterlockedExchange(&this->Flag, 0);
    }
private:
    LONG Flag = false;
};

SpinLock SpinLocks;



unsigned WINAPI ThreadFunction(void* arg)
{
    for (int k = 0; k < 1000000; k++)
    {
        SpinLocks.Lock();
        a++;
        SpinLocks.Unlock();

    }
    printf("%d\n", a);
    return 0;
}

unsigned WINAPI ThreadFunction2(void *arg)
{
    for (int k = 0; k < 1000000; k++)
    {
        InterlockedIncrement(&a);
        //a = a + 1;
    }
    printf("%d\n", a);
    return 0;
}

int main()
{
    HANDLE hThread1;
    HANDLE hThread2;
    HANDLE hThread3;
    DWORD dwThreadID1;
    DWORD dwThreadID2;
    DWORD dwThreadID3;
    //hThread1 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadID1);
    //hThread2 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadID2);
    hThread1 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction2, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadID1);
    hThread2 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction2, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadID2);
    hThread3 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction2, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadID2);
    if (hThread1 == 0)
    {
        puts("_beginthreadex() error");
        exit(1);
    }
    if (hThread2 == 0)
    {
        puts("_beginthreadex() error");
        exit(1);
    }

    ResumeThread(hThread1);
    ResumeThread(hThread2);
    ResumeThread(hThread3);

    Sleep(3000);
    printf("OK! %d",a);
    //printf("A :%d \n", a);
    return 0;
}


