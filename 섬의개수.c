#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int visit[51][51] = { 0, };
int input[51][51] = { 0, };
int w, h; // 너비와 높이
int x[8] = { 1,1,0,-1,-1,-1,0,1 };
int y[8] = { 0,-1,-1,-1,0,1,1,1 };
int count[1000] = { 0 , };
int k = 0;

void DFS(int c_x, int c_y);

int main()
{
	while (1)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				visit[i][j] = 0;
				input[i][j] = 0;
			}
		}
		scanf("%d%d", &w, &h);

		if (w == 0 && h == 0) // 0 입력받으면 끝
		{
			break;
		}

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				scanf("%d", &input[i][j]);
			}
		}

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (input[i][j] == 1 && visit[i][j] == 0)
				{
					visit[i][j] = 1;
					DFS(i, j);
					count[k]++;
				}
			}
		}
		k++;
	}
	for (int i = 0; i<k; i++)
		printf("%d\n", count[i]);
}

void DFS(int c_x, int c_y)
{
	for (int i = 0; i < 8; i++)
	{
		int now_x = c_x + x[i];
		int now_y = c_y + y[i];

		if (now_x >= 0 && now_x < h && now_y >= 0 && now_y < w)
		{
			if (input[now_x][now_y] == 1 && visit[now_x][now_y] == 0)
			{
				visit[now_x][now_y] = 1;
				DFS(now_x, now_y);
			}
		}
	}
}