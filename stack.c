#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


// 스택 요소(element)의 자료형을 char로 정의
typedef char element;

// 스택의 노드를 구조체로 정의
typedef struct stackNode {
	element data;
	struct stackNode *link;
} stackNode;

// 스택의 top 노드를 지정하기 위해 포인터 top 선언
stackNode* top;

// 스택이 공백 상태인지 확인하는 연산
int isEmpty()
{
	if (top == NULL)
		return 1;
	else
		return 0;
}

// 스택의 top에 원소를 삽입하는 연산
void push(element item)
{
	stackNode* temp = (stackNode *)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top; // 삽입 노드를 top의 위에 연결
	top = temp; // top 위치를 삽입 노드로 이동
}

// 스택의 top에서 원소를 삭제하는 연산
element pop()
{
	element item;
	stackNode* temp = top;
	if (top == NULL) // 스택이 공백 리스트인 경우
	{
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else // 스택이 공백 리스트가 아닌 경우
	{
		item = temp->data;
		top = temp->link; // top 위치를 삭제 노드 아래로 이동
		free(temp); // 삭제된 노드의 메모리 반환
		return item; // 삭제된 원소 반환
	}
}

// 중위 표기식을 후위 표기식으로 변환하는 연산
void transform(const char *exp)
{
	printf("후위 표기식으로 바뀐 식 : ");
	char symbol;
	char str1[100] = { '0' }, str2[100] = { '0' };
	int i = 0, j = 0, length1 = strlen(exp);
	top = NULL;
	str1[j] = exp[i];
	j++;
	for (i = 1; i < length1; i++) // 1차 괄호 처리 (우선 순위)
	{
		symbol = exp[i];
		if (symbol == '*' || symbol == '/')
		{
			push(')');
			str1[j] = symbol; //심볼 삽입
			i++, j++;
			str1[j] = exp[i]; //다음값 삽입
			j++;
			str1[j] = pop(); //괄호 삽입
			j++;
		}
		else
		{
			str1[j] = symbol;
			j++;
		}
	}
	int length2 = strlen(str1);
	j = 0;
	for (i = 0; i < length2+1; i++) // 2차 연산값 처리
	{
		symbol = str1[i];
		if (symbol == '*' || symbol == '/' || 
			symbol == '+' || symbol == '-') // (연산값을 스탣에 push
			push(symbol);
		else if (symbol == ')') // 괄호가 있을 때
		{						//(곱셈, 나눗셈같은 우선 처리 연산)
			str2[j] = pop();
			printf("%c", str2[j]);
			j++;
		}
		else if (symbol == NULL) // 심볼이 비었을 때(마지막)
			printf("%c", pop());
		else					// 피연산값을 순서대로 출력 
		{
			str2[j] = symbol;
			printf("%c", str2[j]);
			j++;
		}
	}
	printf("\n");
}

void main()
{
	system("title Kimkideok");

	const char* express = "A*B-C/D";
	printf("입력한 중위 표기식 : %s\n", express);

	transform(express);
	
	getchar();
}