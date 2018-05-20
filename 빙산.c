#include <stdio.h>

int map[1001][1001];
int visit[1001][1001];

int d_x[4] = { 1,0,-1,0 };//�����»�
int d_y[4] = { 0,-1,0,1 };

int C, R; //col raw
int count = 0; //������ ����
int zero[1000001]; //���� 0�� ����
int index = 0; //zero�迭�� �ε���
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
				
				if (map[i][j] > 0) //������ ������
				{
					input_count++; //ī��Ʈ
					if (input_count > 10000) //������ 10000���� ������
					{
						return 0; //����
					}
				}

				if (i == 0 || j == 0 || i == C-1 || j == R-1)
				{
					map[i][j] = 0; //�� �׵θ��� 0���� ���� �ٲ���
				}
			}
		}

		for (int i = 0; i < C; i++)
		{
			for (int j = 0; j < R; j++)
			{
				if (0 <= map[i][j] && map[i][j] <= 10)
				{}
				else  //�Է°��� ���� �� ���ڰ� ������ ����
					return 0;
			}
		}

		while (count < 2) //������ ������ 2���� �������� �ݺ�
		{
			count = 0;							//�ʱ�ȭ
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

			for (int i = 0; i < C; i++)  //DFS����
			{
				for (int j = 0; j < R; j++)
				{
					if (map[i][j] > 0 && visit[i][j] == 0)
					{
						visit[i][j] = 1;
						DFS(i, j);
						count++; //������ ����
					}
					else if (map[i][j] == 0)
					{
						visit[i][j] = 1;
					}
				}
			}

			if (count < 2) //������ ������ 2���� ������ �쿩����
			{
				for (int i = 0; i < C; i++)
				{
					for (int j = 0; j < R; j++)
					{
						if (map[i][j] > 0)
						{
							search(i, j); //���� 0�� ������ �����ؼ� �迭�� ����
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
							map[i][j] = map[i][j] - zero[index]; //�� ������ ���� 0������ŭ ����
							if (map[i][j] < 0)
							{
								map[i][j] = 0; //������ 0���� �۾����� 0���� �������
							}
							index++;
						}
					}
				}
			}

			else if(count >= 2)
			{
				printf("%d", result); //�ϼ� ���
				return 0;
			}

			if (count == 0) //������ ������ 0�̸� �� �������̹Ƿ� 0 ����� ����
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

		if (now_x >= 0 && now_x < C && now_y >= 0 && now_y < R) //�翬�� �Ҹ�
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
