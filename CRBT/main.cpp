// CBST.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CRBT.h"

using namespace std;

int main()
{
	//srand((unsigned int)time(NULL));
	srand(300);
	//CTREE tree(50);
	//tree.Tree_Insert(100);
	//tree.Tree_Insert(30);
	//tree.Tree_Insert(20);
	//tree.Tree_Insert(10);
	//tree.Tree_Insert(60);
	//tree.Tree_Insert(70);
	//tree.Tree_Insert(110);
	CREDBLACKTREE tree;

	//tree.RedBlack_Insert(71);
	//tree.RedBlack_Insert(68);
	//tree.RedBlack_Insert(59);
	//tree.RedBlack_Insert(77);
	//tree.RedBlack_Insert(96);
	for (int i = 0; i < 15; i++)
	{
		int num = rand() % 100;
		printf("%d ", num);
		tree.RedBlack_Insert(num);
	}
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

	//CTREE tree(120);
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
			tree.Tree_Delete(tmpinput);
			break;
		case 3://출력
			tree.LevelPrint(tree.GetRootNode());
			//tree.printBinaryTree(tree.GetRootNode(),false);
			tree.printTree(tree.GetRootNode(), nullptr, false);
			//printTree(tree.GetRootNode(), nullptr, false);
			break;
		case 4://검색
			//scanf_s("검색 하고싶은 데이터를 입력하세요 %d\n", &input);
			break;
		case 5:
			printf("%d", tree.BSTCHECK(tree.GetRootNode()));
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
		}
	}
	return 0;
}