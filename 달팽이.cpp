#include <iostream>
using namespace std;

int map[1001][1001] = {0, };
int num = 0;

int dx[4] = { 1, 0, -1, 0 }; //하 우 상 좌
int dy[4] = { 0, 1, 0, -1 };

int area(int col,int row);

int input;
int search;
int now_x = 0, now_y = 0;
int before_x = 0, before_y = 0;

int i = 0;

int main()
{
	scanf("%d",&input);
	scanf("%d", &search);
	num = input * input;

	map[0][0] = num;

	while(num != 1) //제일 가운데가 1일때 까지 반복
	{
		before_x = now_x;
		before_y = now_y;

		now_x = now_x + dx[i];
		now_y = now_y + dy[i];

		if (area(now_x, now_y) == 0 || map[now_x][now_y] != 0)
		{
			now_x = before_x;
			now_y = before_y;
			i++;
			i = i % 4;
		}
		else
			map[now_x][now_y] = --num;
	}

	//////출력///////
	for (int i = 0; i < input; i++)
	{
		for (int j = 0; j < input; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < input; i++)
	{
		for (int j = 0; j < input; j++)
		{
			if (map[i][j] == search)
			{
				printf("%d %d", i + 1, j + 1);
			}
		}
	}
}

int area(int col,int row)
{
	if (0 <= col && col < input && 0 <= row && row < input)
	{
		return 1;
	}
	return 0;
}