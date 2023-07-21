// 07_19_LIstshared.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <list>
#include <time.h>
#include <cstdio>
#pragma comment(lib, "Winmm.lib") //winmm.lib 추가

using namespace std;
BOOL g_Shutdown = false;
SRWLOCK g_srwlock;
list <int> g_List;
HANDLE g_Handle[6];

unsigned __stdcall PrintThread(void* param)
{
	int retValue = 0;
	int _param = *(int*)param;
	//SetEvent(g_Handle[_param]);

	printf("PrintThread START\n");
	while (!g_Shutdown)
	{
		DWORD ret = WaitForSingleObject(g_Handle[_param], 1000);
		if (ret == WAIT_TIMEOUT)
		{
			SetEvent(g_Handle[_param]);
			continue;
		}

		AcquireSRWLockShared(&g_srwlock);
		for (auto iter = g_List.begin(); iter != g_List.end(); ++iter)
		{
			printf("%d-", *iter);
		}

		ReleaseSRWLockShared(&g_srwlock);
	}
	printf("PrintThread END\n");
	return 0;
}

unsigned __stdcall DeleteThread(void* param)
{
	int _param = *(int*)param;
	printf("DeleteThread START\n");
	while (!g_Shutdown)
	{
		DWORD ret = WaitForSingleObject(g_Handle[_param], 333);
		if (ret == WAIT_TIMEOUT)
		{
			SetEvent(g_Handle[_param]);
			continue;
		}
		
		//Sleep(333);
		AcquireSRWLockExclusive(&g_srwlock);
		if (g_List.size() > 0)
			g_List.pop_back();
		ReleaseSRWLockExclusive(&g_srwlock);
	}
	printf("DeleteThread END\n");
	return 0;
}

unsigned __stdcall WorkerThread(void* param)
{
	srand(*(int*)param);
	int _param = *(int*)param;
	printf("WorkerThread %d START\n", *(int*)param);
	while (!g_Shutdown)
	{
		DWORD ret = WaitForSingleObject(g_Handle[_param], 1000);
		if (ret == WAIT_TIMEOUT)
		{
			SetEvent(g_Handle[_param]);
			continue;
		}
		//Sleep(1000);
		AcquireSRWLockExclusive(&g_srwlock);
		int retRand = rand() % 500 + 1;
		g_List.push_back(retRand);//맨뒤에 데이터를 삽입
		ReleaseSRWLockExclusive(&g_srwlock);
	}
	printf("WorkerThread %d END\n", *(int*)param);
	return 0;
}

unsigned __stdcall SaveThread(void* param)
{
	int _param = *(int*)param;
	DWORD ret;
	FILE* p_file = nullptr;
	printf("SaveThread START\n");
	while (!g_Shutdown)
	{
		WaitForSingleObject(g_Handle[_param], INFINITE);
		//ResetEvent(g_Handle[_param]);
		AcquireSRWLockShared(&g_srwlock);
		fopen_s(&p_file, " save.txt", "wb");
		int* temp;
		temp = new int(sizeof(g_List.size()));
		int iCnt = 0;
		for (auto iter = g_List.begin(); iter != g_List.end(); ++iter)
		{
			int iter_int = *iter;
			memcpy(temp+iCnt, &iter_int, sizeof(int));
			iCnt++;
		}
		fwrite(temp, sizeof(int), g_List.size(), p_file);
		fclose(p_file);
		ReleaseSRWLockShared(&g_srwlock);
	}
	printf("SaveThread END\n");
	return 0;
}

int main()
{
	InitializeSRWLock(&g_srwlock);
	
	int dwThreadID = 0;
	int intion[6] = { 0,1,2,3,4,5};
	//이벤트 핸들만들기
	g_Handle[0] = CreateEventW(nullptr, false, true, nullptr);
	g_Handle[1] = CreateEventW(nullptr, false, true, nullptr);
	g_Handle[2] = CreateEventW(nullptr, false, true, nullptr);
	g_Handle[3] = CreateEventW(nullptr, false, true, nullptr);
	g_Handle[4] = CreateEventW(nullptr, false, true, nullptr);
	g_Handle[5] = CreateEventW(nullptr, false, false, nullptr);

	HANDLE _CreateThread[6];
	//동시실행을 위해 SUSPEND값으로 정지시키고 스레드를 핸들배열에 넣는다.
	_CreateThread[0] = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread, &intion[0], CREATE_SUSPENDED, nullptr);
	_CreateThread[1] = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread, &intion[1], CREATE_SUSPENDED, nullptr);
	_CreateThread[2] = (HANDLE)_beginthreadex(nullptr, 0, WorkerThread, &intion[2], CREATE_SUSPENDED, nullptr);
	_CreateThread[3] = (HANDLE)_beginthreadex(nullptr, 0, PrintThread, &intion[3], CREATE_SUSPENDED, nullptr);
	_CreateThread[4] = (HANDLE)_beginthreadex(nullptr, 0, DeleteThread, &intion[4], CREATE_SUSPENDED, nullptr);
	_CreateThread[5] = (HANDLE)_beginthreadex(nullptr, 0, SaveThread, &intion[5], CREATE_SUSPENDED, nullptr);

	//스레드를 한번에 실행한다.
	for (int i = 0; i < 6; i++)
	{
	    ResumeThread(_CreateThread[i]);
	}

	while (1)
	{
		int key =_getch();
		if (key=='w')
		{
			//특정 키카 눌리면 SaveThread 를 깨운다.
			SetEvent(g_Handle[5]);
		}
		if (key == 's')
		{
			//특정 키가 눌리면 모든 스레드를 종료 시킴.
			g_Shutdown = true;
			SetEvent(g_Handle[5]);
			break;
		}
	}
	//모든 스레드가 종료 되었는지 확인 후 꺼짐.

	printf("ThreadClose START \n");
	WaitForMultipleObjects(6, _CreateThread, true, INFINITE);//모든 스레드가 정지될때까지 무한대기하면서 확인
	printf("ThreadClose END \n");

	return 0;
}