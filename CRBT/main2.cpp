//// CBST.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
////
//
//#include <iostream>
//#include "RBtree.h"
//#include <iostream>
//#include <time.h>
//#include <Windows.h>
//#include <wchar.h>
//#include <locale.h>
//#include <conio.h>
//#include <map>
//#include "Profile.h"
//#include <queue>
//
//#pragma comment(lib, "winmm.lib")
//#include "CTREE.h"
//#define RANDOM(__min__, __max__) \
//	((int)(((double)((rand()<<15) | rand())) / ((RAND_MAX<<15 | RAND_MAX) + 1) \
//		* (((__max__) + 1) - (__min__))) + (__min__))
//
//using namespace std;
//
//void RBT_INSERT_CHECK(int count, bool RBT_CHECk);
//void RBT_DELETE_CHECK(int count, bool RBT_CHECK);
//void Struct_Time_Check_RANDOM(int count, int start, int end, int max_seed);
//int main()
//{
//	timeBeginPeriod(1);
//	QueryPerformanceFrequency(&_P_Freq);//���� �ð��� �ѹ� ����
//	Struct_Time_Check_RANDOM(10000, 1, 10000, 2000);
//	return 0;
//	
//	return 0;
//}
//
//bool RBT_MAP_CHECK()
//{
//	//map�� ���� ���� ������
//	//�Ѵ� ������ȸ�ϸ鼭 queue�� ���� �����͸� �ִ´�.
//	//�ϳ��� ���鼭 ���ϴ� �ٸ��ٸ� false
//	//���۷��ϴ� ��ĵ� �����ϰڳ�
//}
//
////ī��Ʈ ������ŭ �����鼭
////ī��Ʈ�� 2���� �������� ���� �ִ´�
////��:100000�� ������ 1~200000�� ������ ������
////�׻����� ���� �ߺ� �����ϰ� 10������ �ְ� �����
////�׵����͸� maps�� ����� Ʈ���� ������
////����� Ʈ���� ������ȸ�ϸ鼭 q�� �����͸� ��γְ�
////masp�� Ʈ������ �ϳ��� �̾Ƴ��鼭 ���Ѵ�.
////����ġ�ϸ� ������ ���� timeseed�� ���� ���� ���
////�׸��� ���� ������ �߻���Ų��.
////�׸��� RBT_CHECK�� �����Ʈ���� ������ ������ �˻��Ѵ�.
////���� ���� ����
////��Ʈ���� ���� ������ ������
////�����Ͱ� ���°��� ������ ������
//
//
//void Struct_Time_Check_RANDOM(int count, int start, int end, int max_seed) //���� ��������
//{
//	//4000
//	//4���� �ڷᱸ������
//	RedBlackTree* CRBT;//�����Ʈ��
//	CTREE* CBST;//����Ʈ��
//	int timeSeed = 1;
//
//	//map
//	//unmap
//
//	//4���� �ڷᱸ���� ī����ũ�⸸ŭ ������ �����͸�
//	//start���� end������ �������� �����ϰ� �ְ� ����
//	while (1)
//	{
//		srand(timeSeed);
//		if (max_seed == timeSeed)
//			break;
//
//		CRBT = new RedBlackTree;
//		CBST = new CTREE;
//
//		//�Է�
//		for (int i = 0; i < 10; i++)
//		{
//			int num = RANDOM(1, 100);
//			//�����Ʈ�� ��������
//			//PRO_BEGIN(L"RedBlack_Insert");
//			CRBT->Insert(num);
//			//PRO_END(L"RedBlack_Insert");
//
//			//����Ʈ�� �Է� ����
//			//PRO_BEGIN(L"Tree_Insert");
//			//CBST->Tree_Insert(num);
//			//PRO_END(L"Tree_Insert");
//			
//		}
//		
//		//�˻�
//		for (int i = 0; i < count; i++)
//		{
//			int num = RANDOM(start, end);
//			//�����Ʈ�� ��������
//			//PRO_BEGIN(L"RedBlack_Search");
//			CRBT->Remove(num);
//			//PRO_END(L"RedBlack_Search");
//
//			//����Ʈ�� �Է� ����
//			//PRO_BEGIN(L"Tree_Search");
//			//CBST->Tree_Search(num);
//			//PRO_END(L"Tree_Search");
//			
//		}
//
//
//		//����
//		for (int i = 0; i < count; i++)
//		{
//			int num = RANDOM(start, end);
//			//�����Ʈ�� ��������
//			//PRO_BEGIN(L"RedBlack_Delete");
//			CRBT->Remove(num);
//			//PRO_END(L"RedBlack_Delete");
//
//			//����Ʈ�� ��������
//			//PRO_BEGIN(L"Tree_Delete");
//			//CBST->Tree_Delete(num);
//			//PRO_END(L"Tree_Delete");
//		}
//
//		CRBT->RBT_CHECK(CRBT->GetRootNode());
//
//		//for (map<int, int>::iterator itr = maps2->begin(); itr != maps2->end(); ++itr)
//		//{
//		//	if (itr->first != q->front())
//		//	{
//		//		printf("timeSeed %d\n", timeSeed);//�����õ�� ��������
//		//		printf("itr->first %d\n", itr->first);//��� �ڽĿ��� ������ �������
//		//		throw std::bad_exception{};//���� �����߻�
//		//	}
//		//	//rintf("map %d\n", timeSeed);
//		//	q->pop();
//		//}
//
//		printf("timeSeed %d\n", timeSeed);
//		timeSeed++;
//		//ProfileReset();
//		delete CRBT;
//		delete CBST;
//		//ProfilePrint();
//	}
//	ProfileDataOutText(L"CRBT_CBST_CHECK");
//	//���� �����͸� �ְ� �˻��ϰ� ���� �ϴ� �ð��� ����
//
//}