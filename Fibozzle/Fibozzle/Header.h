#include<stdio.h>

struct emp
{
	char name[10];
	int age;
};

void filetest()
{
	struct emp e;
	FILE *p, *q;
	p = fopen("one.txt", "a");
	q = fopen("one.txt", "r");
	printf("Enter Name and Age:");
	scanf("%s %d", e.name, &e.age);
	fprintf(p, "%s %d", e.name, e.age);
	fclose(p);
	do
	{
		fscanf(q, "%s %d", e.name, e.age);
		printf("%s %d", e.name, e.age);
	} while (!feof(q));
}