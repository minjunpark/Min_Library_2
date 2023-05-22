#include <iostream>
#include "CMemoryPool.h"

class st_test
{
	
public:
	int hp;
	int x;
	int y;
	st_test() 
	{
		hp = 0;
		x = 0;
		y = 0;
		printf("st_test\n");
	}

	virtual ~st_test() 
	{
		printf("~st_test\n");
	}
};

struct st_Player
{
	int hp;
	int x;
	int y;
};

struct st_test2
{
	int a;
	int b;
	char c;
	int k;
	char d;
};

struct st_Monster
{
	int hp;
	int x;
	int y;
};

int main()
{
	//st_test2 a;

	//printf("%d",offsetof(st_test2, d));

	//Node_text* FreeNode = new Node_text;

	////Node_text* n1;

	//Node_text* NewNode = new Node_text;

	//printf(" &(NewNode->data) %p\n", &(NewNode->data));
	//st_Player* data = new(&(NewNode->data)) st_Player;
	//printf("data %p", data);


	//NewNode->next = FreeNode;
	//FreeNode = NewNode;


	//data->~st_Player();//소멸자를 호출해서 데이터 제거

	//CMemoryPool<st_Player> Pool(0, false);
	CMemoryPool<st_test> Pool(0, false);
	//CMemoryPool<st_Player> Pool2(5, false);

	//printf("%d",1);
	//CMemoryPool<st_test> Pool5(0, true);
	//st_test* p1 = Pool5.Alloc();
	//st_test* p2 = Pool5.Alloc();
	//st_test* p3 = Pool5.Alloc();
	//st_test* p4 = Pool5.Alloc();
	//st_test* p5 = Pool5.Alloc();

	//Pool5.Free(p1);
	//Pool5.Free(p2);
	//Pool5.Free(p3);
	//Pool5.Free(p4);
	//Pool5.Free(p5);

	//Pool(300, false);
	
	st_test* p = Pool.Alloc();//할당
	st_test* k = Pool.Alloc();
	//st_Player* v = Pool2.Alloc();
	//Pool.Free(k);
	//Pool.Free(v);

	p->hp = 1;
	p->x = 2;
	p->y = 3;
	k->hp = 3;
	k->x = 4;
	k->y = 5;
	printf("%d %d %d\n", p->hp, p->x, p->y);
	printf("%d %d %d\n", k->hp, k->x, k->y);
	Pool.print();
	st_test* s = Pool.Alloc();;
	s->hp = 7;
	s->x = 8;
	s->y = 9;
	Pool.Free(s);
	Pool.Free(k);
	Pool.Free(p);
	//printf(" &(NewNode->data) %p\n", p);
	//printf("data %p\n", k);
	printf("p : %d %d %d\n", p->hp, p->x, p->y);
	printf("k : %d %d %d\n", k->hp, k->x, k->y);
	printf("s : %d %d %d\n", s->hp, s->x, s->y);
	st_test* l = Pool.Alloc();;
	st_test* w = Pool.Alloc();;
	st_test* g = Pool.Alloc();;
	st_test* m = Pool.Alloc();;
	printf("l : %d %d %d\n", l->hp, l->x, l->y);
	printf("w : %d %d %d\n", w->hp, w->x, w->y);
	printf("g : % d % d % d\n", g->hp, g->x, g->y);
	printf("m : % d % d % d\n", m->hp, m->x,m->y);
	Pool.Free(l);
	Pool.Free(w);
	Pool.Free(g);
	Pool.Free(m);
	Pool.print();
	p->hp = 1;
	p->x = 2;
	p->y = 3;
	Pool.print();
	//printf("%d\n",Pool.Free(k));
	//printf("%d\n", Pool.Free(k));
	//printf("%d\n", Pool.Free(p));
	//printf("%d %d %d\n", p->hp, p->x, p->y);
	//Pool.Free(p);//초기화
	return 0;
}
