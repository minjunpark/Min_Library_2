#include <iostream>
#include "CMemoryPool.h"

struct st_Player
{
	int hp;
	int x;
	int y;
};



struct st_Monster
{
	int hp;
	int x;
	int y;
};

int main()
{
	//Node_text* FreeNode = new Node_text;

	////Node_text* n1;

	//Node_text* NewNode = new Node_text;

	//printf(" &(NewNode->data) %p\n", &(NewNode->data));
	//st_Player* data = new(&(NewNode->data)) st_Player;
	//printf("data %p", data);


	//NewNode->next = FreeNode;
	//FreeNode = NewNode;


	//data->~st_Player();//소멸자를 호출해서 데이터 제거

	CMemoryPool<st_Player> Pool(0, false);
	
	//Pool(300, false);
	st_Player* p = Pool.Alloc();//할당
	st_Player* k = Pool.Alloc();
	st_Player* q = nullptr;

	p->hp = 1;
	p->x = 2;
	p->y = 3;
	k->hp = 3;
	k->x = 4;
	k->y = 5;
	printf("%d %d %d\n", p->hp, p->x, p->y);
	printf("%d %d %d\n", k->hp, k->x, k->y);
	Pool.print();
	st_Player* s = Pool.Alloc();;
	s->hp = 7;
	s->x = 8;
	s->y = 9;
	Pool.Free(s);
	Pool.Free(k);
	Pool.Free(p);
	printf(" &(NewNode->data) %p\n", p);
	printf("data %p\n", k);
	printf("p : %d %d %d\n", p->hp, p->x, p->y);
	printf("k : %d %d %d\n", k->hp, k->x, k->y);
	printf("s : %d %d %d\n", s->hp, s->x, s->y);
	st_Player* l = Pool.Alloc();;
	st_Player* w = Pool.Alloc();;
	printf("l : %d %d %d\n", l->hp, l->x, l->y);
	printf("w : %d %d %d\n", w->hp, w->x, w->y);
	Pool.Free(l);
	Pool.Free(w);
	Pool.print();
	//p->hp = 1;
	//p->x = 2;
	//p->y = 3;
	//Pool.print();
	//printf("%d\n",Pool.Free(k));
	//printf("%d\n", Pool.Free(k));
	////printf("%d\n", Pool.Free(p));
	////printf("%d %d %d\n", p->hp, p->x, p->y);
	////Pool.Free(p);//초기화
	return 0;
}
