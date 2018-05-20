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
	char *lexeme = malloc(sizeof(char) * 929); //문자열을 동적할당함
	int i;//토큰배열 인덱스

	printf("문자열을 입력하세요 : ");
	gets(lexeme); //문자열을 입력받음
	printf("-------------------------------------------------------------------\n");

	make_token(lexeme); //어휘 분석기

	printf("토큰 번호 : ");
	for (int i = 1; i <= index; i++)
	{
		printf("%d ", tocken[i]);
	}
	printf("\n");

	printf("변환 토큰 배열 : ");
	for (i = 1; i <= index; i++)
	{
		T_arr.tocken_arr[i] = tocken[i];
	}
	T_arr.tocken_arr[index + 1] = '$';

	for (int i = 1; i <= index; i++)
	{
		printf("%d ", T_arr.tocken_arr[i]); //입력영역 토큰번호 $ =36
	}
	printf("%c", T_arr.tocken_arr[index + 1]);
	printf("\n");
	LR();
	printf("\n");
	free(lexeme); // 문자열 메모리 해제
}

void make_token(char* lexeme)
{
	int i = 0; // 입력 문자열 배열 번호 변수

	printf("입력하신 문자열은 %s 입니다.\n", lexeme); //입력한 문자열 재확인

	printf("토큰으로 변환 중...\n");

	while (lexeme[i] != '\0') // 입력의 끝까지 반복
	{
		if (lexeme[i] == '+') // +일 경우
		{
			tocken[++index] = PLUS;
		}//메세지출력
		else if (lexeme[i] == '-') // -일 경우
		{
			tocken[++index] = MINUS;
		} //메세지출력
		else if (lexeme[i] == '*') // *일 경우
		{
			tocken[++index] = MULTY;
		} //메세지출력
		else if (lexeme[i] == '/') // /일 경우
		{
			tocken[++index] = DIVIDE;
		} //메세지출력
		else if (lexeme[i] == '(') // (일 경우
		{
			tocken[++index] = OPEN;
		} //메세지출력
		else if (lexeme[i] == ')') // )일 경우
		{
			tocken[++index] = CLOSE;
		} //메세지출력
		else if ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z'))
			//알파벳일 경우
		{
			while ((('a' <= lexeme[i]) && (lexeme[i] <= 'z')) || ('A' <= lexeme[i]) && (lexeme[i] <= 'Z'))
				//다음 문자도 알파벳인지 검사
			{
				lexeme[i++];
			}
			{
				tocken[++index] = ID;
			} // 알파벳 이외의 문자가 나오면 메세지출력
			i--; //백트랙킹 (예를들어 sum+일 경우 +를 읽고있을거기 때문에)
		}
		else if ('0' <= lexeme[i] && lexeme[i] <= '9')
			//숫자일 경우
		{
			while ('0' <= lexeme[i] && lexeme[i] <= '9')
				//다음 문자도 숫자인지 검사
			{
				lexeme[i++];
			}
			{
				tocken[++index] = NUM;
			} // 숫자 이외의 문자가 나오면 메세지출력
			i--; //백트랙킹 (예를들어 88-일 경우 -를 읽고있을거기 때문에)
		}
		else if (lexeme[i] == ' ')
		{
		}
		else // 위 경우에 전부 해당하지 않을때
		{
			printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
			exit(1);
		}

		i++; //다음 문자를 읽어옴
	}
}

int LR()
{
	int stack[929] = { 0, }; //스텍 배열, FAIL로 초기화
	int stack_num = 0; // 스텍 인덱스 변수
	int tocken_num = 1; // 토큰 인덱스 변수

	stack[0] = 0; //스텍의 첫번째는 0으로 시작한다.

	while (1)
	{
		//상태 0 ///////////////////////////////////////////////
		if (stack[stack_num] == 0)
		{
			if (T_arr.tocken_arr[tocken_num] == OPEN) //상태 0이고 (이면
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		//상태 1 ///////////////////////////////////////////////
		else if (stack[stack_num] == 1)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS) //상태 0이고 (이면
			{
				stack[++stack_num] = '+';
				stack[++stack_num] = 7;
				tocken_num++;
				printf("Shift 7\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == MINUS) //상태 0이고 (이면
			{
				stack[++stack_num] = '-';
				stack[++stack_num] = 8;
				tocken_num++;
				printf("Shift 8\n");
			}
			else if (T_arr.tocken_arr[tocken_num] == '$') //상태 0이고 (이면
			{
				printf("Accept!!!문법에 맞는 문자열입니다.\n");
				return 0;
			}
			else
			{
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 2//////////////////////////////////////////////
		else if (stack[stack_num] == 2)
		{
			if (T_arr.tocken_arr[tocken_num] == PLUS || T_arr.tocken_arr[tocken_num] == MINUS || T_arr.tocken_arr[tocken_num] == CLOSE || T_arr.tocken_arr[tocken_num] == '$') //상태 0이고 (이면
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 3//////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 4//////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 5//////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 6//////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 7//////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 8//////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 9//////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 10/////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		} 
		////상태 11/////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 12/////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 13/////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 14/////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 15/////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////상태 16/////////////////////////////////////////////
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
				printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
				return 0;
			}
		}
		////else////////////////////////////////////////////////
		else
		{
			printf("Parsing FAIL...문법에 맞지않는 문자열입니다.\n");
			return 0;
		}
	}
}