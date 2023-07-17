// Min_Library.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "CRingbuffer.h"
#include "RingBuffer.h"
#include "MRingBuffer.h"
#include "TRingBuffer.h"
#include <windows.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

char buf[121];
char peek_buf[121];
char De_buf[121];
char test_buf[121];
char* buf_printf;

#include "RingBuf.h"

//RingBuf buffer;



char data[] = { "1abcdefgh 2abcdefgh 3abcdefgh 4abcdefgh 5abcdefgh 6abcdefgh 7abcdefgh 8abcdefgh 9abcdefgh 0abcdefgh 1abcdefgh 2abcdefgh0" };


TRingBuffer Threadbuffer;
//MRingBuffer* buffer = new MRingBuffer;

unsigned WINAPI ThreadFunction(void* arg)
{
	srand(100);
	int enqRandom;
	int deqRandom;

	char* ptr = data;
	char* deqCopy = (char*)malloc(sizeof(data));
	char* dataCopy = (char*)malloc(sizeof(data));
	char* deqPeek = (char*)malloc(sizeof(data));
	char* Start = dataCopy;
	int leftSize = sizeof(data) - 1;

	for (;;)
	{
		if (leftSize == 0)
		{
			dataCopy = Start;
			ZeroMemory(dataCopy, sizeof(data));
			ptr = data;
			leftSize = sizeof(data) - 1;
		}

		enqRandom = rand() % leftSize + 1;
		int enqRet = Threadbuffer.Enqueue(ptr, enqRandom); //랜덤한 길이만큼 넣기 
		ptr = ptr + enqRet; //enq된 사이즈만큼 증가.

		leftSize = leftSize - enqRet;
	}
	return 0;
}

unsigned WINAPI ThreadFunction2(void* arg)
{
	srand(150);
	
	int deqRandom;

	char* ptr = data;
	char* deqCopy = (char*)malloc(sizeof(data));
	char* dataCopy = (char*)malloc(sizeof(data));
	char* deqPeek = (char*)malloc(sizeof(data));
	char* Start = dataCopy;
	int leftSize = sizeof(data) - 1;

	for (;;)
	{
		deqRandom = rand() % 120 + 1;

		ZeroMemory(deqCopy, sizeof(data));
		//ZeroMemory(deqPeek, sizeof(data));
		//int peekRet = Threadbuffer.Peek(deqPeek, deqRandom);

		int deqRet = Threadbuffer.Dequeue(deqCopy, deqRandom);

		//if (deqRet != 0) {
		//	memcpy_s(dataCopy, deqRet, deqCopy, deqRet);
		//	dataCopy = dataCopy + deqRet;
		//}

		//if (strcmp(deqCopy, deqPeek) != 0)
		//{
		//	//printf("count %s\n", count);
		//	printf("deqPeek %s\n", deqPeek);
		//	printf("deqCopy %s", deqCopy);
		//	return 0;
		//}

		//if (count == 200)
		//{
		//	buffer->Resize(15000);
		//}

		if (deqRet > 0)
		{
			printf("%s", deqCopy);
		}
	}
	return 0;
}

void main()
{
	//printf("%d",(9800+300)%10000);

	//return;
	srand(100);
	TRingBuffer* buffer = new TRingBuffer;
	//TRingBuffer * buffer = new TRingBuffer(500);
	//long long count = 0;
	int count = 0;
	//MRingBuffer buffer = MRingBuffer(100);
	//RingBuffer buffer = RingBuffer(10);
	//CRingBuffer buffer = CRingBuffer(10000);
	int enqRandom;
	int deqRandom;

	char* ptr = data;
	char* deqCopy = (char*)malloc(sizeof(data));
	char* dataCopy = (char*)malloc(sizeof(data));
	char* deqPeek = (char*)malloc(sizeof(data));
	char* Start = dataCopy;
	int leftSize = sizeof(data) - 1;

	HANDLE hThread1;
	HANDLE hThread2;
	
	DWORD dwThreadID1;
	DWORD dwThreadID2;
	
	hThread1 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, 0, (unsigned*)&dwThreadID1);
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction2, NULL, 0, (unsigned*)&dwThreadID2);
	int a=0;
	while (1)
	{
		a++;
	}
	
	while (true)
	{

		if (leftSize == 0)
		{

			//printf("%s\n", dataCopy);
			//printf("%s", dataCopy);
			////return;
			//if (strcmp(data, dataCopy) != 0)
			//{
			//	printf("\n%s", dataCopy);
			//	printf("\ncount %d",count);
			//	return;
			//}
			dataCopy = Start;
			ZeroMemory(dataCopy, sizeof(data));
			ptr = data;
			leftSize = sizeof(data) - 1;
		}

		if (count == 3)
		{
			printf("");
		}

		enqRandom = rand() % leftSize + 1;
		int enqRet = buffer->Enqueue(ptr, enqRandom); //랜덤한 길이만큼 넣기 
		ptr = ptr + enqRet; //enq된 사이즈만큼 증가.

		deqRandom = rand() % leftSize + 1;

		ZeroMemory(deqCopy, sizeof(data));
		ZeroMemory(deqPeek, sizeof(data));
		int peekRet = buffer->Peek(deqPeek, deqRandom);

		leftSize = leftSize - enqRet;

		int deqRet = buffer->Dequeue(deqCopy, deqRandom);

		if (deqRet != 0) {
			memcpy_s(dataCopy, deqRet, deqCopy, deqRet);
			dataCopy = dataCopy + deqRet;
		}

		if (strcmp(deqCopy, deqPeek) != 0)
		{
			printf("count %s\n", count);
			printf("deqPeek %s\n", deqPeek);
			printf("deqCopy %s", deqCopy);
			return;
		}

		//if (count == 200)
		//{
		//	buffer->Resize(15000);
		//}

		if (deqRet > 0)
		{
			printf("%s", deqCopy);
		}

		//count++;
	//return;
	}
}

//int main()
//{
//
//    //int seed = 1;
//    //srand(seed);
//    //strcpy_s(buf,sizeof(buf),
//    //    "1abcdefgh 2abcdefgh 3abcdefgh 4abcdefgh 5abcdefgh 6abcdefgh 7abcdefgh 8abcdefgh 9abcdefgh 0abcdefgh 1abcdefgh 2abcdefgh0");
//
//    //CRingBuffer ring(200);
//
//    //RingBuffer ring_test(200);
//
//    //int random;
//    //int random2;
//    //int dequeue;
//    //int buf_count;
//
//    //buf_count = 0;
//    //int test_ret;
//    //
//    //random = rand() % ((60 - 1) + 1) + 1;
//
//    //clock_t t1, t2;
//    //int count = 0;
//
//    //t1 = clock();
//    //
//    //while (1)
//    //for (int i = 0; i <1000000;i++)
//    //{
//    //    t2 = clock();
//    //    if ((t2-t1)>(600*CLOCKS_PER_SEC)) 
//    //    {
//    //        t1 = clock();
//    //        t2 = clock();
//    //        seed++;
//    //        srand(seed);
//    //    }
//    //    
//    //    ring_test.Enqueue(buf, 120);
//    //    random = (rand() % 110) + 1;
//    //    
//    //    ring_test.Dequeue(test_buf, random);
//    //    
//    //    ring.Enqueue(test_buf, random);
//    //    random2 = (rand() % 110) + 1;
//    //    ring.Peek(peek_buf, random);
//    //    dequeue = ring.Dequeue(De_buf, random);
//    //    
//    //    if (memcmp(De_buf, peek_buf, sizeof(De_buf) != 0))
//    //    {
//    //        ring._print();
//    //        printf("Peek Dequeue not break!!");
//    //    }
//    //    printf("random %d\n",random);
//    //    printf("%s", De_buf);
//
//    //    ZeroMemory(buf, sizeof(buf));
//    //    ZeroMemory(peek_buf, sizeof(peek_buf));
//    //    ZeroMemory(De_buf,sizeof(De_buf));
//    //}
//    //printf("\ni : %d",count);
//    int seed = 1;
//    srand(seed);
//    strcpy_s(buf,sizeof(buf),
//        "1abcdefgh 2abcdefgh 3abcdefgh 4abcdefgh 5abcdefgh 6abcdefgh 7abcdefgh 8abcdefgh 9abcdefgh 0abcdefgh 1abcdefgh 2abcdefgh0");
//  
//   // CRingBuffer ring = CRingBuffer(1000);
//    
//    //CRingBuffer ring_test = CRingBuffer(1000);
//
//    RingBuffer ring = RingBuffer(1000);
//    RingBuffer ring_test = RingBuffer(1000);
//
//    int random;
//    int random2;
//    int dequeue;
//    int buf_count;
//
//    buf_count = 0;
//    int test_ret;
//    
//    //random = rand() % ((60 - 1) + 1) + 1;
//
//    clock_t t1, t2;
//    int count = 0;
//
//    t1 = clock();
//    
//    while (1)
//    //for (int i = 0; i <40;i++)
//    {
//        //t2 = clock();
//        //if ((t2-t1)>(600*CLOCKS_PER_SEC)) 
//        //{
//        //    t1 = clock();
//        //    t2 = clock();
//        //    seed++;
//        //    srand(seed);
//        //}
//       
//        //ring_test.Enqueue(buf, 120);
//        
//        
//        //random = 98;
//        //ring_test.Dequeue(test_buf, 120);
//        
//        ring.Enqueue(buf, 120);
//        random = (rand() %10) + 1;
//        //random2 = (rand() % 100) + 1;
//        ring.Peek(peek_buf, 120);
//        dequeue = ring.Dequeue(De_buf, 120);
//        
//        if (memcmp(De_buf, peek_buf, sizeof(De_buf) != 0))
//        {
//           // ring._print();
//            printf("Peek Dequeue not break!!");
//        }
//        //printf("random %d\n",random);
//        printf("%s", De_buf);
//
//        //if (i>=38) {
//        //    //ring._print();
//        //    printf("");
//        //}
//
//        //ZeroMemory(buf, sizeof(buf));
//        //ZeroMemory(peek_buf, sizeof(peek_buf));
//        //ZeroMemory(De_buf,sizeof(De_buf));
//    }
//
//
//    //printf("\n");
//    //ring_test._print();
//    //ring_test._print();
//    //ring._print();
//    ////printf("GetBufferSize() %d\n", ring.GetBufferSize());
//    ////printf("ring.DirectEnqueueSize() %d\n", ring.DirectEnqueueSize());
//    //ring.Enqueue(buf,sizeof(buf));
//    ////printf("ring.DirectEnqueueSize() %d\n", ring.DirectEnqueueSize());
//    ////printf("GetUseSize() %d\n", ring.GetUseSize());
//    ////printf("GetFreeSize() %d\n", ring.GetFreeSize());
//    //ring.Enqueue(buf, sizeof(buf));
//    //ring._print();
//    //ring._print();
//    ////
//    //memset(buf,0, sizeof(buf));
//    //printf("%s",buf);
//    ////printf("ring.DirectDequeueSize() %d\n", ring.DirectDequeueSize());
//    //ring.Peek(buf, sizeof(buf));
//    //printf("ring.DirectDequeueSize() %d\n", ring.DirectDequeueSize());
//    //printf("Peek    : %s\n", buf);
//
//    //ring.Dequeue(buf, sizeof(buf));
//    //printf("ring.DirectDequeueSize() %d\n", ring.DirectDequeueSize());
//    //printf("Dequeue : %s\n", buf);
//    //ring.Dequeue(buf, sizeof(buf));
//    //printf("ring.DirectDequeueSize() %d\n", ring.DirectDequeueSize());
//    //printf("Dequeue : %s\n", buf);
//    //ring._print();
//    //ring._print();
//}

