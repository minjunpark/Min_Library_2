#include <Windows.h>
#include <process.h>
#include <iostream>




int g_Data = 0;//가상의 데이터 처리
alignas(64)//인터록함수 쓰는거니까 변수 떨어뜨려두자
int g_Connect = 0;//접속자 수
alignas(64)
bool g_Shutdown = false;//얘도 계속 참조하는 애니까 떨구는게 맞지 않을까?
HANDLE g_Handle[5];
//같은 시드면 똑같이 넣고 빼고를 반복해서 계속 0만나온다 
//time null로 할때도 값을 바꿔가면서 해야될듯
//버그확인위해서 일단 고정시드로 확인하면서 디버깅

unsigned __stdcall AcceptThread(void* param)
{
    srand(1);
    int retValue = 0;
    int _param = *(int*)param;
    SetEvent(g_Handle[_param]);

    printf("AcceptThread START\n");
    while (!g_Shutdown)
    {
        int retRand = rand() % 900 + 100;//100에서 1000사이의값을 가져온다.
        Sleep(retRand);//100에서 1000사이만큼 논다
        retValue = _InterlockedIncrement((LONG*)&g_Connect);//1씩 더하기
    }
    printf("AcceptThread END\n");
    return 0;
}

unsigned __stdcall DisconnectThread(void* param)
{
    srand(5);
    int retValue = 0;
    int _param = *(int*)param;
    SetEvent(g_Handle[_param]);
    printf("DisconnectThread START\n");
    while (!g_Shutdown)
    {
        int retRand = rand() % 900 + 100;//100에서 1000사이의값을 가져온다.
        Sleep(retRand);//100에서 1000사이만큼 논다
        //retValue = InterlockedCompareExchange((LONG*)& g_Connect, 0, 0);//비교해서 넣었는데 0
        retValue = _InlineInterlockedAdd((LONG*)&g_Connect, 0);//비교하는것보다 단순더하고 리턴하는게 더 적을테니까
        if (retValue <= 0)//만약에 g_Conncet가 0이거나 그것보다 작다면 0을 리턴할거니까 0이하로 갈이유가 없음
            continue;//다시 컨티뉴해서 랜덤값 활용해서 100~900ms안에 실행 
        retValue = _InterlockedDecrement((LONG*)&g_Connect);//만약 0이 아닌데 여기까지오면 유저수를 빼야한다.
    }
    printf("DisconnectThread END\n");
    return 0;
}

unsigned __stdcall UpdateThread(void* param)
{
    srand(time(nullptr));
    int retValue = 0;
    int _param = *(int*)param;
    SetEvent(g_Handle[_param]);
    printf("UpdateThread START\n");
    while (!g_Shutdown)
    {
        Sleep(10);//10ms 마다 1씩더하고 
        retValue = _InterlockedIncrement((LONG*)&g_Data);
        if (retValue % 1000 == 0)//100으로 나눴을때 나머지가 0이라면 
        {
            printf("g_Data : %d\n", retValue);//이것을 출력
        }
    }
    printf("UpdateThread END\n");
    return 0;
}

//+ beginthreadex 를 사용
//
//+ 모든 변수 및 출력은 동기화가 이루어지도록 안전하게 되어야 함.
//+ interlocked 로 해결되는 경우는 interlocked 사용.
//+ interlocked 로 해결이 안되는 경우는 critical_section 사용.
//+ critical_section 사용 후 srw 으로 변경 테스트
//+ 모든 스레드는 할일이 없는경우 block 상태로 쉬도록 합니다.
//
//+ 모든 스레드는 g_Shutdown 이 true 가 되면 종료됨.
//
//+ main 스레드는 모든 스레드가 종료 된 후에 종료처리.
//
//+ 메인에서 스레드의 종료 확인은 WaitForMultipleObjects 사용.

int main()
{
    int dwThreadID = 0;
    int a[5] = { 0,1,2,3,4 };
    //이벤트 핸들만들기
    g_Handle[0] = CreateEvent(nullptr, false, false, nullptr);
    g_Handle[1] = CreateEvent(nullptr, false, false, nullptr);
    g_Handle[2] = CreateEvent(nullptr, false, false, nullptr);
    g_Handle[3] = CreateEvent(nullptr, false, false, nullptr);
    g_Handle[4] = CreateEvent(nullptr, false, false, nullptr);

    HANDLE _CreateThread[5];
    //동시실행을 위해 SUSPEND값으로 정지시키고 스레드를 핸들배열에 넣는다.
    _CreateThread[0] = (HANDLE)_beginthreadex(nullptr, 0, UpdateThread, &a[0], CREATE_SUSPENDED, nullptr);
    _CreateThread[1] = (HANDLE)_beginthreadex(nullptr, 0, UpdateThread, &a[1], CREATE_SUSPENDED, nullptr);
    _CreateThread[2] = (HANDLE)_beginthreadex(nullptr, 0, UpdateThread, &a[2], CREATE_SUSPENDED, nullptr);
    _CreateThread[3] = (HANDLE)_beginthreadex(nullptr, 0, AcceptThread, &a[3], CREATE_SUSPENDED, nullptr);
    _CreateThread[4] = (HANDLE)_beginthreadex(nullptr, 0, DisconnectThread, &a[4], CREATE_SUSPENDED, nullptr);

    //WaitForMultipleObjects(5, g_Handle, true, INFINITE); SUSPEND하고 실행하면 안된다.
    //setEvent가 호출되지 않아서 논시그널 상태이기 때문에 무한 대기가 발생한다.

    //스레드를 한번에 실행한다.
    for (int i = 0; i < 5; i++)
    {
        ResumeThread(_CreateThread[i]);
    }


    //WaitForMultipleObjects();
    int retConncet = 0;
    //20초동안 1초마다 정지하면서 현재 접속한 유저수를 출력
    for (int i = 0; i < 20; i++)
    {
        Sleep(1000);
        //retConncet = _InlineInterlockedAdd((LONG*)&g_Connect, 0);//
        //printf("g_Connect : %d\n", retConncet);//초마다 Concnet값을 가져온다.
        printf("g_Connect : %d\n", g_Connect);//1초마다 연결된 유저를 출력한다.
    }
    
    g_Shutdown = true;//모든스레드를 정지시킬것이다. 얘는 굳이 동기화 안해도 될듯?
    
    printf("ThreadClose START \n");
    WaitForMultipleObjects(5, _CreateThread, true, INFINITE);//모든 스레드가 정지될때까지 무한대기하면서 확인
    //스레드가 리턴으로 종료되지 않는이상 여기서 벗어나지 않는다.
    printf("ThreadClose END \n");

    return 0;
}
