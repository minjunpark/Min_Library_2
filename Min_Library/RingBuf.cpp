#include"RingBuf.h"
#include <cstdio>
#include <Windows.h>
#include <iostream>

RingBuf::RingBuf(void)
{
	readPos = 0;
	writePos = 0;
}

RingBuf::RingBuf(int iBufferSize)
{
	readPos = 0;
	writePos = 0;
}


int RingBuf::Enqueue(char* chpData, int iSize)
{
	int count = 0;

	while (iSize != 0)
	{
		//배열에 데이터 꽉 참
		if ((writePos + 1) % BUFFER_SIZE == readPos)
		{
			//printf("배열이 꽉 찼습니다 \n");
			return count;
		}

		arr[writePos] = *chpData;
		writePos = (writePos + 1) % BUFFER_SIZE;

		count++;
		chpData++;
		iSize--;

	}

	return count;
}

int RingBuf::Dequeue(char* chpData, int iSize)
{
	int count = 0;
	int pos = readPos;

	bool isOneCircle = false;
	int afterCount = 0;

	char* cmpCopy = (char*)malloc(DATA_SIZE);
	ZeroMemory(cmpCopy, sizeof(cmpCopy));

	//끝까지 다 읽을때까지
	while (iSize != 0)
	{
		//읽으려 보니 배열이 비어있음
		if (pos == writePos)
		{
			//여기서 반으로 쪼개지는 상황이 있음. (readPos가 배열 끝에서 시작으로 넘어갔을때)
			if (isOneCircle == true)
			{
				memcpy(cmpCopy, arr + readPos, count - afterCount);
				memcpy(cmpCopy + (count - afterCount), arr, afterCount);
			}
			else
				memcpy(cmpCopy, arr + readPos, count);

			//먼저 했던 peek의 결과와 비교
			if (memcmp(cmpCopy, chpData, strlen(chpData)) == 0)
			{
				readPos = pos;
				delete cmpCopy;
				return count;
			}
			else
			{
				delete cmpCopy;
				return 0;
			}
		}

		pos = (pos + 1) % BUFFER_SIZE;

		if (isOneCircle == true)
			afterCount++;

		if (pos == 0)
			isOneCircle = true;

		count++;
		iSize--;
	}

	if (isOneCircle == true)
	{
		memcpy(cmpCopy, arr + readPos, count - afterCount);
		memcpy(cmpCopy + (count - afterCount), arr, afterCount);
	}
	else
		memcpy(cmpCopy, arr + readPos, count);

	//이부분은 테스트할 때 peek의 결과와 deq의 결과가 같을때만 진짜 deq를 하기 위해 넣은 코드. 
	//반드시 peek를 먼저 했어야 데이터 비교가 가능하고, 쓰지 않을거면 	readPos = pos;	return count; 만 남기고 지워야 함.
	if (memcmp(cmpCopy, chpData, strlen(chpData)) == 0)
	{
		readPos = pos;
		delete cmpCopy;
		return count;
	}
	else
	{
		delete cmpCopy;
		return 0;
	}
}

int RingBuf::Peek(char* chpData, int iSize)
{
	int count = 0;
	int pos = readPos;

	bool isOneCircle = false;
	int afterCount = 0;

	//끝까지 다 읽을때까지
	while (iSize != 0)
	{
		//읽으려 보니 배열이 비어있음
		if (pos == writePos)
		{
			//여기서 반으로 쪼개지는 상황이 있음. (readPos가 배열 끝에서 시작으로 넘어갔을때)
			if (isOneCircle == true)
			{
				memcpy(chpData, arr + readPos, count - afterCount);
				memcpy(chpData + (count - afterCount), arr, afterCount);
			}
			else
				memcpy(chpData, arr + readPos, count);

			return count;
		}

		pos = (pos + 1) % BUFFER_SIZE;

		if (isOneCircle == true)
			afterCount++;

		if (pos == 0)
			isOneCircle = true;

		count++;
		iSize--;
	}

	if (isOneCircle == true)
	{
		memcpy(chpData, arr + readPos, count - afterCount);
		memcpy(chpData + (count - afterCount), arr, afterCount);
	}
	else
		memcpy(chpData, arr + readPos, count);

	return count;
}

int RingBuf::MoveRear(int iSize)
{
	writePos = (writePos + iSize) % BUFFER_SIZE;
	return writePos;
}

int RingBuf::MoveFront(int iSize)
{
	readPos = (readPos + iSize) % BUFFER_SIZE;
	return readPos;
}