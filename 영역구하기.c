#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int map[101][101] = { 0, }; //��,0���� �ʱ�ȭ

int dx[4] = { 1, 0, -1, 0 }; //�����»�
int dy[4] = { 0, -1, 0, 1 };

int M = 0, N = 0; //N:���� M:����
int number = 0; //���簢���� ����
int s_x, s_y, f_x, f_y; //����x,y��ǥ ��x,y��ǥ
int visit[101][101] = { 0, };
int count[10000] = { 0, }; //�� ���� ����
int count_stack = 0; //count �迭 index����
int temp = 0;

void DFS(int y, int x);

int main()
{
	scanf("%d%d", &M, &N); //���� ���� 
	scanf("%d", &number); //���簢�� ����

	for (int i = 0; i < number; i++)
	{
		scanf("%d %d %d %d", &s_x, &s_y, &f_x, &f_y); //��ǥ�Է�

		for (int i = s_x; i < f_x; i++)
		{
			for (int j = s_y; j < f_y; j++)
			{
				map[j][i] = 1;
				visit[j][i] = 1;
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[j][i] == 0 && visit[j][i] == 0)
			{
				visit[j][i] = 1;
				count[count_stack]++;
				DFS(j, i);
				count_stack++;
			}
		}
	}
	printf("%d\n", count_stack);

	////����////
	for (int i = 0; i < count_stack - 1; i++)
	{
		for (int i = 0; i < count_stack - 1; i++)
		{
			if (count[i] > count[i + 1])
			{
				temp = count[i];
				count[i] = count[i + 1];
				count[i + 1] = temp;
			}
		}
	}

	for (int i = 0; i < count_stack; i++)
		printf("%d ", count[i]);
	printf("\n");
}

void DFS(int y, int x)
{
	int now_x = 0;//�����»�
	int now_y = 0;

	for (int i = 0; i < 4; i++)
	{
		now_y = y + dy[i];
		now_x = x + dx[i];

		if (now_x >= 0 && now_x < N && now_y >= 0 && now_y < M) //���� lock
		{
			if (map[now_y][now_x] == 0 && visit[now_y][now_x] == 0) //�湮�� �� ���� 0�̸�
			{
				visit[now_y][now_x] = 1; //�湮�� 1�� �ٲ�
				count[count_stack]++;    //�󿵿� ���� �ø�
				DFS(now_y, now_x);
			}
		}
	}
}