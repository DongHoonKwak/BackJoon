#include <stdio.h>

int map[1001][1001];
int visit[1001][1001];

int d_x[4] = { 1,0,-1,0 };//우하좌상
int d_y[4] = { 0,-1,0,1 };

int C, R; //col raw
int count = 0; //빙산의 개수
int zero[1000001]; //주위 0의 개수
int index = 0; //zero배열의 인덱스
int result = 0;
int input_count = 0;

void DFS(int x, int y);
void search(int x2, int y2);

int main()
{
	scanf("%d%d", &C, &R);

	if (3 <= C && C <= 300 && 3 <= R && R <= 300)
	{
		for (int i = 0; i < C; i++)
		{
			for (int j = 0; j < R; j++)
			{
				scanf("%d", &map[i][j]);
				
				if (map[i][j] > 0) //빙산이 들어오면
				{
					input_count++; //카운트
					if (input_count > 10000) //빙산이 10000개가 넘으면
					{
						return 0; //종료
					}
				}

				if (i == 0 || j == 0 || i == C-1 || j == R-1)
				{
					map[i][j] = 0; //각 테두리는 0으로 값을 바꿔줌
				}
			}
		}

		for (int i = 0; i < C; i++)
		{
			for (int j = 0; j < R; j++)
			{
				if (0 <= map[i][j] && map[i][j] <= 10)
				{}
				else  //입력값중 범위 외 숫자가 있으면 종료
					return 0;
			}
		}

		while (count < 2) //빙산의 개수가 2보다 작을동안 반복
		{
			count = 0;							//초기화
			for (int i = 0; i < 1000001; i++)
				zero[i] = 0;

			for (int i = 0; i < C; i++)
			{
				for (int j = 0; j < R; j++)
				{
					visit[i][j] = 0;
				}
			}

			index = 0;

			for (int i = 0; i < C; i++)  //DFS돌림
			{
				for (int j = 0; j < R; j++)
				{
					if (map[i][j] > 0 && visit[i][j] == 0)
					{
						visit[i][j] = 1;
						DFS(i, j);
						count++; //빙산의 개수
					}
					else if (map[i][j] == 0)
					{
						visit[i][j] = 1;
					}
				}
			}

			if (count < 2) //빙산의 개수가 2보다 작으면 녹여야함
			{
				for (int i = 0; i < C; i++)
				{
					for (int j = 0; j < R; j++)
					{
						if (map[i][j] > 0)
						{
							search(i, j); //주위 0의 개수를 저장해서 배열에 넣음
							index++;
						}
					}
				}

				index = 0;

				for (int i = 0; i < C; i++)
				{
					for (int j = 0; j < R; j++)
					{
						if (map[i][j] > 0)
						{
							map[i][j] = map[i][j] - zero[index]; //각 원소의 주위 0개수만큼 빼줌
							if (map[i][j] < 0)
							{
								map[i][j] = 0; //뺏을때 0보다 작아지면 0으로 만들어줌
							}
							index++;
						}
					}
				}
			}

			else if(count >= 2)
			{
				printf("%d", result); //일수 출력
				return 0;
			}

			if (count == 0) //빙산의 개수가 0이면 다 녹은것이므로 0 출력후 종료
			{
				printf("0");
				return 0;
			}

			result++;
		}
	}
}

void DFS(int x, int y)
{
	int now_x, now_y;

	for (int i = 0; i < 4; i++)
	{
		now_x = x + d_x[i];
		now_y = y + d_y[i];

		if (now_x >= 0 && now_x < C && now_y >= 0 && now_y < R) //당연한 소리
		{
			if (map[now_x][now_y] > 0 && visit[now_x][now_y] == 0)
			{
				visit[now_x][now_y] = 1;
				DFS(now_x, now_y);
			}
		}
	}
}

void search(int x2, int y2)
{
	int now_x2, now_y2;

	for (int i = 0; i < 4; i++)
	{
		now_x2 = x2 + d_x[i];
		now_y2 = y2 + d_y[i];

		if (now_x2 >= 0 && now_x2 < C && now_y2 >= 0 && now_y2 < R)
		{
			if (map[now_x2][now_y2] == 0)
			{
				zero[index]++;
			}
		}
	}
}
