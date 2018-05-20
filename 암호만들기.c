#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

int L, C; //��ȣ���� , ���� ����
char letter[10000];

int mo_count = 0; //���� ����
int ja_count = 0; //���� ����

char result[1000001];
int index = 0;

void Swap(char arr[], int a, int b);
char Partition(char arr[], int left, int right);
void Quick(char arr[], int left, int right);

int MoJa_count();
int DFS(int i);

int main()
{
	scanf("%d%d", &L, &C);  //��ȣ���� , ���� ����

	for (int i = 0; i < C; i++)
	{
		scanf(" %c", &letter[i]);
	}

	Quick(letter, 0, C - 1); //����
	for (int i = 0; i < C; i++)
	{
		result[index++] = letter[i];
		DFS(i+1); //���Ⱑ ��������
		index--;
	}
}

int MoJa_count() //���� ���� ���� ������
{
	mo_count = 0;
	ja_count = 0;
	for (int i = 0; i < L; i++)
	{
		if (result[i] == 'a' || result[i] == 'e' || result[i] == 'i' || result[i] == 'o' || result[i] == 'u')
			mo_count++;
		else
			ja_count++;
	}
	if (mo_count >= 1 && ja_count >= 2)
		return 1;
	else
		return 0;
}

//Quick���� �Լ�
void Swap(char arr[], int a, int b)
{
	char temp;

	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

char Partition(char arr[], int left, int right)
{
	char pivot;
	int low, high;

	pivot = arr[left];
	low = left + 1;
	high = right;

	while (low <= high)
	{
		while (pivot >= arr[low] && low <= right)
			low++;
		while (pivot <= arr[high] && high >= (left + 1))
			high--;
		if (low <= high)
			Swap(arr, low, high);
	}

	Swap(arr, left, high);

	return high;
}

void Quick(char arr[], int left, int right)
{
	int pivot;
	if (left <= right)
	{
		pivot = Partition(arr, left, right);
		Quick(arr, left, pivot - 1);
		Quick(arr, pivot + 1, right);
	}
}

int DFS(int i)
{
	for (int num = i; num < C; num++)
	{
		result[index++] = letter[num];

		if (index == L) //��ȣ�� ���̱��� �԰�
		{
			result[index] = '\0';
			if (MoJa_count() == 1) //����1�� ����2���̻��̸�
			{
				printf("%s\n", result);
			}			
		}
		if (num + 1 < C)
		{
			DFS(num + 1);
		}
		index--;
	}
}