#include <stdio.h>
#include <stdlib.h>

#define PLUS 1
#define MINUS 2
#define MULTY 3
#define DIVIDE 4
#define OPEN 5
#define CLOSE 6
#define ID 7
#define NUM 8

int tocken[929] = { 0, };
int index = 0;
void make_token(char* lexeme);
int LR();

typedef struct Tocken_arr {
	int tocken_arr[1000];
}Tocken_arr;

Tocken_arr T_arr;

int main()
{
	char *lexeme = malloc(sizeof(char) * 929); //���ڿ��� �����Ҵ���
	int i;//��ū�迭 �ε���

	printf("���ڿ��� �Է��ϼ��� : ");
	gets(lexeme); //���ڿ��� �Է¹���
	printf("-------------------------------------------------------------------\n");

	make_token(lexeme); //���� �м���

	printf("��ū ��ȣ : ");
	for (int i = 1; i <= index; i++)
	{
		printf("%d ", tocken[i]);
	}
	printf("\n");

	printf("��ȯ ��ū �迭 : ");
	for (i = 1; i <= index; i++)
	{
		T_arr.tocken_arr[i] = tocken[i];
	}
	T_arr.tocken_arr[index + 1] = '$';

	for (int i = 1; i <= index; i++)
	{
		printf("%d ", T_arr.tocken_arr[i]); //�Է¿��� ��ū��ȣ $ =36
	}
	printf("%c", T_arr.tocken_arr[index + 1]);
	printf("\n");
	LR();
	printf("\n");
	free(lexeme); // ���ڿ� �޸� ����
}

void make_token(char* lexeme)
{
	int i = 0; // �Է� ���ڿ� �迭 ��ȣ ����

	printf("�Է��Ͻ� ���ڿ��� %s �Դϴ�.\n", lexeme); //�Է��� ���ڿ� ��Ȯ��

	printf("��ū���� ��ȯ ��...\n");

	while (lexeme[i] != '\0') // �Է��� ������ �ݺ�
	{
		if (lexeme[i] == '+') // +�� ���
		{
			tocken[++index] = PLUS;
		}//�޼������
		else if (lexeme[i] == '-') // -�� ���
		{
			tocken[++index] = MINUS;
		} //�޼������
		else if (lexeme[i] == '*') // *�� ���
		{
			tocken[++index] = MULTY;
		} //�޼������
		else if (lexeme[i] == '/') // /�� ���
		{
			tocken[++index] = DIVIDE;
		} //�޼������
		else if (lexeme[i] == '(') // (�� ���
		{
			tocken[++index] = OPEN;
		} //�޼������
		else if (lexeme[i] == ')') // )�� ���
		{
			tocken[++index] = CLOSE;
		} //�޼������
		else if ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z'))
			//���ĺ��� ���
		{
			while ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z'))
				//���� ���ڵ� ���ĺ����� �˻�
			{
				lexeme[i++];
			}
			{
				tocken[++index] = ID;
			} // ���ĺ� �̿��� ���ڰ� ������ �޼������
			i--; //��Ʈ��ŷ (������� sum+�� ��� +�� �а������ű� ������)
		}
		else if ('0' <= lexeme[i] && lexeme[i] <= '9')
			//������ ���
		{
			while ('0' <= lexeme[i] && lexeme[i] <= '9')
				//���� ���ڵ� �������� �˻�
			{
				lexeme[i++];
			}
			{
				tocken[++index] = NUM;
			} // ���� �̿��� ���ڰ� ������ �޼������
			i--; //��Ʈ��ŷ (������� 88-�� ��� -�� �а������ű� ������)
		}
		else if (lexeme[i] == ' ')
		{
		}
		else // �� ��쿡 ���� �ش����� ������
		{
			printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
			exit(1);
		}

		i++; //���� ���ڸ� �о��
	}
}

int LR()
{
	int stack[929] = { 0, }; //���� �迭, FAIL�� �ʱ�ȭ
	int stack_num = 0; // ���� �ε��� ����
	int tocken_num = 1; // ��ū �ε��� ����

	stack[0] = 0; //������ ù��°�� 0���� �����Ѵ�.

	while (1)
	{
		//���� 0 ///////////////////////////////////////////////
		if (stack[stack_num] == 0)
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN) //���� 0�̰� (�̸�
			{
				stack[++stack_num] = '(';
				stack[++stack_num] = 4;
				tocken_num++;
				printf("Shift 4\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'id';
				stack[++stack_num] = 5;
				tocken_num++;
				printf("Shift 5\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'num';
				stack[++stack_num] = 6;
				tocken_num++;
				printf("Shift 6\n");
			}
			else if (stack[stack_num + 1] == 'E')
			{
				++stack_num;
				stack[++stack_num] = 1;
				printf("goto E\n");
			}
			else if (stack[stack_num + 1] == 'T')
			{
				++stack_num;
				stack[++stack_num] = 2;
				printf("goto T\n");
			}
			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = 3;
				printf("goto F\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		//���� 1 ///////////////////////////////////////////////
		else if (stack[stack_num] == 1)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS) //���� 0�̰� (�̸�
			{
				stack[++stack_num] = '+';
				stack[++stack_num] = 7;
				tocken_num++;
				printf("Shift 7\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == MINUS) //���� 0�̰� (�̸�
			{
				stack[++stack_num] = '-';
				stack[++stack_num] = 8;
				tocken_num++;
				printf("Shift 8\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == '$') //���� 0�̰� (�̸�
			{
				printf("Accept!!!������ �´� ���ڿ��Դϴ�.\n");
				return 0;
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 2//////////////////////////////////////////////
		else if (stack[stack_num] == 2)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$') //���� 0�̰� (�̸�
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						stack[i] = 'E';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = -1;
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 3		E->T\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == MULTY)
			{
				stack[++stack_num] = '*';
				stack[++stack_num] = 9;
				tocken_num++;
				printf("Shift 9\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == DIVIDE)
			{
				stack[++stack_num] = '/';
				stack[++stack_num] = 10;
				tocken_num++;
				printf("Shift 10\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 3//////////////////////////////////////////////
		else if (stack[stack_num] == 3)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == DIVIDE || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack[i] = 'T';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = -1;
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 6		T->F\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 4//////////////////////////////////////////////
		else if (stack[stack_num] == 4)
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN)
			{
				stack[++stack_num] = '(';
				stack[++stack_num] = 4;
				tocken_num++;
				printf("Shift 4\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'id';
				stack[++stack_num] = 5;
				tocken_num++;
				printf("Shift 5\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'num';
				stack[++stack_num] = 6;
				tocken_num++;
				printf("Shift 6\n");
			}
			else if (stack[stack_num + 1] == 'E')
			{
				++stack_num;
				stack[++stack_num] = 11;
				printf("goto E\n");
			}
			else if (stack[stack_num + 1] == 'T')
			{
				++stack_num;
				stack[++stack_num] = 2;
				printf("goto T\n");
			}
			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = 3;
				printf("goto F\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 5//////////////////////////////////////////////
		else if (stack[stack_num] == 5)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == DIVIDE || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'id')
					{
						stack[i] = 'F';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = -1;
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 8		F->id\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 6//////////////////////////////////////////////
		else if (stack[stack_num] == 6)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == DIVIDE || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'num')
					{
						stack[i] = 'F';
						for (int j = i + 1; j <= stack_num; j++)
						{
							stack[j] = -1;
						}
					}
				}
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 9		F->num\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 7//////////////////////////////////////////////
		else if (stack[stack_num] == 7)
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN)
			{
				stack[++stack_num] = '(';
				stack[++stack_num] = 4;
				tocken_num++;
				printf("Shift 4\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'id';
				stack[++stack_num] = 5;
				tocken_num++;
				printf("Shift 5\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'num';
				stack[++stack_num] = 6;
				tocken_num++;
				printf("Shift 6\n");
			}
			else if (stack[stack_num + 1] == 'T')
			{
				++stack_num;
				stack[++stack_num] = 12;
				printf("goto T\n");
			}

			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = 3;
				printf("goto F\n");
			}

			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 8//////////////////////////////////////////////
		else if (stack[stack_num] == 8)
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN)
			{
				stack[++stack_num] = '(';
				stack[++stack_num] = 4;
				tocken_num++;
				printf("Shift 4\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'id';
				stack[++stack_num] = 5;
				tocken_num++;
				printf("Shift 5\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'num';
				stack[++stack_num] = 6;
				tocken_num++;
				printf("Shift 6\n");
			}
			else if (stack[stack_num + 1] == 'T')
			{
				++stack_num;
				stack[++stack_num] = 13;
				printf("goto T\n");
			}

			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = 3;
				printf("goto F\n");
			}

			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 9//////////////////////////////////////////////
		else if (stack[stack_num] == 9)
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN)
			{
				stack[++stack_num] = '(';
				stack[++stack_num] = 4;
				tocken_num++;
				printf("Shift 4\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'id';
				stack[++stack_num] = 5;
				tocken_num++;
				printf("Shift 5\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'num';
				stack[++stack_num] = 6;
				tocken_num++;
				printf("Shift 6\n");
			}
			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = 14;
				printf("goto F\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 10/////////////////////////////////////////////
		else if (stack[stack_num] == 10)
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN)
			{
				stack[++stack_num] = '(';
				stack[++stack_num] = 4;
				tocken_num++;
				printf("Shift 4\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == ID)
			{
				stack[++stack_num] = 'id';
				stack[++stack_num] = 5;
				tocken_num++;
				printf("Shift 5\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == NUM)
			{
				stack[++stack_num] = 'num';
				stack[++stack_num] = 6;
				tocken_num++;
				printf("Shift 6\n");
			}
			else if (stack[stack_num + 1] == 'F')
			{
				++stack_num;
				stack[++stack_num] = 15;
				printf("goto F\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		} 
		////���� 11/////////////////////////////////////////////
		else if (stack[stack_num] == 11)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS)
			{
				stack[++stack_num] = '+';
				stack[++stack_num] = 7;
				tocken_num++;
				printf("Shift 7\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == MINUS)
			{
				stack[++stack_num] = '-';
				stack[++stack_num] = 8;
				tocken_num++;
				printf("Shift 8\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == CLOSE)
			{
				stack[++stack_num] = ')';
				stack[++stack_num] = 16;
				tocken_num++;
				printf("Shift 16\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 12/////////////////////////////////////////////
		else if (stack[stack_num] == 12)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == '+')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == 'T')
									{
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = -1;
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 1		E->E+T\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == MULTY)
			{
				stack[++stack_num] = '*';
				stack[++stack_num] = 9;
				tocken_num++;
				printf("Shift 9\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == DIVIDE)
			{
				stack[++stack_num] = '/';
				stack[++stack_num] = 10;
				tocken_num++;
				printf("Shift 10\n");
			}

			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 13/////////////////////////////////////////////
		else if (stack[stack_num] == 13)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == '-')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == 'T')
									{
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = -1;
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'E')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 2		E->E-T\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == MULTY)
			{
				stack[++stack_num] = '*';
				stack[++stack_num] = 9;
				tocken_num++;
				printf("Shift 9\n");
			}

			else if (T_arr.tocken_arr[tocken_num] == DIVIDE)
			{
				stack[++stack_num] = '/';
				stack[++stack_num] = 10;
				tocken_num++;
				printf("Shift 10\n");
			}

			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 14/////////////////////////////////////////////
		else if (stack[stack_num] == 14)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == DIVIDE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == '*')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == 'F')
									{
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = -1;
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 4		T->T*F\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 15/////////////////////////////////////////////
		else if (stack[stack_num] == 15)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == DIVIDE || T_arr.tocken_arr[tocken_num] == '$')
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == '/')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == 'F')
									{
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = -1;
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'T')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 5		T->T/F\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////���� 16/////////////////////////////////////////////
		else if (stack[stack_num] == 16)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$' || T_arr.tocken_arr[tocken_num] == MULTY || T_arr.tocken_arr[tocken_num] == DIVIDE)
			{
				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == '(')
					{
						for (int j = i + 1; j <= stack_num; j++)
						{
							if (stack[j] == 'E')
							{
								for (int k = j + 1; k <= stack_num; k++)
								{
									if (stack[k] == ')')
									{
										stack[i] = 'F';
										for (int m = i + 1; m <= stack_num; m++)
										{
											stack[m] = -1;
										}
									}
								}
							}
						}
					}
				}

				for (int i = 0; i <= stack_num; i++)
				{
					if (stack[i] == 'F')
					{
						stack_num = i - 1;
						break;
					}
				}
				printf("reduce 7		F->(E)\n");
			}
			else
			{
				printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
				return 0;
			}
		}
		////else////////////////////////////////////////////////
		else
		{
			printf("Parsing FAIL...������ �����ʴ� ���ڿ��Դϴ�.\n");
			return 0;
		}
	}
}