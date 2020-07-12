#include <stdio.h>
#include <Windows.h>
void main()
{
	int num[9] = { 0 };
	int big = 0, loc = 0;

	system("title Kimkideok");
	printf("9개의 자연수 중에 최대값을 찾고 그 값의 위치를 찾는 프로그램입니다.\n\n");
	printf("100보다 작은 자연수 9개를 입력하세요.\n");
	for (int i = 0; i < 9; i++)
	{
		printf("%d번째 자연수 : ", i+1);
		scanf_s("%d", &num[i]);
	}

	for (int j = 0; j < 9; j++)
	{
		if (num[j] > big)
		{
			big = num[j];
			loc = j + 1;
		}
		else;
	}

	for (int k = 0; k < 9; k++)
	{
		printf("%d ", num[k]);
	}
	printf("\n");
	printf("가장 큰 수 : %d, 위치 : %d\n", big, loc);
}