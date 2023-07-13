// CBST.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CRBT.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <wchar.h>
#include <locale.h>
#include <conio.h>
#include <map>
#include "Profile.h"
#include <queue>

#pragma comment(lib, "winmm.lib")
#include "CTREE.h"
#define RANDOM(__min__, __max__) \
	((int)(((double)((rand()<<15) | rand())) / ((RAND_MAX<<15 | RAND_MAX) + 1) \
		* (((__max__) + 1) - (__min__))) + (__min__))

using namespace std;

void RBT_INSERT_CHECK(int count,bool RBT_CHECk);
void RBT_DELETE_CHECK(int count, bool RBT_CHECK);
void Struct_Time_Check_RANDOM(int count, int start, int end, int max_seed);
int main()
{
	timeBeginPeriod(1);
	QueryPerformanceFrequency(&_P_Freq);//최초 시간대 한번 세팅
	Struct_Time_Check_RANDOM(1000,1,1000,100);
	return 0;
	//srand((unsigned int)time(NULL));
	
	//CTREE tree(50);
	//tree.Tree_Insert(100);
	//tree.Tree_Insert(30);
	//tree.Tree_Insert(20);
	//tree.Tree_Insert(10);
	//tree.Tree_Insert(60);
	//tree.Tree_Insert(70);
	//tree.Tree_Insert(110);
	CREDBLACKTREE tree;
	map<int, int> maps;

	//tree.RedBlack_Insert(20);
	//tree.RedBlack_Insert(10);
	//tree.RedBlack_Insert(50);
	//tree.RedBlack_Insert(30);
	//tree.RedBlack_Insert(80);
	//tree.RedBlack_Insert(40);
	//tree.RedBlack_Insert(35);
	//tree.RedBlack_Insert(25);
	//tree.RedBlack_Insert(37);

	tree.RedBlack_Insert(35);
	tree.RedBlack_Insert(20);
	tree.RedBlack_Insert(50);
	tree.RedBlack_Insert(10);
	tree.RedBlack_Insert(30);
	tree.RedBlack_Insert(40);
	tree.RedBlack_Insert(80);
	tree.RedBlack_Insert(37);
	tree.RedBlack_Insert(45);
	tree.RedBlack_Insert(5);
	tree.RedBlack_Insert(15);
	tree.RedBlack_Insert(25);
	tree.RedBlack_Insert(33);
	tree.RedBlack_Insert(13);
	tree.RedBlack_Insert(2);
	tree.RedBlack_Insert(27);
	//tree.RedBlack_Delete(15);
	//tree.RedBlack_Delete(33);
	//tree.RedBlack_Delete(37);
	//tree.RedBlack_Delete(35);

	//tree.RedBlack_Insert(30);
	//tree.RedBlack_Insert(35);
	//tree.RedBlack_Insert(20);
	//tree.RedBlack_Insert(10);
	//tree.RedBlack_Insert(25);
	//tree.RedBlack_Insert(50);
	//tree.RedBlack_Insert(40);
	//tree.RedBlack_Insert(80);
	//tree.RedBlack_Insert(37);

	//srand(1);
	//for (int i = 0; i < 6; i++)
	//{
	//	int num = RANDOM(1, 100);
	//	printf("%d ", num);
	//	tree.RedBlack_Insert(num);
	//}

	//for (int i = 0; i < 20; i++)
	//{
	//	int num = RANDOM(1,100);
	//	printf("%d ", num);
	//	//PRO_BEGIN(L"A");
	//	maps.insert({ num,num });
	//	tree.RedBlack_Insert(num);
	//	//PRO_END(L"A");
	//}
	//maps.erase(59);
	//tree.RedBlack_Insert(71);
	//tree.RedBlack_Insert(68);
	//tree.RedBlack_Insert(59);
	//tree.RedBlack_Insert(77);
	//tree.RedBlack_Insert(96);

	//RBT_INSERT_CHECK(2000,true);
	RBT_DELETE_CHECK(2000, false);

	//ProfileDataOutText(L"ABC");
	//printf("\n");
	//tree.RedBlack_Insert(20);
	//tree.RedBlack_Insert(10);
	//tree.RedBlack_Insert(50);
	//tree.RedBlack_Insert(30);
	//tree.RedBlack_Insert(80);
	//tree.RedBlack_Insert(40);
	//tree.RedBlack_Insert(35);
	//tree.RedBlack_Insert(25);


	//tree.Tree_Insert(5);
	//tree.Tree_Insert(3);
	//tree.Tree_Insert(2);

//	CTREE tree(120);
	//tree.Tree_Insert(50);
	//tree.Tree_Insert(55);
	//tree.Tree_Insert(30);

	//CREDBLACKTREE tree(5);
	//
	//tree.Tree_Insert(2);
	//tree.Tree_black_Insert(7);

	//tree.Tree_Insert(200);
	//tree.Tree_Insert(150);
	//tree.Tree_Insert(270);
	//tree.Tree_Insert(260);
	//tree.Tree_Insert(300);
	//tree.Tree_Insert(350);
	//tree.Tree_Insert(240);
	//tree.Tree_Insert(265);
	//tree.Tree_Insert(266);
	//tree.Tree_Insert(267);
	//tree.Tree_Insert(268);



	//for (int i=0;i<30;i++) 
	//{
	//    int num = rand()%100;
	//    tree.Tree_Insert(num);
	//}

	//CTREE tree(100);
	//tree.Tree_Insert(30);
	//tree.Tree_Insert(100);
	//tree.Tree_Insert(60);
	//tree.Tree_Insert(70);
	//tree.Tree_Insert(55);

	//tree.Tree_Insert(50);
	//tree.Tree_Insert(100);
	//tree.Tree_Insert(70);
	//tree.Tree_Insert(120);


	//tree.All_print(tree.pRoot);
	//printf("\n");
	//tree.All_print(tree.pRoot);
	//tree.printBinaryTree(tree.pRoot);

	int input = 0;
	int tmpinput = 0;
	while (1)
	{
		printf("1.데이터 입력\n");
		printf("2.데이터 삭제\n");
		printf("3.데이터 출력\n");
		printf("4.데이터 검색\n");
		printf("5.데이터 검증\n");
		printf("6.개수구하기\n");
		printf("7.깊이구하기\n");
		printf("8.오른쪽 회전테스트\n");
		printf("9.왼쪽 회전테스트\n");
		printf("10.레드블랙 트리 검증\n");
		scanf_s("%d", &input);
		printf("\n");
		switch (input)
		{
		
		case 1://입력
			printf("입력할 데이터를 입력하세요");
			scanf_s("%d", &tmpinput);
			printf("\n");
			tree.RedBlack_Insert(tmpinput);
			break;
		case 2://삭제
			printf("삭제할 데이터를 입력하세요");
			scanf_s("%d", &tmpinput);
			printf("\n");
			//tree.RedBlack_Delete(tmpinput);
			tree.Remove(tree.GetRootNode(),tmpinput);
			break;
		case 3://출력
			//tree.LevelPrint(tree.GetRootNode());
			tree.All_print(tree.GetRootNode());
			printf("\n");
			for (map<int, int>::iterator itr = maps.begin(); itr != maps.end(); ++itr) 
			{
				cout << itr->first << " ";// << endl;
			}
			cout << endl;
			//tree.printBinaryTree(tree.GetRootNode(),false);
			tree.printTree(tree.GetRootNode(), nullptr, false);
			
			//printTree(tree.GetRootNode(), nullptr, false);
			break;
		case 4://검색
			//scanf_s("검색 하고싶은 데이터를 입력하세요 %d\n", &input);
			break;
		case 5:
			printf("1이면 현재레드블랙 트리에 이상이 없습니다 %d\n", tree.RBT_CHECK(tree.GetRootNode()));
			break;
		case 6:
			printf("개수는 %d\n", tree.Tree_Count(tree.GetRootNode()));
			break;
		case 7:
			printf("깊이는 %d\n", tree.Depth_Count(tree.GetRootNode()));
			break;
		case 8:
			printf("회전할 입력할 데이터를 입력하세요");
			scanf_s("%d", &tmpinput);
			printf("\n");
			tree.Right_Rotation_Test(tmpinput);
			break;
		case 9:
			printf("회전할 입력할 데이터를 입력하세요");
			scanf_s("%d", &tmpinput);
			printf("\n");
			tree.Left_Rotation_Test(tmpinput);
			break;
		case 10:
			int result;
			printf("검증 ");
			result = tree.RBT_CHECK(tree.GetRootNode());
			printf("%d\n", result);
			break;
		}
	}
	return 0;
}

bool RBT_MAP_CHECK()
{
	//map에 같은 정보 넣은후
	//둘다 중위순회하면서 queue에 같은 데이터를 넣는다.
	//하나씩 빼면서 비교하다 다르다면 false
	//버퍼로하는 방식도 가능하겠네
}

//카운트 갯수만큼 넣으면서
//카운트의 2배의 랜덤사이 값을 넣는다
//예:100000을 넣으면 1~200000의 랜덤이 잡히고
//그사이의 값을 중복 제외하고 10만개를 넣게 만들고
//그데이터를 maps과 레드블랙 트리에 넣은후
//레드블랙 트리를 중위순회하면서 q에 데이터를 모두넣고
//masp과 트리에서 하나씩 뽑아내면서 비교한다.
//불일치하면 재현을 위해 timeseed와 문제 생긴 노드
//그리고 강제 에러를 발생시킨다.
//그리고 RBT_CHECK로 레드블랙트리의 오류가 없는지 검사한다.
//레드 연속 여부
//루트마다 블랙의 개수가 같은지
//넣은것과 나온것의 개수가 같은지
void RBT_INSERT_CHECK(int count,bool RBT_CHECK)
{
	CREDBLACKTREE* tree2;
	map<int, int>* maps2;
	queue<int>* q;
	int timeSeed = 1;

	while (1) {
		srand(timeSeed);
		tree2 = new CREDBLACKTREE;
		maps2 = new map<int, int>;
		q = new queue<int>;
		for (int i = 0; i < count; i++)
		{
			int num = RANDOM(1, (count * 2));
			maps2->insert({ num,num });
			tree2->RedBlack_Insert(num);
		}

		tree2->All_Q(tree2->GetRootNode(), q);

		for (map<int, int>::iterator itr = maps2->begin(); itr != maps2->end(); ++itr)
		{
			if (itr->first != q->front())
			{
				printf("timeSeed %d\n", timeSeed);//랜덤시드는 무엇인지
				printf("itr->first %d\n", itr->first);//어느 자식에서 문제가 생겼는지
				throw std::bad_exception{};//강제 에러발생
			}
			q->pop();
		}

		if (RBT_CHECK==true)
			tree2->RBT_CHECK(tree2->GetRootNode());

		printf("timeSeed %d\n", timeSeed);
		timeSeed++;
		delete tree2;
		delete maps2;
		delete q;
	}
}

//딜리트 체크
void RBT_DELETE_CHECK(int count, bool RBT_CHECK)
{
	CREDBLACKTREE* tree2;
	map<int, int>* maps2;
	queue<int>* q;
	int timeSeed = 1;
	
	while (1) {
		srand(timeSeed);
		tree2 = new CREDBLACKTREE;
		maps2 = new map<int, int>;
		q = new queue<int>;

		for (int i = 0; i < count; i++)
		{
			int num = RANDOM(1, (count * 2));
			maps2->insert({ num,num });
			tree2->RedBlack_Insert(num);
		}

		for (int i = 0; i < count; i++)
		{
			int num = RANDOM(1, (count * 2));
			maps2->erase(num);
			//maps2->remove(num);
			//maps2->insert({ num,num });
			tree2->Remove(tree2->GetRootNode(),num);
		}

		tree2->All_Q(tree2->GetRootNode(), q);

		for (map<int, int>::iterator itr = maps2->begin(); itr != maps2->end(); ++itr)
		{
			if (itr->first != q->front())
			{
				printf("timeSeed %d\n", timeSeed);//랜덤시드는 무엇인지
				printf("itr->first %d\n", itr->first);//어느 자식에서 문제가 생겼는지
				throw std::bad_exception{};//강제 에러발생
			}
			//rintf("map %d\n", timeSeed);
			q->pop();
		}

		if (RBT_CHECK == true)
			tree2->RBT_CHECK(tree2->GetRootNode());

		printf("timeSeed %d\n", timeSeed);
		timeSeed++;
		delete tree2;
		delete maps2;
		delete q;
	}

}

void Struct_Time_Check_RANDOM(int count, int start, int end,int max_seed) //실제 성능측정
{
	//4000
	//4가지 자료구조세팅
	CREDBLACKTREE* CRBT;//레드블랙트리
	CTREE* CBST;//이진트리
	int timeSeed = 1;

	//map
	//unmap

	//4개의 자료구조에 카운터크기만큼 랜덤한 데이터를
	//start부터 end까지의 범위에서 랜덤하게 넣고 뺴고
	while (1)
	{	
		srand(timeSeed);
		if (max_seed == timeSeed)
			break;

		CRBT = new CREDBLACKTREE;
		CBST = new CTREE;
		
		//입력
		for (int i = 0; i < count; i++)
		{
			int num = RANDOM(start, end);
			//레드블랙트리 삽입측정
			PRO_BEGIN(L"RedBlack_Insert");
			CRBT->RedBlack_Insert(num);
			PRO_END(L"RedBlack_Insert");
			
			//이진트리 입력 측정
			PRO_BEGIN(L"Tree_Insert");
			//CBST->Tree_Insert(num);
			PRO_END(L"Tree_Insert");
		}
		
		
		//검색
		for (int i = 0; i < count; i++)
		{
			int num = RANDOM(start, end);
			//레드블랙트리 삽입측정
			//PRO_BEGIN(L"RedBlack_Search");
			CRBT->RedBlack_Search_Node(num);
			//PRO_END(L"RedBlack_Search");

			//이진트리 입력 측정
			//PRO_BEGIN(L"Tree_Search");
			CBST->Tree_Search(num);
			//PRO_END(L"Tree_Search");
		}


		//삭제
		for (int i = 0; i < count; i++)
		{
			int num = RANDOM(start, end);
			//레드블랙트리 삭제측정
			PRO_BEGIN(L"RedBlack_Delete");
			CRBT->Remove(CRBT->GetRootNode(),num);
			PRO_END(L"RedBlack_Delete");

			//이진트리 삭제측정
			PRO_BEGIN(L"Tree_Delete");
			CBST->Tree_Delete(num);
			PRO_END(L"Tree_Delete");
		}

		CRBT->RBT_CHECK(CRBT->GetRootNode());

		//for (map<int, int>::iterator itr = maps2->begin(); itr != maps2->end(); ++itr)
		//{
		//	if (itr->first != q->front())
		//	{
		//		printf("timeSeed %d\n", timeSeed);//랜덤시드는 무엇인지
		//		printf("itr->first %d\n", itr->first);//어느 자식에서 문제가 생겼는지
		//		throw std::bad_exception{};//강제 에러발생
		//	}
		//	//rintf("map %d\n", timeSeed);
		//	q->pop();
		//}

		printf("timeSeed %d\n", timeSeed);
		timeSeed++;
		//ProfileReset();
		delete CRBT;
		delete CBST;
		//ProfilePrint();
	}
	ProfileDataOutText(L"CRBT_CBST_CHECK");
	//같은 데이터를 넣고 검색하고 삭제 하는 시간을 측정

}

