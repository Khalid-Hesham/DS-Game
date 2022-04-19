#include <iostream>
using namespace std;


class node {
public:
	int data;
	class node* next;
};

node* player1 = NULL;
node* player1_1 = NULL;
node* player1_2 = NULL;
node* player1_3 = NULL;
node* player1_4 = NULL;
node* player2 = NULL;
node* player2_1 = NULL;
node* player2_2 = NULL;
node* player2_3 = NULL;
node* player2_4 = NULL;


class player {
public:
	int Static_Piece = 4;
	int Active_Piece = 0;
};

void addToEmpty(node** last, int data = 0) {
	node *temp = new node;
	temp->data = data;
	*last = temp;
	(*last)->next = *last;
}

void append(node** last, int index, int data = 0) {
	if (*last == NULL) {
		addToEmpty(last, data);
		player1 = *last;
		player1->data = 1;
		return;
	}

	node* temp = new node;

	temp->data = data;
	temp->next = (*last)->next;
	(*last)->next = temp;
	*last = temp;

	if (index == 26) {
		player2 = *last;
		player2->data = 2;
	}
}

void traverse(node* last) {
	node* p;
	p = last->next;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != last->next);

}

void InitializeGame(node** last) {
	for (int i = 0; i < 52; i++) {
		append(last, i);
	}
}

void cls() {
	cout << "\033[2J\033[1;1H";
}

int main() {
	node* last = NULL;
	InitializeGame(&last);
	traverse(last);

	return 0;
}
