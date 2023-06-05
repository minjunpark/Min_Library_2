#include "CRT2.h"

CREDBLACKTREE2::CREDBLACKTREE2()
{
	nil = new Node;
	nil->pParent = nullptr;
	nil->pColor = e_BLACK;
	nil->pLeft = nullptr;
	nil->pRight = nullptr;
	black_depth = 0;
	insert_Count = 0;
	delete_Count = 0;

	pRoot = nullptr;

};

CREDBLACKTREE2::CREDBLACKTREE2(int data)
{
	nil = new Node;
	nil->pParent = nullptr;
	nil->pColor = e_BLACK;
	nil->pLeft = nullptr;
	nil->pRight = nullptr;

	//Ʈ���ʱ�ȭ
	pRoot = new Node;
	if (pRoot == nullptr)
		return;
	pRoot->pColor = e_BLACK;
	pRoot->Data = data;
	pRoot->pParent = nil;
	pRoot->pLeft = nil;
	pRoot->pRight = nil;
}

CREDBLACKTREE2::~CREDBLACKTREE2()
{
	delete_clear(pRoot);

	delete nil;

}

void CREDBLACKTREE2::delete_clear(Node* pNode)
{
	if (pNode == nullptr || pNode == nil)
		return;

	//���� ��ȸ�� ��� ������ ��ȸ
	delete_clear(pNode->pLeft);
	delete_clear(pNode->pRight);
	delete pNode;//��� �Ҵ�� �������
};

//����
void CREDBLACKTREE2::RedBlack_Insert(int data)
{
	if (data <= 0) //0������ �����ʹ� ó������ �ʰڴ�.
		return;

	if (pRoot == nullptr)//��Ʈ��尡 ���ٸ�
	{
		pRoot = new Node;
		pRoot->pColor = e_BLACK;//��
		pRoot->Data = data;
		pRoot->pParent = nil;//��Ʈ��� �θ�� ����.
		pRoot->pLeft = nil;
		pRoot->pRight = nil;
		insert_Count++;
		return;//��Ʈ��� �����ϰ� ����
	}

	//��Ʈ��尡 �ִ� ���¿����� ������ �Է�
	Node* pNode = nullptr;
	Node* cNode = pRoot;//��Ʈ ������ ����
	Node* insertNode = nullptr;

	while (cNode != nil)//�־���ϴ� ��ġ�� Ž���Ѵ�.
	{
		if (cNode->Data == data)//�ߺ������ʹ� ����������Ѵ�.
			return;

		pNode = cNode;//�θ� ��带 �����Ѵ�.

		if (cNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			cNode = cNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			cNode = cNode->pRight;
		}
	}

	//�������Դٴ°� ������忡 �����ߴٴ� ��
	//������ ��带 �����
	insertNode = new Node;
	insertNode->Data = data;
	insertNode->pColor = e_RED;//��ó�� �Է½� �ݵ�� ���������� �����Ѵ�.
	insertNode->pParent = pNode;//�θ� �ִ´�.
	insertNode->pLeft = nil;
	insertNode->pRight = nil;

	insert_Count++;

	if (pNode->Data > data)//�θ� ��庸�� �۴ٸ� ��������
		pNode->pLeft = insertNode;
	else//�θ� ��庸�� ũ�ٸ� ����������
		pNode->pRight = insertNode;

	///////////////////////////////////////////////////////////
	///������� �����Ʈ�� ����//////////////////////////////
	///////////////////////////////////////////////////////////

	RedBlack_Insert_Refresh(insertNode);
}

void CREDBLACKTREE2::RedBlack_Insert_Refresh(Node* pNode)
{
	Node* _MNode = pNode;
	Node* _PNode = _MNode->pParent;
	Node* _GNode = _PNode->pParent;
	Node* _UNode;

	while (1)
	{
		_PNode = _MNode->pParent;
		_GNode = _PNode->pParent;

		if (_GNode->pLeft == _PNode)
			_UNode = _GNode->pRight;
		else
			_UNode = _GNode->pLeft;

		if (_PNode->pColor == e_RED)//���� ���� �θ� RED �����?
		{
			if (_UNode->pColor == e_BLACK)//������ ����Ʈ���ϋ�
			{
				if (_GNode->pLeft == _PNode//�θ� �Ҿƹ��� �����ڽ�
					&& _PNode->pLeft == _MNode)//���� �θ��� �����ڽ�
				{
					//1.�θ�� �Ҿƹ����� ����� �ٲ� ��
					Color_swap(_PNode);
					Color_swap(_GNode);

					//2.�Ҿƹ��� �������� ���������� ȸ��
					Right_Rotation(_GNode);
				}
				else if (_GNode->pRight == _PNode//�θ� �Ҿƹ����� ������ �ڽ�
					&& _PNode->pRight == _MNode)//���� �θ��� �������ڽ�
				{
					//1.�θ�� �Ҿƹ����� ���� ����� �ٲ� ��
					Color_swap(_PNode);
					Color_swap(_GNode);
					//2.�Ҿƹ��� �������� ���������� ȸ��
					Left_Rotation(_GNode);
				}
				else if (_GNode->pLeft == _PNode//�θ� �Ҿƹ��� �����ڽ�
					&& _PNode->pRight == _MNode)//���� �θ��� �������ڽ�
				{
					Left_Rotation(_PNode);

					Color_swap(_MNode);
					Color_swap(_GNode);

					Right_Rotation(_GNode);
				}
				else if (_GNode->pRight == _PNode//�θ� �Ҿƹ��� ������
					&& _PNode->pLeft == _MNode)//���� �θ��� �����ڽ�
				{
					Right_Rotation(_PNode);

					Color_swap(_MNode);
					Color_swap(_GNode);

					Left_Rotation(_GNode);
				}
			}
			else//������ ����Ʈ���϶�
			{
				if (_GNode->pColor == e_BLACK)//�Ҿƹ����� ���̶�� �����
					Color_swap(_GNode);

				Color_swap(_GNode->pLeft);//�Ҿƹ����� ���� �ڽ� ���带 ������->������� ������ü�� ���ۺ��� �θ�� �����
				Color_swap(_GNode->pRight);//�Ҿƹ����� ���� �ڽ� ���带 ������->������ ����Ʈ���� �̱⶧����

				if (_GNode == pRoot)//���� �Ҿƹ����� ��Ʈ����� ������ �ٲ��ش�.
					_GNode->pColor = e_BLACK;

				if (_GNode->pColor == e_RED)//���� �̵ڿ� �Ҿƹ����� ����� �ٲ���¶��
				{
					//RedBlack_Insert_Refresh(_GNode);//�ٽ� �Ҿƹ������� ������ ����.
					_MNode = _GNode;
				}
			}
		}

		if (_MNode != _GNode)
		{//���� ��尡 ���� �ʴٸ� ������ ����Ʈ���� �ƴϸ�
		 //���� �Ҿƹ����� ��Ʈ�� �ƴϰų� �Ҿƹ����� ����� �ٲ�� �ƴ϶� ���� �����̱� ������
			break;
		}

		if (pRoot->pColor == e_RED)//��Ʈ��尡 ������ ������ �ٲ��ش�.
			pRoot->pColor = e_BLACK;
	}
}

void CREDBLACKTREE2::Right_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pLeft == nil)//�������°��� �ҳ��� ������ �ʴ´�.
	//	return;

	Node* lNode = sNode->pLeft;
	//if (lNode == nil || lNode == nullptr)//ȸ���Ϸ��µ� ���ʳ�� �����Ͱ� ������ ȸ���Ұ�
	//	return;

	if (lNode->pRight != nil)
	{
		sNode->pLeft = lNode->pRight;
		sNode->pLeft->pParent = sNode;
	}
	else
	{
		sNode->pLeft = nil;
	}
	lNode->pRight = sNode;

	lNode->pParent = sNode->pParent;

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//���� �̵��Ϸ��� ��尡 Root�����
	{
		pRoot = lNode;//LNode�� ��Ʈ�� �ٲ��ش�.
	}
}



void  CREDBLACKTREE2::Left_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pRight == nil)//�������°��� �ҳ��� ������ �ʴ´�.
	//	return;

	Node* lNode = sNode->pRight;

	//if (lNode == nil || lNode == nullptr)//ȸ���Ϸ��µ� ������ ��� �����Ͱ� ���ٸ� ȸ���Ұ�
	//	return;

	if (lNode->pLeft != nil)
	{
		sNode->pRight = lNode->pLeft;
		sNode->pRight->pParent = sNode;
	}
	else
	{
		sNode->pRight = nil;
	}
	lNode->pLeft = sNode;

	lNode->pParent = sNode->pParent;

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//���� �̵��Ϸ��� ��尡 Root�����
		pRoot = lNode;//LNode�� ��Ʈ�� �ٲ��ش�.
}


void CREDBLACKTREE2::Right_Delete_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pLeft == nil)//�������°��� �ҳ��� ������ �ʴ´�.
	//	return;

	Node* lNode = sNode->pLeft;
	//if (lNode == nil || lNode == nullptr)//ȸ���Ϸ��µ� ���ʳ�� �����Ͱ� ������ ȸ���Ұ�
	//	return;

	if (lNode->pRight != nil)
	{
		sNode->pLeft = lNode->pRight;
		sNode->pLeft->pParent = sNode;
	}
	else
	{
		sNode->pLeft = nil;
	}
	lNode->pRight = sNode;

	lNode->pParent = sNode->pParent;

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//���� �̵��Ϸ��� ��尡 Root�����
	{
		pRoot = lNode;//LNode�� ��Ʈ�� �ٲ��ش�.
	}
}



void  CREDBLACKTREE2::Left_Delete_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pRight == nil)//�������°��� �ҳ��� ������ �ʴ´�.
	//	return;

	Node* lNode = sNode->pRight;

	//if (lNode == nil || lNode == nullptr)//ȸ���Ϸ��µ� ������ ��� �����Ͱ� ���ٸ� ȸ���Ұ�
	//	return;

	if (lNode->pLeft != nil)
	{
		sNode->pRight = lNode->pLeft;
		sNode->pRight->pParent = sNode;
	}
	else
	{
		sNode->pRight = nil;
	}
	lNode->pLeft = sNode;

	lNode->pParent = sNode->pParent;

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//���� �̵��Ϸ��� ��尡 Root�����
		pRoot = lNode;//LNode�� ��Ʈ�� �ٲ��ش�.
}



bool CREDBLACKTREE2::Color_swap(Node* pNode)
{
	if (pNode == nil || pNode == nullptr)
		return false;

	if (pNode->pColor == e_BLACK)
		pNode->pColor = e_RED;
	else
		pNode->pColor = e_BLACK;

	return true;
}

int CREDBLACKTREE2::Tree_Count(Node* pNode)
{
	int count = 0;//������ �ʱ�ȭ�ؾ� �ϳ��� ī��Ʈ�ȴ�.���ϸ� ���丮��ǹ���
	if (pNode != nullptr && pNode != nil)
	{
		count = 1 + Tree_Count(pNode->pLeft) + Tree_Count(pNode->pRight);
	}
	return count;
}

int CREDBLACKTREE2::Depth_Count(Node* root)
{
	int height = 0;
	if (root != nullptr && root != nil)
	{
		int left = Depth_Count(root->pLeft);//���ʳ�� ��Ȯ���ϰ� ����
		int right = Depth_Count(root->pRight);//�����ʳ�� �� Ȯ���ϰ� ����

		//��Ʈ ���� �ݵ�� ���ϱ� 1ī��Ʈ�ϰ�
		height = 1;
		if (left > right)
			height += left;
		else
			height += right;
	}
	return height;
}

//����
bool CREDBLACKTREE2::RedBlack_Delete(int data)
{
	Node* pNode = nil;
	Node* cNode = pRoot;
	Node* sNode = nullptr;
	if (delete_Count == 13)
	{
		printf("delete count %d\n", delete_Count);
	}
	printf("delete count %d\n", delete_Count);

	//�켱 �����ؾ��ϴ� ����� ��ġ�� Ž���Ѵ�.
	while (cNode != nil)
	{
		if (cNode->Data == data)//�����ؾ��ϴ� ��忡 �����ߴٸ�
			break;//�ݺ����� Ż���Ѵ�.

		pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.

		if (cNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			cNode = cNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			cNode = cNode->pRight;
		}
	}

	if (cNode == nil)//�����Ͱ� ���ٴ� ���̹Ƿ� �������� �ʰ� �����Ѵ�.
		return false;

	//���� cNode ��ġ�� �����ؾ��ϴ� ��ġ��.
	//������ ��尡(1) �ܸ� ����� ���
	if (cNode->pColor == e_RED) //�����Ǵ� ��尡 �������� ����Ʈ��������� �׳� �����ع����� �̻����.
	{
		if (cNode->pLeft == nil && cNode->pRight == nil)//�ڽ��� ���� �����
		{
			if (pNode == nil)//��Ʈ ����ϰ��
				pRoot = nullptr;//��Ʈ ��带 �����Ѵ�.->�̹ݺ��� Ż��� cNode�� ��Ʈ �ڵ� ���ŵ�
			else if (pNode->pLeft == cNode) //�θ����� ���ʳ�����
			{
				pNode->pLeft = nil;//���ʳ�� nil����
			}
			else//�θ����� �����ʳ����
			{
				pNode->pRight = nil;//�����ʳ�� �ʱ�ȭ
			}
		}
		//������ ��尡(3) �� ���� ����Ʈ���� ������ �ִ� ���
		else if (cNode->pLeft != nil && cNode->pRight != nil)
		{
			Node* nNode = cNode;//���� ��ġ ����
			pNode = nil;

			//cNode = cNode->pRight;//�����ʳ��� �ѹ��̵�

			cNode = cNode->pLeft;//���ʳ��� �ѹ��̵�

			//���� ����Ʈ���� ���� ū���� ã�´�.
			while (cNode->pRight != nil)
			{
				pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.
				cNode = cNode->pRight;//��� ���������� �̵�
			}

			nNode->Data = cNode->Data;//������ ������� ������Ʈ

			if (pNode != nil)//��Ʈ��尡 �ƴҰ��
			{
				pNode->pRight = cNode->pLeft;//�θ��尡 ��Ʈ���Ǿ� �����Ǿ� �ϴ°��� �ڽ����� �޾ƾ��Ѵ�.
				cNode->pLeft->pParent = pNode;
			}
			else if (pNode == nil)//��Ʈ����ϰ��
			{
				nNode->pLeft = cNode->pLeft;//�θ� ��Ʈ�����
				cNode->pLeft->pParent = nNode;
			}

			//�ٷ� ������ ��带 �޴°� �����ʳ���� �ڽ��� �޴´� nil�̶�� �װʹ�� �������.
		}
		//������ ��尡(2) �ϳ��� ����Ʈ���� ������ �ִ� ���
		else if (cNode->pLeft != nil)//���� ��常 �������
		{
			if (pNode == nil) //��Ʈ ����� ���
			{//�����ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� ��Ʈ�� ����� �׳� ��ĭ ����.
				Node* nNode = pRoot->pLeft;//������ ��� ��ġ����
				pRoot->Data = cNode->pLeft->Data;//��Ʈ ��� �����;�����Ʈ
				pRoot->pRight = cNode->pLeft->pRight;//��Ʈ ��� ������ ������Ʈ
				pRoot->pLeft = cNode->pLeft->pLeft;//��Ʈ��� ������ ������Ʈ
				cNode = nNode;//������ ��带 �����.
			}
			else if (pNode->Data > cNode->Data)//�����ؾ��ϴ� �����Ͱ� �θ� ��庸�� �۴ٸ�
			{
				pNode->pLeft = cNode->pLeft;//���� �����ڽ��� �θ����� �������� �̵���Ų��.
				cNode->pLeft->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pLeft;//���� �����ڽ��� �θ����� ���������� �̵���Ų��.
				cNode->pLeft->pParent = pNode;
			}
		}
		else if (cNode->pRight != nil)//�����ʳ�常 �������
		{
			if (pNode == nil)//��Ʈ ����� ���
			{//���ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� �׳� ��ĭ ����
				Node* nNode = pRoot->pRight;//���� ��ġ ����
				pRoot->Data = cNode->pRight->Data;
				pRoot->pLeft = cNode->pRight->pLeft;
				pRoot->pRight = cNode->pRight->pRight;
				cNode = nNode;//���������� ���� cNode������Ʈ
			}
			else if (pNode->Data > cNode->Data)//�����ϴ� �����Ͱ� �θ��庸�� �۴ٸ�
			{
				pNode->pLeft = cNode->pRight;//���� ������ �ڽ��� �θ����� �������� �̵���Ų��.
				cNode->pRight->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pRight;//���� ������ �ڽ��� �θ����� ���������� �̵���Ų��.
				cNode->pRight->pParent = pNode;
			}
		}
	}
	//���̶��
	else if (cNode->pColor == e_BLACK)
	{
		//���� cNode ��ġ�� �����ؾ��ϴ� ��ġ��.
		//������ ��尡(1) �ܸ� ����� ���
		if (cNode->pLeft == nil && cNode->pRight == nil)//�ڽ��� ���� �����
		{

		}
		//������ ��尡(3) �� ���� ����Ʈ���� ������ �ִ� ���
		else if (cNode->pLeft != nil && cNode->pRight != nil)
		{
			Node* nNode = cNode;//���� ��ġ ����
			pNode = nil;

			//cNode = cNode->pRight;//�����ʳ��� �ѹ��̵�

			cNode = cNode->pLeft;//���ʳ��� �ѹ��̵�

			//���� ����Ʈ���� ���� ū���� ã�´�.
			while (cNode->pRight != nil)
			{
				pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.
				cNode = cNode->pRight;//��� ���������� �̵�
			}

			nNode->Data = cNode->Data;//������ ������� ������Ʈ
			/// <summary>
			/// //////////////////
			/// </summary>
			/// <param name="data"></param>
			/// <returns></returns>
			if (cNode->pColor == e_RED) //�����Ǵ� ��尡 �������� ����Ʈ��������� �׳� �����ع����� �̻����.
			{
				if (cNode->pLeft == nil && cNode->pRight == nil)//�ڽ��� ���� �����
				{
					if (pNode == nil)//��Ʈ ����ϰ��
						pRoot = nullptr;//��Ʈ ��带 �����Ѵ�.->�̹ݺ��� Ż��� cNode�� ��Ʈ �ڵ� ���ŵ�
					else if (pNode->pLeft == cNode) //�θ����� ���ʳ�����
					{
						pNode->pLeft = nil;//���ʳ�� nil����
					}
					else//�θ����� �����ʳ����
					{
						pNode->pRight = nil;//�����ʳ�� �ʱ�ȭ
					}
				}
				//������ ��尡(3) �� ���� ����Ʈ���� ������ �ִ� ���
				else if (cNode->pLeft != nil && cNode->pRight != nil)
				{
					Node* nNode = cNode;//���� ��ġ ����
					pNode = nil;

					//cNode = cNode->pRight;//�����ʳ��� �ѹ��̵�

					cNode = cNode->pLeft;//���ʳ��� �ѹ��̵�

					//���� ����Ʈ���� ���� ū���� ã�´�.
					while (cNode->pRight != nil)
					{
						pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.
						cNode = cNode->pRight;//��� ���������� �̵�
					}

					nNode->Data = cNode->Data;//������ ������� ������Ʈ

					if (pNode != nil)//��Ʈ��尡 �ƴҰ��
					{
						pNode->pRight = cNode->pLeft;//�θ��尡 ��Ʈ���Ǿ� �����Ǿ� �ϴ°��� �ڽ����� �޾ƾ��Ѵ�.
						cNode->pLeft->pParent = pNode;
					}
					else if (pNode == nil)//��Ʈ����ϰ��
					{
						nNode->pLeft = cNode->pLeft;//�θ� ��Ʈ�����
						cNode->pLeft->pParent = nNode;
					}

					//�ٷ� ������ ��带 �޴°� �����ʳ���� �ڽ��� �޴´� nil�̶�� �װʹ�� �������.
				}
				//������ ��尡(2) �ϳ��� ����Ʈ���� ������ �ִ� ���
				else if (cNode->pLeft != nil)//���� ��常 �������
				{
					if (pNode == nil) //��Ʈ ����� ���
					{//�����ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� ��Ʈ�� ����� �׳� ��ĭ ����.
						Node* nNode = pRoot->pLeft;//������ ��� ��ġ����
						pRoot->Data = cNode->pLeft->Data;//��Ʈ ��� �����;�����Ʈ
						pRoot->pRight = cNode->pLeft->pRight;//��Ʈ ��� ������ ������Ʈ
						pRoot->pLeft = cNode->pLeft->pLeft;//��Ʈ��� ������ ������Ʈ
						cNode = nNode;//������ ��带 �����.
					}
					else if (pNode->Data > cNode->Data)//�����ؾ��ϴ� �����Ͱ� �θ� ��庸�� �۴ٸ�
					{
						pNode->pLeft = cNode->pLeft;//���� �����ڽ��� �θ����� �������� �̵���Ų��.
						cNode->pLeft->pParent = pNode;
					}
					else
					{
						pNode->pRight = cNode->pLeft;//���� �����ڽ��� �θ����� ���������� �̵���Ų��.
						cNode->pLeft->pParent = pNode;
					}
				}
				else if (cNode->pRight != nil)//�����ʳ�常 �������
				{
					if (pNode == nil)//��Ʈ ����� ���
					{//���ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� �׳� ��ĭ ����
						Node* nNode = pRoot->pRight;//���� ��ġ ����
						pRoot->Data = cNode->pRight->Data;
						pRoot->pLeft = cNode->pRight->pLeft;
						pRoot->pRight = cNode->pRight->pRight;
						cNode = nNode;//���������� ���� cNode������Ʈ
					}
					else if (pNode->Data > cNode->Data)//�����ϴ� �����Ͱ� �θ��庸�� �۴ٸ�
					{
						pNode->pLeft = cNode->pRight;//���� ������ �ڽ��� �θ����� �������� �̵���Ų��.
						cNode->pRight->pParent = pNode;
					}
					else
					{
						pNode->pRight = cNode->pRight;//���� ������ �ڽ��� �θ����� ���������� �̵���Ų��.
						cNode->pRight->pParent = pNode;
					}
				}
				delete cNode;//�������
				delete_Count++;
				return true;//Ʈ�� ����
			}

			/////////////////////////////////////////

			/// <summary>
			/// /////////////////////
			/// </summary>
			/// <param name="data"></param>
			/// <returns></returns>
			if (pNode != nil)//��Ʈ��尡 �ƴҰ��
			{
				pNode->pRight = cNode->pLeft;//�θ��尡 ��Ʈ���Ǿ� �����Ǿ� �ϴ°��� �ڽ����� �޾ƾ��Ѵ�.
				cNode->pLeft->pParent = pNode;
			}
			else if (pNode == nil)//��Ʈ����ϰ��
			{
				nNode->pLeft = cNode->pLeft;//�θ� ��Ʈ�����
				cNode->pLeft->pParent = nNode;
			}
			/// <summary>
			/// /////////////////////
			/// </summary>
			/// <param name="data"></param>
			/// <returns></returns>

			RedBlack_Delete_Refresh(cNode);//������� ���������� ��ġ������

			if (cNode->pLeft == nil && cNode->pRight == nil)//�ڽ��� ���� �����
			{
				if (pNode == nil)//��Ʈ ����ϰ��
					pRoot = nullptr;//��Ʈ ��带 �����Ѵ�.->�̹ݺ��� Ż��� cNode�� ��Ʈ �ڵ� ���ŵ�
				else if (pNode->pLeft == cNode) //�θ����� ���ʳ�����
				{
					pNode->pLeft = nil;//���ʳ�� nil����
				}
				else//�θ����� �����ʳ����
				{
					pNode->pRight = nil;//�����ʳ�� �ʱ�ȭ
				}
			}
			//������ ��尡(3) �� ���� ����Ʈ���� ������ �ִ� ���
			else if (cNode->pLeft != nil && cNode->pRight != nil)
			{
				Node* nNode = cNode;//���� ��ġ ����
				pNode = nil;

				cNode = cNode->pLeft;//���ʳ��� �ѹ��̵�

				//���� ����Ʈ���� ���� ū���� ã�´�.
				while (cNode->pRight != nil)
				{
					pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.
					cNode = cNode->pRight;//��� ���������� �̵�
				}

				nNode->Data = cNode->Data;//������ ������� ������Ʈ

				if (pNode != nil)//��Ʈ��尡 �ƴҰ��
				{
					pNode->pRight = cNode->pLeft;//�θ��尡 ��Ʈ���Ǿ� �����Ǿ� �ϴ°��� �ڽ����� �޾ƾ��Ѵ�.
					cNode->pLeft->pParent = pNode;
				}
				else if (pNode == nil)//��Ʈ����ϰ��
				{
					nNode->pLeft = cNode->pLeft;//�θ� ��Ʈ�����
					cNode->pLeft->pParent = nNode;
				}
				//�ٷ� ������ ��带 �޴°� �����ʳ���� �ڽ��� �޴´� nil�̶�� �װʹ�� �������.
			}
			//������ ��尡(2) �ϳ��� ����Ʈ���� ������ �ִ� ���
			else if (cNode->pLeft != nil)//���� ��常 �������
			{
				if (pNode == nil) //��Ʈ ����� ���
				{//�����ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� ��Ʈ�� ����� �׳� ��ĭ ����.
					Node* nNode = pRoot->pLeft;//������ ��� ��ġ����
					pRoot->Data = cNode->pLeft->Data;//��Ʈ ��� �����;�����Ʈ
					pRoot->pRight = cNode->pLeft->pRight;//��Ʈ ��� ������ ������Ʈ
					pRoot->pLeft = cNode->pLeft->pLeft;//��Ʈ��� ������ ������Ʈ
					cNode = nNode;//������ ��带 �����.
				}
				else if (pNode->Data > cNode->Data)//�����ؾ��ϴ� �����Ͱ� �θ� ��庸�� �۴ٸ�
				{
					pNode->pLeft = cNode->pLeft;//���� �����ڽ��� �θ����� �������� �̵���Ų��.
					cNode->pLeft->pParent = pNode;
				}
				else
				{
					pNode->pRight = cNode->pLeft;//���� �����ڽ��� �θ����� ���������� �̵���Ų��.
					cNode->pLeft->pParent = pNode;
				}
			}
			else if (cNode->pRight != nil)//�����ʳ�常 �������
			{
				if (pNode == nil)//��Ʈ ����� ���
				{//���ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� �׳� ��ĭ ����
					Node* nNode = pRoot->pRight;//���� ��ġ ����
					pRoot->Data = cNode->pRight->Data;
					pRoot->pLeft = cNode->pRight->pLeft;
					pRoot->pRight = cNode->pRight->pRight;
					cNode = nNode;//���������� ���� cNode������Ʈ
				}
				else if (pNode->Data > cNode->Data)//�����ϴ� �����Ͱ� �θ��庸�� �۴ٸ�
				{
					pNode->pLeft = cNode->pRight;//���� ������ �ڽ��� �θ����� �������� �̵���Ų��.
					cNode->pRight->pParent = pNode;
				}
				else
				{
					pNode->pRight = cNode->pRight;//���� ������ �ڽ��� �θ����� ���������� �̵���Ų��.
					cNode->pRight->pParent = pNode;
				}
			}

			delete cNode;//�������
			delete_Count++;
			return true;//Ʈ�� ����
		}
		//������ ��尡(2) �ϳ��� ����Ʈ���� ������ �ִ� ���
		else if (cNode->pLeft != nil)//���� ��常 �������
		{
			//if (pNode == nil) //��Ʈ ����� ���
			//{//�����ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� ��Ʈ�� ����� �׳� ��ĭ ����.
			//	Node* nNode = pRoot->pLeft;//������ ��� ��ġ����
			//	pRoot->Data = cNode->pLeft->Data;//��Ʈ ��� �����;�����Ʈ
			//	pRoot->pRight = cNode->pLeft->pRight;//��Ʈ ��� ������ ������Ʈ
			//	pRoot->pLeft = cNode->pLeft->pLeft;//��Ʈ��� ������ ������Ʈ
			//	cNode = nNode;//������ ��带 �����.
			//}
			//else if (pNode->Data > cNode->Data)//�����ؾ��ϴ� �����Ͱ� �θ� ��庸�� �۴ٸ�
			//	pNode->pLeft = cNode->pLeft;//���� �����ڽ��� �θ����� �������� �̵���Ų��.
			//else
			//	pNode->pRight = cNode->pLeft;//���� �����ڽ��� �θ����� ���������� �̵���Ų��.
		}
		else if (cNode->pRight != nil)//�����ʳ�常 �������
		{
			//if (pNode == nil)//��Ʈ ����� ���
			//{//���ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� �׳� ��ĭ ����
			//	Node* nNode = pRoot->pRight;//���� ��ġ ����
			//	pRoot->Data = cNode->pRight->Data;
			//	pRoot->pLeft = cNode->pRight->pLeft;
			//	pRoot->pRight = cNode->pRight->pRight;
			//	cNode = nNode;//���������� ���� cNode������Ʈ
			//}
			//else if (pNode->Data > cNode->Data)//�����ϴ� �����Ͱ� �θ��庸�� �۴ٸ�
			//	pNode->pLeft = cNode->pRight;//���� ������ �ڽ��� �θ����� �������� �̵���Ų��.
			//else
			//	pNode->pRight = cNode->pRight;//���� ������ �ڽ��� �θ����� ���������� �̵���Ų��.
		}

		//���� �����Ʈ���� �뷱������ �����Ѵ�.
		RedBlack_Delete_Refresh(cNode);//������� ���������� ��ġ������

		//���� ������ ����� ���¸� �Ǻ��ؼ� �����Ѵ�.
		if (cNode->pLeft == nil && cNode->pRight == nil)//�ڽ��� ���� �����
		{
			if (pNode == nil)//��Ʈ ����ϰ��
				pRoot = nullptr;//��Ʈ ��带 �����Ѵ�.->�̹ݺ��� Ż��� cNode�� ��Ʈ �ڵ� ���ŵ�
			else if (pNode->pLeft == cNode) //�θ����� ���ʳ�����
				pNode->pLeft = nil;//���ʳ�� nil����
			else//�θ����� �����ʳ����
				pNode->pRight = nil;//�����ʳ�� �ʱ�ȭ
		}
		//������ ��尡(3) �� ���� ����Ʈ���� ������ �ִ� ���
		else if (cNode->pLeft != nil && cNode->pRight != nil)
		{
			Node* nNode = cNode;//���� ��ġ ����
			pNode = nil;

			cNode = cNode->pLeft;//���ʳ��� �ѹ��̵�

			//���� ����Ʈ���� ���� ū���� ã�´�.
			while (cNode->pRight != nil)
			{
				pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.
				cNode = cNode->pRight;//��� ���������� �̵�
			}

			nNode->Data = cNode->Data;//������ ������� ������Ʈ

			if (pNode != nil)//��Ʈ��尡 �ƴҰ��
			{
				pNode->pRight = cNode->pLeft;//�θ��尡 ��Ʈ���Ǿ� �����Ǿ� �ϴ°��� �ڽ����� �޾ƾ��Ѵ�.
				cNode->pLeft->pParent = pNode;
			}
			else if (pNode == nil)//��Ʈ����ϰ��
			{
				nNode->pLeft = cNode->pLeft;//�θ� ��Ʈ�����
				cNode->pLeft->pParent = nNode;
			}
			//�ٷ� ������ ��带 �޴°� �����ʳ���� �ڽ��� �޴´� nil�̶�� �װʹ�� �������.
		}
		//������ ��尡(2) �ϳ��� ����Ʈ���� ������ �ִ� ���
		else if (cNode->pLeft != nil)//���� ��常 �������
		{
			if (pNode == nil) //��Ʈ ����� ���
			{//�����ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� ��Ʈ�� ����� �׳� ��ĭ ����.
				Node* nNode = pRoot->pLeft;//������ ��� ��ġ����
				pRoot->Data = cNode->pLeft->Data;//��Ʈ ��� �����;�����Ʈ
				pRoot->pRight = cNode->pLeft->pRight;//��Ʈ ��� ������ ������Ʈ
				pRoot->pLeft = cNode->pLeft->pLeft;//��Ʈ��� ������ ������Ʈ
				cNode = nNode;//������ ��带 �����.
			}
			else if (pNode->Data > cNode->Data)//�����ؾ��ϴ� �����Ͱ� �θ� ��庸�� �۴ٸ�
			{
				pNode->pLeft = cNode->pLeft;//���� �����ڽ��� �θ����� �������� �̵���Ų��.
				cNode->pLeft->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pLeft;//���� �����ڽ��� �θ����� ���������� �̵���Ų��.
				cNode->pLeft->pParent = pNode;
			}
		}
		else if (cNode->pRight != nil)//�����ʳ�常 �������
		{
			if (pNode == nil)//��Ʈ ����� ���
			{//���ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� �׳� ��ĭ ����
				Node* nNode = pRoot->pRight;//���� ��ġ ����
				pRoot->Data = cNode->pRight->Data;
				pRoot->pLeft = cNode->pRight->pLeft;
				pRoot->pRight = cNode->pRight->pRight;
				cNode = nNode;//���������� ���� cNode������Ʈ
			}
			else if (pNode->Data > cNode->Data)//�����ϴ� �����Ͱ� �θ��庸�� �۴ٸ�
			{
				pNode->pLeft = cNode->pRight;//���� ������ �ڽ��� �θ����� �������� �̵���Ų��.
				cNode->pRight->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pRight;//���� ������ �ڽ��� �θ����� ���������� �̵���Ų��.
				cNode->pRight->pParent = pNode;
			}
		}

	}

	delete cNode;//�������
	delete_Count++;
	return true;//Ʈ�� ����
}

void CREDBLACKTREE2::RedBlack_Delete_Refresh(Node* _DNode)//��������
{
	//printTree(pRoot, nullptr, false);
	Node* _MNode;//��
	Node* _MLNode;//���� ����
	Node* _MRNode;//���� ����
	Node* _PNode;//���Ǻθ�

	Node* _SNode;//��������
	Node* _SLNode;//���� �����ڽ�
	Node* _SRNode;//���� �������ڽ�

	_MNode = _DNode;//������ ���� �ִ´�.

	//_PNode = _MNode->pParent;//������ ����� �θ�

	//if (_PNode->pLeft == _MNode)//������ ����� ������ �����
	//	_SNode = _PNode->pRight;//������ �θ��� �����ʳ��
	//else
	//	_SNode = _PNode->pLeft;//������ �θ��� ���ʳ��

	//_SLNode_ = _SNode->pLeft;//������ ���� �ڽ�
	//_SRNode_ = _SNode->pRight;//������ ������ �ڽ�

	//while (1)
	//{

	_MLNode = _MNode->pLeft;
	_MRNode = _MNode->pRight;
	_PNode = _MNode->pParent;//������ ����� �θ�

	if (_PNode->pLeft == _MNode)//������ ����� ������ �����
		_SNode = _PNode->pRight;//������ �θ��� �����ʳ��
	else if (_PNode->pRight == _MNode)
		_SNode = _PNode->pLeft;//������ �θ��� ���ʳ��
	else if (_PNode->pLeft == nil)
		_SNode = _PNode->pRight;
	else if (_PNode->pRight == nil)
		_SNode = _PNode->pLeft;
	else
		_SNode = nil;

	_SLNode = _SNode->pLeft;//������ ���� �ڽ�
	_SRNode = _SNode->pRight;//������ ������ �ڽ�

	//�̰� ��Ʈ����� ��츦 �����ص־��ϳ�.
	//������ 2��������
	//�ܸ���� �����ϰ� �ܸ���尡 �ƴҶ��� �����ؾ��Ѵ�.

	if (_PNode->pLeft == _MNode)//���� �θ��� �����ڽ��̶��
	{
		//2.1 ���� ����� �ڽ�(���س��)�� ������ ���
		if (_MNode->pLeft->pColor == e_RED)//nil�� �ƴϸ鼭 ������ �������̶��
		{
			//�ڽ��� ������ �������(��)�� ��������
			//���� ����� �ڽ�(����) �� ������ �ٲپ������� ���� �ذ�
			//���� �ڸ��� ��尡 ������ �̸� ������ �ٲٴ°ɷ� ������ ��.
			_MNode->pLeft->pColor = e_BLACK;
			return;
		}

		//2.2 ���� ����� ������ ����
		if (_SNode->pColor == e_RED)
		{
			_SNode->pColor = e_BLACK;//������ ������ �ٲ�
			Left_Rotation(_PNode);//�θ� �������� ��ȸ��!!!
			_PNode->pColor = e_RED;//���� �θ� ����� �ٲ�.
			_MNode = _MNode->pLeft;//�׸��� ������ (���� �� ���³��, ��������� �ڽ�) �������� ó������ ���۾�.
			RedBlack_Delete_Refresh(_MNode);
		}

		//2.3 ���� ����� ������ ���̰� ������ ���� �ڽ��� ��(�θ� �������� �ƴ����� ����)

		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_BLACK &&
			_SRNode->pColor == e_BLACK)
		{
			_SNode->pColor = e_RED;//�̶��� ������ �����
			//_MNode = _PNode;//�׷��� �� �θ� �������� ó������ �ٽ� ó��.
			RedBlack_Delete_Refresh(_PNode);
		}

		//2.4 ���� ����� ������ ���̰� ������ ���ڽ��� ����, �����ڽ��� ��

		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_RED &&
			_SRNode->pColor == e_BLACK)
		{
			_SLNode->pColor = e_BLACK;//������ ���ڽ��� ������
			_SNode->pColor = e_RED;//������ �����
			Right_Rotation(_SNode);//���� �������� ��ȸ��
			_SRNode = _SNode;
			_SNode = _SLNode;
		}

		//2.5 ���� ����� ������ ���̰� ������ �����ڽ��� ����

		if (_SNode->pColor == e_BLACK &&
			_SRNode->pColor == e_RED)
		{
			_SNode->pColor = _SNode->pParent->pColor;//���� �÷��� �θ� �÷���.
			_PNode->pColor = e_BLACK;//�θ� �÷��� ��
			_SNode->pRight->pColor = e_BLACK;//������ �����ڽ��� ��
			Left_Rotation(_PNode);//�θ���� ��ȸ��   
			return;
			//RedBlack_Delete_Refresh(_DNode);
		}
	}
	else//���� �θ��� ������ �ڽ��̶��
	{
		//2.1 ���� ����� �ڽ�(���س��)�� ������ ���
		if (_MNode->pLeft->pColor == e_RED)//nil�� �ƴϸ鼭 ������ �������̶��
		{
			//�ڽ��� ������ �������(��)�� ��������
			//���� ����� �ڽ�(����) �� ������ �ٲپ������� ���� �ذ�
			//���� �ڸ��� ��尡 ������ �̸� ������ �ٲٴ°ɷ� ������ ��.
			_MNode->pLeft->pColor = e_BLACK;
			return;
		}

		//2.2 ���� ����� ������ ������ ����
		if (_SNode->pColor == e_RED)
		{
			_SNode->pColor = e_BLACK;//������ ������ �ٲ�
			Left_Rotation(_PNode);//�θ� �������� ��ȸ��!!!
			_PNode->pColor = e_RED;//���� �θ� ����� �ٲ�.
			_MNode = _MNode->pRight;//�׸��� ������ (���� �� ���³��, ��������� �ڽ�) �������� ó������ ���۾�.
			RedBlack_Delete_Refresh(_MNode);
			//continue;
		}

		//2.3 ���� ����� ������ ���̰� ������ ���� �ڽ��� ��(�θ� �������� �ƴ����� ����)
		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_BLACK &&
			_SRNode->pColor == e_BLACK)
		{
			_SNode->pColor = e_RED;//�̶��� ������ �����
			RedBlack_Delete_Refresh(_PNode);//�� �θ� �������� �ٽ� ���뷱��
			//return;
		}

		//2.4 ���� ����� ������ ���̰� ������ ���ڽ��� ����, �����ڽ��� ��

		if (_SNode->pColor == e_BLACK &&
			_SRNode->pColor == e_RED &&
			_SLNode->pColor == e_BLACK)
		{
			_SRNode->pColor = e_BLACK;//������ �����ڽ��� ������
			_SNode->pColor = e_RED;//������ �����
			Left_Rotation(_SNode);//���� �������� ��ȸ��
			_SLNode = _SNode;
			_SNode = _SRNode;
		}

		//2.5 ���� ����� ������ ���̰� ������ �����ڽ��� ����

		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_RED)
		{
			_SNode->pColor = _SNode->pParent->pColor;//���� �÷��� �θ� �÷���.
			_PNode->pColor = e_BLACK;//�θ� �÷��� ��
			_SNode->pLeft->pColor = e_BLACK;//������ ���ڽ��� ��
			Right_Rotation(_PNode);//�θ���� ��ȸ��  
			return;
			//RedBlack_Delete_Refresh(_DNode);
		}
	}
	//}
}

//����
bool CREDBLACKTREE2::Tree_Delete(int data)
{
	Node* pNode = nullptr;
	Node* cNode = pRoot;

	//�켱 �����ؾ��ϴ� ����� ��ġ�� Ž���Ѵ�.
	while (cNode != nil)
	{
		if (cNode->Data == data)//�����ؾ��ϴ� ��忡 �����ߴٸ�
			break;//�ݺ����� Ż���Ѵ�.

		pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.

		if (cNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			cNode = cNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			cNode = cNode->pRight;
		}
	}

	if (cNode == nil)//�����Ͱ� ���ٴ� ���̹Ƿ� �������� �ʰ� �����Ѵ�.
		return false;

	//���� checkNode ��ġ�� �����ؾ��ϴ� ��ġ��.
	//������ ��尡(1) �ܸ� ����� ���
	if (cNode->pLeft == nil && cNode->pRight == nil)//�ڽ��� ���� �����
	{
		if (pNode == nil)//��Ʈ ����ϰ��
			pRoot = nullptr;//��Ʈ ��带 �����Ѵ�.->�̹ݺ��� Ż��� cNode�� ��Ʈ �ڵ� ���ŵ�

		//return true;//������ ���ϱ� �������� �ʰ��ϰڴ�.->�̰ǹ� ��å���ϱ� �����ε�?
		else if (pNode->pLeft == cNode) //�θ����� ���ʳ����
			pNode->pLeft = nil;//���ʳ�� �ʱ�ȭ
		else//�θ����� �����ʳ����
			pNode->pRight = nil;//�����ʳ�� �ʱ�ȭ
	}
	//������ ��尡(3) �� ���� ����Ʈ���� ������ �ִ� ���
	else if (cNode->pLeft != nil && cNode->pRight != nil)
	{
		Node* nNode = cNode;//���� ��ġ ����
		pNode = nil;

		cNode = cNode->pRight;//�����ʳ��� �ѹ��̵�

		//������ ����Ʈ�� �� ���� ���� ��带 ã�´�.
		while (cNode->pLeft != nil)
		{
			pNode = cNode;//�����ؾ��ϴ� ����� �θ��带 ����Ѵ�.
			cNode = cNode->pLeft;//��� �������� �̵�
		}

		nNode->Data = cNode->Data;//������ �������

		if (pNode != nil)//��Ʈ��尡 �ƴҰ��
			pNode->pLeft = cNode->pRight;//�θ��尡 ��Ʈ���Ǿ� �����Ǿ� �ϴ°��� �ڽ����� �޾ƾ��Ѵ�.
		else//��Ʈ����ϰ��
			nNode->pRight = cNode->pRight;//�θ� ��Ʈ�����
		//�ٷ� ������ ��带 �޴°� �����ʳ���� �ڽ��� �޴´� nullptr�̶�� �װʹ�� �������.
	}
	//������ ��尡(2) �ϳ��� ����Ʈ���� ������ �ִ� ���
	else if (cNode->pLeft != nil)//���� ��常 �������
	{
		if (pNode == nil) //��Ʈ ����� ���
		{//�����ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� ��Ʈ�� ����� �׳� ��ĭ ����.
			Node* nNode = pRoot->pLeft;//������ ��� ��ġ����
			pRoot->Data = cNode->pLeft->Data;//��Ʈ ��� �����;�����Ʈ
			pRoot->pRight = cNode->pLeft->pRight;//��Ʈ ��� ������ ������Ʈ
			pRoot->pLeft = cNode->pLeft->pLeft;//��Ʈ��� ������ ������Ʈ
			cNode = nNode;//������ ��带 �����.
		}
		else if (pNode->Data > cNode->Data)//�����ؾ��ϴ� �����Ͱ� �θ� ��庸�� �۴ٸ�
			pNode->pLeft = cNode->pLeft;//���� �����ڽ��� �θ����� �������� �̵���Ų��.
		else
			pNode->pRight = cNode->pLeft;//���� �����ڽ��� �θ����� ���������� �̵���Ų��.
	}
	else if (cNode->pRight != nil)//�����ʳ�常 �������
	{
		if (pNode == nil)//��Ʈ ����� ���
		{//���ʿ� �ƹ� ��嵵 ���ٴ°Ŵϱ� �׳� ��ĭ ����
			Node* nNode = pRoot->pRight;//���� ��ġ ����
			pRoot->Data = cNode->pRight->Data;
			pRoot->pLeft = cNode->pRight->pLeft;
			pRoot->pRight = cNode->pRight->pRight;
			cNode = nNode;//���������� ���� cNode������Ʈ
		}
		else if (pNode->Data > cNode->Data)//�����ϴ� �����Ͱ� �θ��庸�� �۴ٸ�
			pNode->pLeft = cNode->pRight;//���� ������ �ڽ��� �θ����� �������� �̵���Ų��.
		else
			pNode->pRight = cNode->pRight;//���� ������ �ڽ��� �θ����� ���������� �̵���Ų��.
	}

	//������ ��尡 �����尡 �ƴ϶��
	if (cNode->pColor != e_RED)
	{

	}

	delete cNode;//�������

	return true;//Ʈ�� ����
}

//�˻�
bool CREDBLACKTREE2::Tree_Search(int data)
{
	Node* SearchNode = pRoot;//��Ʈ ������ ����

	while (SearchNode != nullptr)
	{
		if (SearchNode->Data == data)//�����Ͱ� �ִٸ�
			return true;

		if (SearchNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			SearchNode = SearchNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			SearchNode = SearchNode->pRight;
		}
	}
	return false;
}

CREDBLACKTREE2::Node* CREDBLACKTREE2::Tree_Search_Node(int data)
{
	Node* SearchNode = pRoot;//��Ʈ ������ ����

	while (SearchNode != nullptr)
	{
		if (SearchNode->Data == data)//�����Ͱ� �ִٸ�
			return SearchNode;

		if (SearchNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			SearchNode = SearchNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			SearchNode = SearchNode->pRight;
		}
	}
	return nil;//�����Ͱ� ���ٸ� nil����
};


//�ܼ� ������ȸ ���
void CREDBLACKTREE2::All_print(Node* pNode)
{
	if (pNode == nullptr || pNode == nil)
		return;

	//���� ��ȸ�� ��� ������ ���
	All_print(pNode->pLeft);

	printf("%d ", pNode->Data);

	All_print(pNode->pRight);
}


// ���� ��ȸ�� �����ϰ� Ȯ�� �� �� �ְ� �Ѵ�.
void CREDBLACKTREE2::printBinaryTree(Node* pNode, bool isLeft, int space, int height)
{
	// �⺻ ���̽�
	if (pNode == nullptr || pNode == nil) {
		return;
	}

	// ���� ������ �Ÿ� ����
	space += height;

	// ������ �ڽ��� ���� ���
	printBinaryTree(pNode->pRight, true, space);
	cout << endl;

	// �������� ä�� �� ���� ��带 �μ��մϴ�.
	for (int i = height; i < space - 1; i++) {
		cout << ' ';
	}
	if (pNode == pRoot)//��Ʈ ����϶�
	{
		cout << "-" << pNode->Data;
	}
	else if (isLeft)//�ڽĳ���϶�
	{
		cout << "��  " << pNode->Data;
	}
	else {

		cout << "��  " << pNode->Data;
	}

	// ���� �ڽ� ���
	cout << endl;
	printBinaryTree(pNode->pLeft, false, space);

}

// ���� Ʈ���� �б⸦ �μ��ϴ� ����� �Լ�
void CREDBLACKTREE2::showTrunks(Trunk* p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	cout << p->str;
}

void CREDBLACKTREE2::printTree(Node* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr || root == nil) {
		return;
	}

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->pRight, trunk, true);

	if (!prev) {
		trunk->str = "---";
	}
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else {
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	if (root->pColor == e_BLACK)//true ���� B���
		cout << " " << root->Data << "B" << endl;
	else
		cout << " " << root->Data << "R" << endl;
	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->pLeft, trunk, false);
}

//���� ����� Ʈ���� üũ�ϴ� �ڵ�
int CREDBLACKTREE2::RBT_CHECK(Node* _pNode)
{
	if (_pNode == nil)//���� ��尡 nil�� �ƴҋ�
		return 0;

	//���� ����üũ
	//������ȸ ����带 ��ȸ�ϸ鼭 ���ӵ� �θ� RED �ڽ�RED�� �ִٸ�
	if (_pNode->pColor == e_RED && _pNode->pParent->pColor == e_RED)
	{
		printf("\_pNode->P->Data %d\n", _pNode->pParent->Data);
		printf("_pNode->Data %d\n", _pNode->Data);
		printTree(pRoot, nullptr, false);
		throw std::bad_exception{};//���� ���� �߻���Ű��
		return 5;
	}
	RBT_CHECK(_pNode->pLeft);
	RBT_CHECK(_pNode->pRight);

	//���ܳ�忡�� ���� ��Ʈ������ ���üũ
	if (_pNode->pLeft == nil && _pNode->pRight == nil)
	{
		Node* _tmpNode = _pNode;//���� ��������ϰ��
		int BlackCount = 0;
		while (_tmpNode != pRoot)
		{
			if (_tmpNode->pColor == e_BLACK)
			{
				BlackCount++;
			}
			_tmpNode = _tmpNode->pParent;//�θ� Ÿ��ö󰡸鼭 üũ
		}
		if (black_depth == 0)
			black_depth = BlackCount;
		else if (black_depth != BlackCount)
		{
			printf("black_depthError\n");
			printf("_tmpNode->P->Data %d\n", _pNode->pParent->Data);
			printf("_tmpNode->Data %d\n", _pNode->Data);
			//printTree(pRoot, nullptr, false);
			throw std::bad_exception{};//���� ���� �߻���Ű��
			return 2;
		}
	}

	//���ݱ��� ������ Ž���Ǵ� ����� Ȯ��
	//�߰��ѳ�� - �����ȳ�� == ������ ����
	int _in_outNodeCount = insert_Count - delete_Count;
	if (_in_outNodeCount != Tree_Count(pRoot))
	{
		throw std::bad_exception{};//���� ���� �߻���Ű��
		return 3;
	}
	//���ప�� �ٸ���
	//�����Ͱ� ���� �����ϴ°��� �ٸ���
	//��尡 ���ǵǰ� �ִ� ��Ȳ


	return 1;//1 true �̸� ���� ��� �����°� �����̶�� ��
}




void CREDBLACKTREE2::LevelPrint(Node* pNode)
{
	if (pNode == nullptr)
		return;

	queue<Node*>q;
	q.push(pNode);

	while (!q.empty())//ť�� ��������
	{
		Node* _qNode = q.front();
		q.pop();

		if (_qNode->pLeft != nullptr && _qNode != nil)
			q.push(_qNode->pLeft);

		if (_qNode->pRight != nullptr && _qNode != nil)
			q.push(_qNode->pRight);

		if (_qNode != nil)
			printf("%d ", _qNode->Data);
	}
	printf("\n");
}


void CREDBLACKTREE2::Black_Insert(int data)
{
	if (data <= 0) //0������ �����ʹ� ó������ �ʰڴ�.
		return;

	//��Ʈ��尡 �ִ� ���¿����� ������ �Է�
	Node* pNode = nullptr;
	Node* cNode = pRoot;//��Ʈ ������ ����
	Node* insertNode = nullptr;

	while (cNode != nil)//�־���ϴ� ��ġ�� Ž���Ѵ�.
	{
		if (cNode->Data == data)//�ߺ������ʹ� ����������Ѵ�.
			return;

		pNode = cNode;//�θ� ��带 �����Ѵ�.

		if (cNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			cNode = cNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			cNode = cNode->pRight;
		}
	}

	//�������Դٴ°� ������忡 �����ߴٴ� ��
	//������ ��带 �����
	insertNode = new Node;
	insertNode->Data = data;
	insertNode->pColor = e_BLACK;//��ó�� �Է½� �ݵ�� ���������� �����Ѵ�.
	insertNode->pParent = pNode;//�θ� �ִ´�.
	insertNode->pLeft = nil;
	insertNode->pRight = nil;

	insert_Count++;

	if (pNode->Data > data)//�θ� ��庸�� �۴ٸ� ��������
		pNode->pLeft = insertNode;
	else//�θ� ��庸�� ũ�ٸ� ����������
		pNode->pRight = insertNode;
}


void CREDBLACKTREE2::Right_Rotation_Test(int data)
{
	Node* sNode = pRoot;
	while (sNode != nil)//�־���ϴ� ��ġ�� Ž���Ѵ�.
	{
		if (sNode->Data == data)//�ߺ������͸� ã�Ҵٸ� �� ��带 ȸ��
			break;

		if (sNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			sNode = sNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			sNode = sNode->pRight;
		}
	}

	Node* lNode = sNode->pLeft;
	if (lNode == nil || lNode == nullptr)//ȸ���Ϸ��µ� ���ʳ�� �����Ͱ� ������ ȸ���Ұ�
		return;

	if (lNode->pRight != nil)
	{
		sNode->pLeft = lNode->pRight;
		sNode->pLeft->pParent = sNode;
	}
	else
	{
		sNode->pLeft = nil;
	}
	lNode->pRight = sNode;

	lNode->pParent = sNode->pParent;

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//���� �̵��Ϸ��� ��尡 Root�����
	{
		pRoot = lNode;//LNode�� ��Ʈ�� �ٲ��ش�.
	}
}

void  CREDBLACKTREE2::Left_Rotation_Test(int data)
{
	//if (sNode == nil || sNode->pRight == nil)
	//return;
	Node* sNode = pRoot;
	while (sNode != nil)//�־���ϴ� ��ġ�� Ž���Ѵ�.
	{
		if (sNode->Data == data)//�ߺ������͸� ã�Ҵٸ� �� ��带 ȸ��
			break;

		if (sNode->Data > data) //���� ��庸�� �����Ͱ� �۴ٸ� �������� �����Ѵ�.
		{
			sNode = sNode->pLeft;
		}
		else//���� ��庸�� �����Ͱ� ũ�ٸ� ���������� �����Ѵ�.
		{
			sNode = sNode->pRight;
		}
	}

	Node* lNode = sNode->pRight;

	if (lNode == nil || lNode == nullptr)//ȸ���Ϸ��µ� ������ ��� �����Ͱ� ���ٸ� ȸ���Ұ�
		return;

	if (lNode->pLeft != nil)
	{
		sNode->pRight = lNode->pLeft;
		sNode->pRight->pParent = sNode;
	}
	else
	{
		sNode->pRight = nil;
	}
	lNode->pLeft = sNode;

	lNode->pParent = sNode->pParent;

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//���� �̵��Ϸ��� ��尡 Root�����
		pRoot = lNode;//LNode�� ��Ʈ�� �ٲ��ش�.
}