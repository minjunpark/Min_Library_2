#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

bool visit[9];
vector<int> graph[9];


void dfs(int value)
{
	visit[value] = true;
	printf("%d\n", value);
	for (int i = 0; i < graph[value].size(); i++)
	{
		int x = graph[value][i];
		if (visit[x] == false)//�湮���� �ʾҴٸ�
			dfs(x);
	}
}

void bfs(int value)
{
	queue<int>q;
	q.push(value);
	//printf("start : %d\n",value);

	visit[value] = true;

	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		printf("search : %d\n", x);

		for (int i = 0; i < graph[x].size(); i++)
		{
			int y = graph[x][i];
			if (visit[y] == false)//�湮���� �ʾҴٸ�
				q.push(y);
			visit[y] = true;
		}
	}
}

int main(void)
{
	// ��� 1�� ����� ��� ���� ���� 
	graph[1].push_back(2);
	graph[1].push_back(3);
	graph[1].push_back(8);

	// ��� 2�� ����� ��� ���� ���� 
	graph[2].push_back(1);
	graph[2].push_back(7);

	// ��� 3�� ����� ��� ���� ���� 
	graph[3].push_back(1);
	graph[3].push_back(4);
	graph[3].push_back(5);

	// ��� 4�� ����� ��� ���� ���� 
	graph[4].push_back(3);
	graph[4].push_back(5);

	// ��� 5�� ����� ��� ���� ���� 
	graph[5].push_back(3);
	graph[5].push_back(4);

	// ��� 6�� ����� ��� ���� ���� 
	graph[6].push_back(7);

	// ��� 7�� ����� ��� ���� ���� 
	graph[7].push_back(2);
	graph[7].push_back(6);
	graph[7].push_back(8);

	// ��� 8�� ����� ��� ���� ���� 
	graph[8].push_back(1);
	graph[8].push_back(7);

	bfs(1);
	return 0;
}