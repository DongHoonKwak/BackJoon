#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int map[51][51] = { 0, };
int visit[51][51] = { 0, };
int M, N; //가로 세로
int cab;
int x_dot, y_dot;
int x[4] = { 1,0,-1,0 };
int y[4] = { 0,-1,0,1 };
int bug[100] = { 0, };
int try;

void DFS(int y, int x);

int main()
{
	scanf("%d", &try);
	for (int k = 0; k < try; k++)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				visit[i][j] = 0;
				map[i][j] = 0;
			}
		}

		scanf("%d%d%d", &M, &N, &cab);

		for (int i = 0; i < cab; i++)
		{
			scanf("%d%d", &x_dot, &y_dot);
			map[x_dot][y_dot] = 1;
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (map[j][i] == 1 && visit[j][i] == 0)
				{
					visit[j][i] = 1;
					bug[k]++;
					DFS(j, i);
				}
			}
		}
	}
	for (int k = 0; k < try; k++)
		printf("%d\n", bug[k]);
}

void DFS(int c_y, int c_x)
{
	for (int i = 0; i < 4; i++)
	{
		int now_x = c_x + x[i];
		int now_y = c_y + y[i];

		if (map[now_y][now_x] == 1 && visit[now_y][now_x] == 0)
		{
			visit[now_y][now_x] = 1;
			DFS(now_y, now_x);
		}
	}
}