/*---------------------------------------------------------------

	procademy MemoryPool.

	�޸� Ǯ Ŭ���� (������Ʈ Ǯ / ��������Ʈ)
	Ư�� ����Ÿ(����ü,Ŭ����,����)�� ������ �Ҵ� �� ��������.

	- ����.

	procademy::CMemoryPool<DATA> MemPool(300, FALSE);
	DATA *pData = MemPool.Alloc();

	pData ���

	MemPool.Free(pData);


----------------------------------------------------------------*/
#ifndef  __PROCADEMY_MEMORY_POOL__
#define  __PROCADEMY_MEMORY_POOL__
#include <new.h>


//namespace procademy
//{
template <class DATA>
class CMemoryPool
{
private:
	int m_iCapacity;//�޸�Ǯ ��ü ����
	int m_iUseCount;//������� ������
	bool m_iPlacementNew;// Alloc �� ������ / Free �� �ı��� ȣ�� ����

	struct Node
	{
		DATA data;
		Node* next = nullptr;
	};

public:
	// ���� ������� ��ȯ�� (�̻��) ������Ʈ ���� ����.
	Node* _FreeNode;

	//////////////////////////////////////////////////////////////////////////
	// ������, �ı���.
	//
	// Parameters:	(int) �ʱ� �� ����.
	//				(bool) Alloc �� ������ / Free �� �ı��� ȣ�� ����
	// Return:
	//////////////////////////////////////////////////////////////////////////
	CMemoryPool(int iBlockNum, bool bPlacementNew = false)
	{
		m_iCapacity = 0;//��ü �Ѱ���
		m_iUseCount = 0;//��� ���� ����
		m_iPlacementNew = bPlacementNew;//Alloc �� ������ / Free �� �ı��� ȣ�� ����
		//_FreeNode = nullptr;
		if (iBlockNum == 0)//0�̶�� �� ������ ������ ����
			return;

		for (int iMemory = 0; iMemory < iBlockNum; iMemory++)//����Ƚ����ŭ ���鼭 ������
		{
			Node* NewNode = new Node;

			if (m_iPlacementNew == false)//Alloc�� ������ �ı��ڸ� ȣ������ �����Ŷ��
				DATA* data = new(&(NewNode->data)) DATA;//�̸� ������ �������صд�.

			NewNode->next = _FreeNode;//����
			_FreeNode = NewNode;//�ױ�

			m_iCapacity++;//���� ��� ���� ������Ű��
		}
	};

	virtual	~CMemoryPool()
	{
		if (m_iCapacity == 0)//0����� ������� �Ȱ��̹Ƿ� �Ҹ��ڸ� �� ������ �ʿ䰡 ����.
			return;

		//��� ��� ����
		Node* _Node = _FreeNode;
		while (_Node != nullptr)//���� ��尡 nullptr��� ����尡 ����ٴ� ���̴�.����
		{
			Node* tmpNode = _Node;//��� �ӽ÷� �����ϰ�
			delete tmpNode;//�������
			_Node = _Node->next;//�������� �Ѿ��.
		}
	};

	//////////////////////////////////////////////////////////////////////////
	// �� �ϳ��� �Ҵ�޴´�.  
	//
	// Parameters: ����.
	// Return: (DATA *) ����Ÿ �� ������.
	//////////////////////////////////////////////////////////////////////////
	DATA* Alloc(void)
	{
		if ((m_iCapacity - m_iUseCount) > 0)//����Ҽ� �ִ� �޸� ������Ʈ�� �ִٸ�
		{
			Node* OldNode = _FreeNode;
			DATA* Data;

			if (m_iPlacementNew == true)//Alloc������ �����ڸ� ȣ�����ֱ� �ٶ�»���
				Data = new (&(OldNode->data)) DATA;//data������ ��ü�� palcement_new�� ��ġ����Ƽ� �޸�ó���Ѵ�.
			else
				Data = &(OldNode->data);//�̹� ������ �����ڰ� ���õ� ���� ������ ���ÿ��� ������ �ٷθ���

			//1. top�� top�� link�� �Ҵ�.
			//2. top ���� �޸� ����
			//OldNode->next = _FreeNode;
			//_FreeNode = OldNode;

			//OldNode = OldNode->next;//���󿡼� ����-> ������ �����͸� ������.
			//_FreeNode = OldNode;//��带 �������� ������嵵 �ٲ��ش�.

			//OldNode->next = _FreeNode;
			//_FreeNode = OldNode;

			_FreeNode = OldNode->next;//���ÿ��� ��� ����

			m_iUseCount++;//�ѻ�뷮�� �÷��ش�.
			//return &OldNode->data;
			return Data;
		}
		else//��� �� �� �ִ� �޸� ������Ʈ�� ���ٸ� ���� �������ش�.
		{
			Node* NewNode = new Node;

			DATA* Data = new (&(NewNode->data)) DATA;

			NewNode->next = _FreeNode;//���ÿ� ��� �߰�
			_FreeNode = NewNode;

			//NewNode = NewNode->next;
			//_FreeNode = NewNode;

			_FreeNode = NewNode->next;//���ÿ��� ��� ����

			m_iUseCount++;//��뷮 �÷��ְ�
			m_iCapacity++;//��� �� ������ ���������ش�.

			//return &NewNode->data;
			return Data;
		}
	};



	//////////////////////////////////////////////////////////////////////////
	// ������̴� ���� �����Ѵ�.
	//
	// Parameters: (DATA *) �� ������.
	// Return: (BOOL) TRUE, FALSE.
	//////////////////////////////////////////////////////////////////////////
	bool	Free(DATA* pData)
	{
		if (pData == nullptr)
			return false;

		//���� ������ ���� �ߺ� �Է��������� �Ǽ�����
		if ((&_FreeNode->data) == pData)
			return false;

		if (m_iUseCount > 0)//���� ������� ���� �ִٸ�
		{
			Node* ReData = (Node*)pData;

			if (m_iPlacementNew == true)//�Ҹ��ڸ� ȣ���ؾ��ϴ� ��Ȳ�̶��
				ReData->data.~DATA();

			ReData->next = _FreeNode;//���ƿ� �޸𸮸�
			_FreeNode = ReData;//���ÿ� �ٽ� �״´�.

			m_iUseCount--;//������� ī���͸� ���δ�.
			return true;
		}

		return false;//���� ����� ī���Ͱ� ���� ��Ȳ�ε� ���� ��� �̹Ƿ� false�� �����Ѵ�.
	};

	void print()
	{
		printf("m_iCapacity %d\n", m_iCapacity);
		printf("m_iUseCount %d\n", m_iUseCount);
		printf("m_iPlacementNew %d\n", m_iPlacementNew);
	};


	//////////////////////////////////////////////////////////////////////////
	// ���� Ȯ�� �� �� ������ ��´�. (�޸�Ǯ ������ ��ü ����)
	//
	// Parameters: ����.
	// Return: (int) �޸� Ǯ ���� ��ü ����
	//////////////////////////////////////////////////////////////////////////
	int		GetCapacityCount(void) { return m_iCapacity; }

	//////////////////////////////////////////////////////////////////////////
	// ���� ������� �� ������ ��´�.
	//
	// Parameters: ����.
	// Return: (int) ������� �� ����.
	//////////////////////////////////////////////////////////////////////////
	int		GetUseCount(void) { return m_iUseCount; }


};
//}
#endif