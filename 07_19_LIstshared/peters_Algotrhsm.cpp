//
//#include <iostream>
//#include <Windows.h>
//#include <process.h>
//#include <conio.h>
//#include <list>
//#include <time.h>
//#include <cstdio>
//#pragma comment(lib, "Winmm.lib") //winmm.lib �߰�
//
//
//
//bool Flag[2] = {false,false};
//
//int turn=0;
//
//alignas(64)
//
//LONGLONG g_num = 0;
//void Lock1() 
//{
//	Flag[0] = true;
//	turn = 1;
//
//	while (Flag[1]==true && turn == 1) {}
//	//{
//	//	if (Flag[1]==false)
//	//	{
//	//		break;
//	//	}
//	//	if (turn != 0) 
//	//	{
//	//		break;
//	//	}
//	//}
//}
//
//void unLock1()
//{
//	Flag[0] = false;
//}
//
//void Lock2()
//{
//	Flag[1] = true;
//	turn = 0;
//
//	while (Flag[0] == true && turn == 0) {}
//	//{
//	//	if (Flag[0] == false)
//	//	{
//	//		break;
//	//	}
//	//	if (turn != 1)
//	//	{
//	//		break;
//	//	}
//	//}
//}
//
//void unLock2()
//{
//	Flag[1] = false;
//}
//
//unsigned __stdcall Thread1(void* param)
//{
//	printf("Thread1 START\n");
//	for (LONGLONG i=0; i < 200000000;i++)
//	{
//		Lock1();
//		g_num++;
//		unLock1();
//	}
//	printf("Thread1 END\n");
//	return 0;
//}
//
//unsigned __stdcall Thread2(void* param)
//{
//	printf("Thread2 START\n");
//	for (LONGLONG i = 0; i < 200000000; i++)
//	{
//		Lock2();
//		g_num++;
//		unLock2();
//	}
//	printf("Thread2 END\n");
//	return 0;
//}
//
//
//int main()
//{
//	HANDLE _CreateThread[2];
//	//���ý����� ���� SUSPEND������ ������Ű�� �����带 �ڵ�迭�� �ִ´�.
//	_CreateThread[0] = (HANDLE)_beginthreadex(nullptr, 0, Thread1, 0, CREATE_SUSPENDED, nullptr);
//	_CreateThread[1] = (HANDLE)_beginthreadex(nullptr, 0, Thread2, 0, CREATE_SUSPENDED, nullptr);
//
//	ResumeThread(_CreateThread[0]);
//	ResumeThread(_CreateThread[1]);
//
//	printf("ThreadClose START \n");
//	WaitForMultipleObjects(2, _CreateThread, true, INFINITE);//��� �����尡 �����ɶ����� ���Ѵ���ϸ鼭 Ȯ��
//	printf("ThreadClose END \n");
//	printf("%lld", g_num);
//}