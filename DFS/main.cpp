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
		if (visit[x] == false)//방문하지 않았다면
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
			if (visit[y] == false)//방문하지 않았다면
				q.push(y);
			visit[y] = true;
		}
	}
}

int main(void)
{
	// 노드 1에 연결된 노드 정보 저장 
	graph[1].push_back(2);
	graph[1].push_back(3);
	graph[1].push_back(8);

	// 노드 2에 연결된 노드 정보 저장 
	graph[2].push_back(1);
	graph[2].push_back(7);

	// 노드 3에 연결된 노드 정보 저장 
	graph[3].push_back(1);
	graph[3].push_back(4);
	graph[3].push_back(5);

	// 노드 4에 연결된 노드 정보 저장 
	graph[4].push_back(3);
	graph[4].push_back(5);

	// 노드 5에 연결된 노드 정보 저장 
	graph[5].push_back(3);
	graph[5].push_back(4);

	// 노드 6에 연결된 노드 정보 저장 
	graph[6].push_back(7);

	// 노드 7에 연결된 노드 정보 저장 
	graph[7].push_back(2);
	graph[7].push_back(6);
	graph[7].push_back(8);

	// 노드 8에 연결된 노드 정보 저장 
	graph[8].push_back(1);
	graph[8].push_back(7);

	bfs(1);
	return 0;
}