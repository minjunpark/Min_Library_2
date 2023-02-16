// Min_Library.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstdio>
#include "CRingbuffer.h"
char buf[82];
int main()
{
    strcpy_s(buf,sizeof(buf),"1234567890 abcdefghijklmnopqrstuvwxyz 1234567890 abcdefghijklmnopqrstuvwxyz 12345");

    CRingBuffer ring = CRingBuffer(200);
    ring._print();
    //printf("GetBufferSize() %d\n", ring.GetBufferSize());
    //printf("ring.DirectEnqueueSize() %d\n", ring.DirectEnqueueSize());
    ring.Enqueue(buf,sizeof(buf));
    //printf("ring.DirectEnqueueSize() %d\n", ring.DirectEnqueueSize());
    //printf("GetUseSize() %d\n", ring.GetUseSize());
    //printf("GetFreeSize() %d\n", ring.GetFreeSize());
   // ring.Enqueue(buf, sizeof(buf));
    ring._print();
    ring._print();
    //
    memset(buf,0, sizeof(buf));
    printf("%s",buf);
    //printf("ring.DirectDequeueSize() %d\n", ring.DirectDequeueSize());
    ring.Dequeue(buf, sizeof(buf));
    printf("ring.DirectDequeueSize() %d\n", ring.DirectDequeueSize());
    printf("%s", buf);
    ring._print();
    //ring._print();
}

