#include <stdio.h>

struct Date {
	int year;
	int month;
	int day;
};

struct student {
	int age;
	char name[50];
	float grade;
	struct Date *date;
};

int main()
{
	struct Date d = { 2017, 9, 27 };
	struct student s = { 23, "곽동훈", 4.5 };
	s.date = &d;
	printf("나이 : %d\n", s.age);
	printf("이름 : %s\n", s.name);
	printf("학점 : %f\n", s.grade);
	printf("날짜 : %d년 %d월 %d일\n", s.date->year, s.date->month, s.date->day);
	return 0;
}

