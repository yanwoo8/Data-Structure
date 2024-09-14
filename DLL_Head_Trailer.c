// DLL Double Linked List : ÀÌÁß ¿¬°á ¸®½ºÆ®
// header O, trailer O

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define element char
#define nullE '\0'

typedef struct DDLnode {
	struct DDLnode* prev;
	element elem;
	struct DDLnode* next;
} DDLnode;

// init() : initialize new DDL with head & trailer node
DDLnode* initDDL() {
	DDLnode* head = (DDLnode*)malloc(sizeof(DDLnode));
	DDLnode* trailer = (DDLnode*)malloc(sizeof(DDLnode));

	head->prev = NULL;
	head->elem = nullE;
	head->next = trailer;

	trailer->prev = head;
	trailer->elem = nullE;
	trailer->next = NULL;

	return head;
}

// add(list, r, e) : add node with 'e' to the rth position of the DDL 'head'.
DDLnode* addDDL(DDLnode* head, int r, element e) {

	// 1. find rth node
	int cnt = 1;
	DDLnode* fst = head->next;
	DDLnode* snd = head;

	// 1'. error
	if (fst == NULL) { printf("Where is the trailer?\n"); exit(1); }

	while (fst->next != NULL && cnt < r) {
		cnt++;
		fst = fst->next;
		snd = snd->next;
	}

	// 1-1. if rth position is invalid : end
	if (r < 1 || r > cnt) {
		printf("invalid position\n");
		return NULL;
	}

	// 1-2. if r is wrong position : make new node 
	else {
		DDLnode* newNode = (DDLnode*)malloc(sizeof(DDLnode));
		newNode->elem = e;
		newNode->next = NULL;
		newNode->prev = NULL;

		// code for debuging
		if (0) {
			printf("Address of fst: %p\n", (void*)fst);
			printf("Address of newNode: %p\n", (void*)newNode);
			printf("Value of newNode->next before assignment: %p\n\n", (void*)(newNode->next));

			printf("Address of snd: %p\n", (void*)snd);
			printf("Address of newNode: %p\n", (void*)newNode);
			printf("Value of newNode->prev before assignment: %p\n\n", (void*)(newNode->prev));

			printf("Value of fst->prev before assignment: %p\n", (void*)(fst->prev));
			printf("Value of snd->next before assignment: %p\n", (void*)(snd->next));
		}

		newNode->next = fst;
		newNode->prev = snd;
		fst->prev = newNode;
		snd->next = newNode;

		if (0) {
			printf("Value of newNode->next after assignment: %p\n", (void*)(newNode->next));
			printf("Value of newNode->prev after assignment: %p\n", (void*)(newNode->prev));
			printf("Value of fst->prev after assignment: %p\n", (void*)(fst->prev));
			printf("Value of snd->next after assignment: %p\n", (void*)(snd->next));
		}

		return newNode;
	}
}

// deleteDDL_R : delete rth node of DDL
void deleteDDL_R(DDLnode* head, int r) {
	if (head == NULL || head->next == NULL || head->next->next == NULL) {
		printf("no element\n");
		return;
	}

	// 1. find rth node
	int cnt = 1;
	DDLnode* fst = head->next;
	if (fst == NULL) { printf("Where is the trailer?\n"); exit(1); }
	while (fst->next != NULL && cnt < r) {
		cnt++;
		fst = fst->next;
	}

	// 1-1. if rth position is invalid : end
	if (r < 1 || r > cnt || fst->next == NULL) {
		printf("invalid position\n");
		return;
	}
	// 1-2. if r is wrong position : delete
	else {
		fst->prev->next = fst->next;
		fst->next->prev = fst->prev;
	}
	free(fst);
	return;
}

// deleteDDL_E : delete all node of DDL that element is 'e'

// getDDL : return element of rth node of DDL
element getDDL(DDLnode* head, int r) {
	if (head == NULL || head->next == NULL || head->next->next == NULL) {
		printf("no element\n");
		return nullE;
	}

	// 1. find rth node
	int cnt = 1;
	DDLnode* fst = head->next;
	DDLnode* snd = head;

	if (fst == NULL) { printf("Where is the trailer?\n"); exit(1); }
	while (fst->next != NULL && cnt < r) {
		cnt++;
		fst = fst->next;
		snd = snd->next;
	}

	// 1-1. if rth position is invalid : end
	if (r < 1 || r > cnt || fst->next == NULL) {
		printf("invalid position\n");
		return nullE;
	}
	// 1-2. if r is wrong position : return
	else {
		return fst->elem;
	}
}


void printDDL(DDLnode* head) {

	if (head == NULL || head->next == NULL || head->next->next == NULL)
	{
		printf("no element\n"); return;
	}

	DDLnode* curr = head->next;

	if (curr == NULL) { printf("Where is the trailer?\n"); exit(1); }

	while (curr->next != NULL) {
		printf("%c", curr->elem);
		curr = curr->next;
	}

	printf("\n");
	return;
}
