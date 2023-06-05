#pragma once
#include <iostream>
#include <queue>
#define max(a,b) (((a)>(b))?(a):(b))//��ȣ�� ������ �ѷ�����
#include <map>
using namespace std;
class CREDBLACKTREE2
{
public:
	enum
	{
		e_BLACK = 1,
		e_RED = 0
	};

	struct Node
	{
		int Data;
		char pColor = e_RED;//false ���� true ����
		Node* pParent = nullptr;
		Node* pLeft = nullptr;
		Node* pRight = nullptr;
	};

	struct Trunk
	{
		Trunk* prev;
		string str;

		Trunk(Trunk* prev, string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};

	Node* pRoot;
	Node* nil;

	int insert_Count;//��������
	int delete_Count;//�����Ѱ���
	int black_depth;//���� Ʈ�� ���� ����

public:
	//�ʱ�ȭ
	CREDBLACKTREE2();
	CREDBLACKTREE2(int data);

	Node* GetRootNode() { return pRoot; }//��Ʈ��� ��������
	virtual ~CREDBLACKTREE2();

	void delete_clear(Node* pNode);//��絥���� ����

	//����
	void RedBlack_Insert(int data);//RBT Insert
	void RedBlack_Insert_Refresh(Node* pNode);//insert�� �뷱���۾�
	//����
	bool RedBlack_Delete(int data);
	void RedBlack_Delete_Refresh(Node* _DNode);


	//�뷱�� �۾��� ����
	void Right_Rotation(Node* sNode);//����ȸ��
	void Right_Delete_Rotation(Node* sNode);//����ȸ��
	void Right_Rotation_Test(int data);//����ȸ�� �׽�Ʈ
	void  Left_Rotation(Node* sNode);//������ȸ��
	void  Left_Delete_Rotation(Node* sNode);//������ȸ��
	void  Left_Rotation_Test(int data);//������ ȸ�� �׽�Ʈ
	bool Color_swap(Node* pNode);//���� ������
	int Tree_Count(Node* pNode);//Ʈ�� ���� ��������
	int Depth_Count(Node* root);//�ִ� ���� Ȯ���ϱ�

	bool Tree_Delete(int data);//�ܼ� ��������

	//�˻�
	bool Tree_Search(int data);//�ִ� ���� ����
	Node* Tree_Search_Node(int data);//��ġ���� Nil�̸� ���ٴ¶�

	void Black_Insert(int data);//���� ���ǹ߻���

	// ��¿��Լ� ����
	void showTrunks(Trunk* p);
	void printBinaryTree(Node* pNode, bool isLeft, int space = 0, int height = 5);
	void printTree(Node* root, Trunk* prev, bool isLeft);
	void LevelPrint(Node* pNode);
	void All_print(Node* pNode);

	//�������ڵ�
	int RBT_CHECK(Node* _pNode);

	//Ʈ���� ��� �����͸� ������ȸ�ϸ鼭 q�� �ִ´�.
	void All_Q(Node* pNode, queue<int>* q)
	{
		if (pNode == nullptr || pNode == nil)
			return;

		//���� ��ȸ�� ��� ������ ���
		All_Q(pNode->pLeft, q);
		q->push(pNode->Data);//������ȸ�� ��Ʈ�� ��� ��带 �ִ´�.
		All_Q(pNode->pRight, q);
	}



};