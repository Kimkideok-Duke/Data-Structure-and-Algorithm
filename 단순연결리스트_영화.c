#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define SIZE 40


// 단순 연결 리스트의 노드 구조를 구조체로 정의
typedef struct ListNode {
	char data[SIZE];
	int year;
	struct ListNode* link;
} listNode;

// 리스트 시작을 나타내는 head 노드를 구조체로 정의
typedef struct {
	listNode* head;
} linkedList_h;

// 공백 연결 리스트를 생성하는 연산
linkedList_h* createLinkedList_h(void)
{
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;
	return L;
}

// 연결 리스트의 전체 메모리를 해제하는 연산
void freeLinkedList_h(linkedList_h* L)
{
	listNode* p;
	while (L->head != NULL)
	{
		p = L->head;
		L->head = L->head->link;
		free(p);
		p = NULL;
	}
}

void printList(linkedList_h* L)
{
	int Num = 0;
	listNode* p; // = NULL;
	p = L->head;
	while (p != NULL)
	{
		Num++;
		printf(" %d 제목: %s\t", Num, p->data);
		printf(" 년도: %d\n", p->year);
		p = p->link;
	}
}

void insertNode(linkedList_h* L, char *s, int y)
{
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, s);
	newNode->year = y;
	// 공백 리스트인 경우
	// 새 노드를 첫 번째이자 마지막 노드로 연결
	if (L->head == NULL)
	{
		newNode->link = NULL;
		L->head = newNode;
	}
	// 선행 노드가 있으면 그 다음 노드에 삽입되게 한다.
	else if (newNode == NULL)
	{
		newNode->link = L->head; // 새 노드를 첫 번째 노드로 삽입
		L->head = newNode;
	}
	else //리스트 중간에 삽입되게 한다.
	{
		newNode->link = L->head->link;
		L->head->link = newNode;
	}
}

int menu()
{
	int men = 0;
	printf(" --------------------\n");
	printf(" 1. 영화 정보 추가\n");
	printf(" 2. 영화 정보 출력\n");
	printf(" 3. 종료\n");
	printf(" --------------------\n");
	printf(" 번호를 선택하세요 : ");
	scanf("%d", &men);
	return men;
}

int main()
{
	int cho = 0, y;
	char s[40];
	linkedList_h* L;
	L = createLinkedList_h();
	while ((cho = menu()) != 3)
	{
		getchar();
		if (cho == 1)
		{
			printf(" 영화의 제목을 입력하세요 : ");
			scanf("%s", &s);
			printf(" 영화의 개봉 연도를 입력하세요 : ");
			scanf("%d", &y);
			insertNode(L, s, y);
		}
		else if (cho == 2)
		{
			printList(L);
			getchar();
		}
		else if (cho == 3)
		{
			freeLinkedList_h(L);
			break;
		}
		system("cls");
	}
	return 0;
}