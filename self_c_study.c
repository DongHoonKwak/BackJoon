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
	struct student s = { 23, "������", 4.5 };
	s.date = &d;
	printf("���� : %d\n", s.age);
	printf("�̸� : %s\n", s.name);
	printf("���� : %f\n", s.grade);
	printf("��¥ : %d�� %d�� %d��\n", s.date->year, s.date->month, s.date->day);
	return 0;
}

