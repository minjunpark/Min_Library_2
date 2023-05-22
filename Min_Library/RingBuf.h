constexpr int BUFFER_SIZE = 1000;
constexpr int DATA_SIZE = 121;

class RingBuf
{
private:
	char arr[BUFFER_SIZE]{ 0, };
	int readPos = 0;	//front
	int writePos = 0;	//rear

public:
	//������
	RingBuf(void);
	RingBuf(int iBufferSize);

	// WritePos �� ������ ����. / ���� ũ�� ���� ((char *)������ ������. (int)ũ��.) //���� ũ��
	int Enqueue(char* chpData, int iSize);

	// ReadPos ���� ������ ������. ReadPos �̵�. ((char *)������ ������. (int)ũ��.) //������ ũ��
	int Dequeue(char* chpDest, int iSize);

	// ReadPos ���� ������ �о��. ReadPos ����. ((char *)������ ������. (int)ũ��.) //������ ũ��
	int Peek(char* chpDest, int iSize);

	// ���ϴ� ���̸�ŭ �б���ġ ���� ���� / ���� ��ġ �̵�
	int MoveRear(int iSize);
	int MoveFront(int iSize);

	void	ClearBuffer(void)
	{
		//���� �ʱ�ȭ
		readPos = 0;
		writePos = 0;
	}

};