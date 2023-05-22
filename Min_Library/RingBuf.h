constexpr int BUFFER_SIZE = 1000;
constexpr int DATA_SIZE = 121;

class RingBuf
{
private:
	char arr[BUFFER_SIZE]{ 0, };
	int readPos = 0;	//front
	int writePos = 0;	//rear

public:
	//생성자
	RingBuf(void);
	RingBuf(int iBufferSize);

	// WritePos 에 데이터 넣음. / 넣은 크기 리턴 ((char *)데이터 포인터. (int)크기.) //넣은 크기
	int Enqueue(char* chpData, int iSize);

	// ReadPos 에서 데이터 가져옴. ReadPos 이동. ((char *)데이터 포인터. (int)크기.) //가져온 크기
	int Dequeue(char* chpDest, int iSize);

	// ReadPos 에서 데이터 읽어옴. ReadPos 고정. ((char *)데이터 포인터. (int)크기.) //가져온 크기
	int Peek(char* chpDest, int iSize);

	// 원하는 길이만큼 읽기위치 에서 삭제 / 쓰기 위치 이동
	int MoveRear(int iSize);
	int MoveFront(int iSize);

	void	ClearBuffer(void)
	{
		//버퍼 초기화
		readPos = 0;
		writePos = 0;
	}

};