#define _SECURE_NO_WARNING
#include <stdio.h>

int visit[1001][1001] = {0, };
char map[1001][1001];
int queue_x[1000001] = {0, };
int queue_y[1000001] = {0, };

int front = -1;
int rear = -1;

int dx[4] = { 1, 0, -1, 0 }; //�����»�
int dy[4] = { 0, -1, 0, 1 };

int H, W;
char cheese = '1'; //ġ���
char food;
int s_x, s_y; //���� x,y��ǥ
int c_x, c_y; //ġ���� x,y��ǥ
int score = 0; //����
int result = 0;

void BFS(int x,int y);

int main()
{
	printf("���� : ");
	scanf(" %d", &H);
	printf("�� : ");
	scanf(" %d", &W);
	printf("���� : ");
	scanf(" %c", &food);

	for (int i = 0; i < H; i++)
	{
		scanf("%s", &map[i]);
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'S') //���� ��ġ ����
			{
				s_x = i;
				s_y = j;

				queue_x[++rear] = i;
				queue_y[rear] = j;
			}
			else if (map[i][j] == 'X') //���� �湮�ߴ� ġ��
			{
				visit[i][j] = 1;
			}
		}
	}

	while (cheese <= food)
	{
		for (int i = 0; i < H; i++) //ġ��ã��
		{
			for (int j = 0; j < W; j++)
			{
				if (map[i][j] == cheese)
				{
					c_x = i;
					c_y = j;
				}
			}
		}
		BFS(s_x,s_y);

		for (int i = 0; i < H; i++) //visit�ʱ�ȭ
		{
			for (int j = 0; j < W; j++)
			{
				visit[i][j] = 0;
			}
		}

		s_x = c_x;
		s_y = c_y;
		queue_x[++rear] = s_x;
		queue_y[rear] = s_y;

		cheese++;
	}

	printf("%d\n", result);
}

void BFS(int x,int y)
{
	int now_x, now_y;
	score = 0;

	while (front < rear)
	{
		x = queue_x[++front];
		y = queue_y[front];

		score++;

		for (int i = 0; i < 4; i++)
		{
			now_x = x + dx[i];
			now_y = y + dy[i];

			if (0 <= now_x && now_x < H && 0 <= now_y && now_y < W)
			{
				if (visit[now_x][now_y] == 0 && map[now_x][now_y] != 'X')
				{
					visit[now_x][now_y] = 1;
					if (map[now_x][now_y] == cheese)
					{
						result += score;
					}
					queue_x[++rear] = now_x;
					queue_y[rear] = now_y;
				}
			}
		}
	}
}