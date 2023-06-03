// CBST.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CTREE.h"

using namespace std;

int main()
{
    //srand((unsigned int)time(NULL));
    srand(500);
    //CTREE tree(50);
    //tree.Tree_Insert(100);
    //tree.Tree_Insert(30);
    //tree.Tree_Insert(20);
    //tree.Tree_Insert(10);
    //tree.Tree_Insert(60);
    //tree.Tree_Insert(70);
    //tree.Tree_Insert(110);
   

    //CTREE tree(120);
    //tree.Tree_Insert(50);
    //tree.Tree_Insert(55);
    //tree.Tree_Insert(30);

    //CTREE tree(100);
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

    CTREE tree(500);
    for (int i=0;i<15;i++) 
    {
        int num = rand()%1000;
        tree.Tree_Insert(num);
    }

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
        scanf_s("%d", &input);
        printf("\n");
        switch (input)
        {
            case 1://입력
                printf("입력할 데이터를 입력하세요");
                scanf_s("%d", &tmpinput);
                printf("\n");
                tree.Tree_Insert(tmpinput);
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
                printf("%d", tree.Tree_Count(tree.GetRootNode()));
                break;
            case 7:
                printf("%d", tree.Depth_Count(tree.GetRootNode()));
                break;
        }
        printf("\n");
    }

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
