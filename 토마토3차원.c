#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

map[104][104][104];
visit[104][104][104];

int dx[6] = {1, 0, 0, -1, 0, 0}; //���� �丶�� Ž�� ����
int dy[6] = {0, 1, -1, 0, 0, 0};
int dz[6] = { 0, 0, 0, 0, 1, -1 };


int queue_x[1001];
int queue_y[1001];
int queue_z[1001];
int index = 0;

int M, N, H;
int day = 0;
int count = 1;

void DFS(int x, int y, int z);
int All_Non_Zero();

int main()
{
	scanf("%d%d%d", &M, &N, &H); //���� ���� ����

	for (int k = 0; k < H; k++) //�Է¹ޱ�
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				scanf("%d", &map[j][i][k]);
			}
		}
	}

	if (All_Non_Zero() == 1)
	{
		printf("0");
		return 0;
	}

	while (count != 0)
	{
		count = 0;
		for (int k = 0; k < H; k++) //����  //1�� ��ġ ����
		{
			for (int i = 0; i < N; i++) //����
			{
				for (int j = 0; j < M; j++) //����
				{
					if (map[j][i][k] == 1 && visit[j][i][k] == 0) //�丶�䰡 �ְ� �湮�� ��������
					{
						queue_x[index] = j;//�� ��ġ ����
						queue_y[index] = i;
						queue_z[index++] = k;
					}
				}
			}
		}

		for (int i = 0; i < index; i++) //1�� ��ġ���� BFS����
		{
			DFS(queue_x[i], queue_y[i], queue_z[i]);
		}

		day++;
	}

	if (All_Non_Zero() == 0)
	{
		printf("-1");
	}
	else
		printf("%d", day);
}
 //���� : x     ���� : y      ���� : z
void DFS(int x, int y, int z)
{
	int now_x;
	int now_y;
	int now_z;

	visit[x][y][z] = 1;

	for (int i = 0; i < 6; i++)
	{
		now_x = x + dx[i];
		now_y = y + dy[i];
		now_z = z + dz[i];

		if (0 <= now_x && now_x < M && 0 <= now_y && now_y < N && 0 <= now_z && now_z < H)
		{
			if (map[now_x][now_y][now_z] == 0 && visit[now_x][now_y][now_z] == 0) //�丶�䰡 ���� �湮�� ��������
			{
				map[now_x][now_y][now_z] = 1;
			}
		}
	}
}

int All_Non_Zero()
{
	for (int k = 0; k < H; k++) //����  
	{
		for (int i = 0; i < N; i++) //����
		{
			for (int j = 0; j < M; j++) //����
			{
				if (map[j][i][k] == 1 || map[j][i][k] == -1)
					continue;
			}
		}
	}
	return 1; //0�� �ϳ��� ������ 1��ȯ
}