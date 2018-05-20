#include <iostream>
#include <string>
using namespace std;

int index = 0;

char command[7];
int number;
int arr[21];

int main()
{
	int com_num = 0;

	scanf("%d", &com_num);

	for (int i = 0; i < com_num; i++)
	{
		scanf("%s ", command);

		if (command[1] == 'd') //add
		{
			scanf("%d", &number);
			arr[number] = number;
		}
		else if (command[1] == 'e') //remove
		{
			scanf("%d", &number);
			arr[number] = 0;
		}
		else if (command[1] == 'o') //toggle
		{
			scanf("%d", &number);
			if (arr[number] == number)
				arr[number] = 0;
			else
				arr[number] = number;
		}
		else if (command[1] == 'h') //check
		{
			scanf("%d", &number);
			if (arr[number] == number)
				printf("1\n");
			else
				printf("0\n");
		}
		else if (command[1] == 'l')//all
		{
			for (int i = 1; i < 21; i++)
			{
				arr[i] = i;
			}
		}
		else if (command[1] == 'm') //empty
		{
			for (int i = 0; i < 20; i++)
			{
				arr[i] = 0;
			}
		}
	}
}