#define _CRT_SECURE_NO_WARNINGS 
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <Windows.h>
#define MAX_NAME_LENGTH 50 
char seats[10] = { 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o' };

typedef struct 
{ 
	char name[MAX_NAME_LENGTH];
	int seat;
	char pay[5];
}element;

typedef struct treeNode 
{ 
	element key; 
	struct treeNode *left; 
	struct treeNode *right; 
}treeNode;

treeNode* insertKey(treeNode *p, element key) 
{
	treeNode *newNode; 
	int compare;

	if (p == NULL) 
	{ 
		newNode = (treeNode*)malloc(sizeof(treeNode)); 
		newNode->key = key; 
		newNode->left = NULL; 
		newNode->right = NULL; 
		return newNode; 
	}
	else 
	{ 
		compare = strcmp(key.name, p->key.name); 
		if (compare < 0) 
			p->left = insertKey(p->left, key); 
		else if (compare > 0) 
			p->right = insertKey(p->right, key); 
		else 
			printf("\n 이미 예약된 이름입니다! \n");
		return p; 
	}
}

void insert(treeNode** root, element key) 
{ 
	*root = insertKey(*root, key); 
}

void deleteNode(treeNode *root, element key) 
{ 
	treeNode *parent, *p, *succ, *succ_parent; 
	treeNode *child;

	parent = NULL; 
	p = root; 
	while ((p != NULL) && (strcmp(p->key.name, key.name) != 0)) 
	{ 
		parent = p; 
		if (strcmp(key.name, p->key.name)<0) 
			p = p->left; 
		else 
			p = p->right; 
	}
	
	if (p == NULL) 
	{ 
		printf("\n 예약된 좌석이 없습니다!"); 
		return; 
	}
 
	if ((p->left == NULL) && (p->right == NULL)) 
	{ 
		if (parent != NULL) 
		{ 
			if (parent->left == p) 
				parent->left = NULL; 
			else parent->right = NULL; 
		} 
		else root = NULL; 
	}
 
	else if ((p->left == NULL) || (p->right == NULL)) 
	{ 
		if (p->left != NULL) 
			child = p->left; 
		else  
			child = p->right;

		if (parent != NULL) 
		{ 
			if (parent->left == p) 
				parent->left = child; 
			else  
				parent->right = child; 
		}
		else 
			root = child;
	}

	else 
	{ 
		succ_parent = p; 
		succ = p->right; 
		while (succ->left != NULL) 
		{ 
			succ_parent = succ; 
			succ = succ->left; 
		} 
		if (succ_parent->left == succ) 
			succ_parent->left = succ->right; 
		else   
			succ_parent->right = succ->right;

		p->key = succ->key; 
		p = succ;
	} 
	free(p);
}
 
treeNode* searchBST(treeNode* root, element key) 
{ 
	treeNode* p;
	int compare; 
	p = root;

	while (p != NULL) 
	{ 
		compare = strcmp(key.name, p->key.name); 
		if (compare < 0) 
			p = p->left; 
		else if (compare > 0) 
			p = p->right;
		else 
		{ 
			printf("---------예약정보-----------");
			printf("\n\t예약자 명 : %s", p->key.name);
			return p; 
		} 
	} 
	return p;
}
 
void menu() 
{ 
	printf("\n*---------------------------*"); 
	printf("\n\t1 : 좌석 예약"); 
	printf("\n\t2 : 예약 조회"); 
	printf("\n\t3 : 좌석 변경");
	printf("\n\t4 : 예약 취소");
	printf("\n\t5 : 종료"); 
	printf("\n*---------------------------*\n  "); 
}

void view_seats()
{
	int cnt = 0;
	printf("\n\n        KPU 도서관");
	printf("\n-------좌석 배치도-------");
	printf("\n=========================\n");
	printf("1 2  3 4  5 6  7 8  9 10\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%c ", seats[i]);
		cnt++;
		if (cnt == 2)
		{
			printf(" ");
			cnt = 0;
		}
	}
	printf("\n=========================\n");
}

 const char* payment(int i)
{
	char cash[5] = "CASH";
	char card[5] = "CARD";
	if(i == 1) return cash;
	else if (i == 2) return card;
}

void main() 
{
	system("title 2015146003_Kimkideok");

	element e; 
	treeNode *root = NULL, *temp = NULL, *temp1 = NULL; 
	int choice, pay, pos, pos1, rm, chg;

	do { 
		view_seats();
		menu();
		scanf("%d", &choice);
	
		switch (choice) 
		{
		case 1: 
			printf("\n---------좌석예약-----------\n");
			while (1) {
				printf("\n좌석을 선택하세요\n(o : 사용가능, x : 사용중) : ");
				scanf("%d", &pos);
				if (seats[pos - 1] == 'x')	printf("이미 사용중인 좌석입니다.\n다시 선택해주세요.\n");
				else if (pos > 10) printf("없는 좌석입니다.\n다시 선택해주세요.\n");
				else if (pos < 1) printf("없는 좌석입니다.\n다시 선택해주세요.\n");
				else break;
			}
			seats[pos - 1] = 'x';
			e.seat = pos;
			printf("\n예약자 명을 입력하세요 : ");
			scanf("%s", e.name);
			while (1)
			{
				printf("\n결재수단을 선택하세요 : \n\t1 : cash \n\t2 : card\n");
				scanf("%d", &pay);
				if (pay == 1)
				{
					printf("\n계좌이체를 선택했습니다\n\n");
					break;
				}
				else if (pay == 2)
				{
					printf("\n카드결제를 선택했습니다\n\n");
					break;
				}
				else printf("\n잘못입력하셨습니다.\n");
			}
			strcpy(e.pay, payment(pay));
			insert(&root, e);
			break;
		case 2:
			printf("\n---------예약조회-----------\n");
			printf("\n예약자 명을 입력하세요 : ");
			scanf("%s", e.name);
			temp = searchBST(root, e);
			if (temp != NULL)
			{
				printf("\n\t예약좌석  : %d", temp->key.seat);
				printf("\n\t결제종류  : %s\n", temp->key.pay);
				printf("----------------------------\n");
			}
			else
				printf("\n조회할 수 없는 이름입니다.\n");
			break;
		case 3:
			printf("\n---------좌석변경-----------\n");
			printf("\n예약자 명을 입력하세요 : ");
			scanf("%s", e.name);
			temp = searchBST(root, e);
			if (temp != NULL)
			{
				printf("\n\t예약좌석  : %d", temp->key.seat);
				printf("\n\t결제종류  : %s\n", temp->key.pay);
				printf("----------------------------\n");
				printf("\n변경할 좌석을 입력하세요 : ");
				pos1 = temp->key.seat;
				scanf("%d", &pos);
				printf("\n%d번 자리로 변경하시겠습니까? : \n\t1: 예\n\t2: 아니요\n", pos);
				scanf("%d", &chg);
			}
			else
				printf("\n조회할 수 없는 이름입니다.\n");
			if (chg == 1)
			{
				temp->key.seat = pos;
				seats[pos1 - 1] = 'o';
				seats[pos - 1] = 'x';
			}
			else;
			break;
		case 4:
			printf("\n---------예약취소-----------\n");
			printf("\n예약자 명을 입력하세요 : ");
			scanf("%s", e.name);
			temp1 = searchBST(root, e);
			if (temp1 != NULL)
			{
				printf("\n\t예약좌석  : %d", temp->key.seat);
				printf("\n\t결제종류  : %s\n", temp->key.pay);
				printf("----------------------------\n");
				printf("\n예약을 취소하시겠습니까? \n\t1: 예\n\t2: 아니요\n");
				scanf("%d", &rm);
			}
			else
			{
				printf("\n조회할 수 없는 이름입니다.\n");
			}
			if (rm == 1)
			{
				pos = temp->key.seat;
				seats[pos - 1] = 'o';
				deleteNode(root, e);
			}
			else;
			break;
		} 
		while (getchar() != '\n');
	} 
	while (choice != 5);
}