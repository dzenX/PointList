#include <stdlib.h>
#include <stdio.h>

struct Point {
	double x, y, z;
};

struct Node {
	struct Point p;
	struct Node* next;
};

struct Node* init(struct Point p) {
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->next = NULL;
	head->p = p;
};

void printList(struct Node* lst) {
	printf("List\n");
	while (lst) {
		printf("Point(%f, %f, %f);\n", lst->p.x, lst->p.y, lst->p.z);
		lst = lst->next;
	}
	printf("\n");
}

struct Node * push(struct Node * head, struct Point p) {
	struct Node *saved, *prev, *tmp;
	saved = head;
	tmp = (struct Node*)malloc(sizeof(struct Node));
	tmp->p = p;
	while ((head != NULL)&&((head->p.x*head->p.x + head->p.y*head->p.y + head->p.z*head->p.z)
		< (p.x*p.x + p.y*p.y + p.z*p.z))) {
		prev = head;
		head = head->next;
	}
	if (head == NULL) {
		prev->next = tmp;
		tmp->next = NULL;
	}
	else if (head == saved) {
		tmp->next = head;
		return tmp;
	}
	else {
		prev->next = tmp;
		tmp->next = head;
	}
	return saved;
}

struct Node* pop(struct Node* head) {
	struct Node* deleted = head;
	head = head->next;
	free(deleted);
	return head;
}

struct Node* deleteList(struct Node* head) {
	struct Node* next;
	if (head != NULL) {
		next = head->next;
		free(head);
		if (next != NULL) {
			deleteList(next);
		}
	}
	return NULL;
}

struct Node* changeOrder(struct Node * head) {
	struct Node *newOne, *tmp;
	newOne = head;
	head = head->next;
	newOne->next = NULL;
	while (head) {
		tmp = head;
		head = head->next;
		tmp->next = newOne;
		newOne = tmp;
	}
	return newOne;
}

int main() {
	struct Node * head;
	struct Point p,p1,p2,p3;
	p.x = 1;
	p.y = 1;
	p.z = 1;
	p1.x = 0;
	p1.y = 0;
	p1.z = 0;
	p2.x = 2;
	p2.y = 2;
	p2.z = 2;
	p3.x = 3;
	p3.y = 3;
	p3.z = 2;
	printf("Test of adding elems\n\n");
	head = init(p);
	printList(head);
	head = push(head, p1);
	printList(head);
	head = push(head, p3);
	printList(head);
	head = push(head, p2);
	printList(head);
	printf("Test of changing order of elems\n\n");
	head = changeOrder(head);
	printList(head);
	printf("Test of deleting head elem\n\n");
	head = pop(head);
	printList(head);
	printf("Test of deleting list\n\n");
	head = deleteList(head);
	printList(head);
	return 0;
}