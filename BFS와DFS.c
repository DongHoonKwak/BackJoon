#define _SECURE_NO_WARNING
#include <stdio.h>

void DFS(int start);
void BFS(int start);

int map[1001][1001];
int visit_DFS[1001];
int visit_BFS[1001];

int queue[1001];
int rear = 0;
int front = 0;

int N; //정점의 개수(1~1000)
int M; //간선의 개수(1~10000)

int main()
{
	int start_num;

	int num1, num2;

	scanf("%d%d%d", &N, &M, &start_num);
	if (1 <= N && N <= 1000 && 1 <= M && M <= 10000)
	{
		for (int i = 0; i < M; i++)
		{
			scanf("%d%d", &num1, &num2);
			map[num1][num2] = map[num2][num1] = 1;
		}
		DFS(start_num);
		printf("\n");
		BFS(start_num);
	}
	else
		return 0;
}

void DFS(int start)
{
	visit_DFS[start] = 1;
	printf("%d ", start);

	for (int i = 1; i <= N; i++)
	{
		if (map[start][i] == 1 && !visit_DFS[i])
		{
			visit_DFS[i] = 1;
			DFS(i);
		}
	}
}

void BFS(int start)
{
	visit_BFS[start] = 1;
	queue[rear++] = start;

	while (front != rear)
	{
		start = queue[front++];
		printf("%d ", start);
		for (int i = 1; i <= N; i++)
		{
			if (map[start][i] == 1 && !visit_BFS[i])
			{
				visit_BFS[i] = 1;
				queue[rear++] = i;
			}
		}
	}
}