#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class node {
public:
	int data;
	class node* next;
};

node* player1_base = NULL;
node* player2_base = NULL;


class player {
public:
	int Static_Piece = 2;
	int Active_Piece = 0;
	node* p1 = NULL;
	node* p2 = NULL;
};

player player1;
player player2;

void addToEmpty(node** last, int data = 0) {
	node *temp = new node;
	temp->data = data;
	*last = temp;
	(*last)->next = *last;
}

void append(node** last, int data = 0) {
	if (*last == NULL) {
		addToEmpty(last, data);
		return;
	}

	node* temp = new node;

	temp->data = data;
	temp->next = (*last)->next;
	(*last)->next = temp;
	*last = temp;
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
		append(last);
		if (i == 0)
			player1_base = *last;
		if (i == 26)
			player2_base = *last;
	}
}

void cls() {
	cout << "\033[2J\033[1;1H";
}

int RollDice() {
	return rand() % 6 + 1;
}

void move(node** p, int n) {
	for (int i = 0; i < n; i++)
		*p = (*p)->next;
}

void Board(node* last) {
	node* p;
	p = last;
	move(&p, 24);

	cout << "            ";
	for (int i = 0; i < 3; i++) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
	cout << "            ";
	move(&p, 48); cout << p->data << "   "; move(&p, 4); cout << p->data << endl;
	cout << "            ";
	move(&p, 47); cout << p->data << "   "; move(&p, 6); cout << p->data << endl;
	cout << "            ";
	move(&p, 45); cout << p->data << "   "; move(&p, 8); cout << p->data << endl;
	cout << "            ";
	move(&p, 43); cout << p->data << "   "; move(&p, 10); cout << p->data << endl;
	cout << "            ";
	move(&p, 41); cout << p->data << "   "; move(&p, 12); cout << p->data << endl;
	move(&p, 34);
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << "      "; move(&p, 13);
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		p = p->next;
	}
	move(&p, 26); cout << endl << p->data << "                           "; move(&p, 26); cout << p->data << endl;
	move(&p, 25);
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		move(&p, 51);
	}
	cout << "      "; move(&p, 39);
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		move(&p, 51);
	}
	cout << "\n            ";
	move(&p, 19); cout << p->data << "   "; move(&p, 40); cout << p->data << endl;
	cout << "            ";
	move(&p, 11); cout << p->data << "   "; move(&p, 42); cout << p->data << endl;
	cout << "            ";
	move(&p, 9); cout << p->data << "   "; move(&p, 44); cout << p->data << endl;
	cout << "            ";
	move(&p, 7); cout << p->data << "   "; move(&p, 46); cout << p->data << endl;
	cout << "            ";
	move(&p, 5); cout << p->data << "   "; move(&p, 48); cout << p->data << endl;
	cout << "            ";
	move(&p, 3);
	for (int i = 0; i < 3; i++) {
		cout << p->data << " ";
		move(&p, 51);
	}
	cout << endl;
}

int main() {
	int dice;
	srand(time(0));
	player player_1, player_2;

	node* last = NULL;
	InitializeGame(&last);

	traverse(last);
	cls();
	player2.p1 = player2_base;
	dice = RollDice();
	for (int i = 0; i < dice; i++) {
		player2.p1->data = 0;
		player2.p1 = player2.p1->next;
		player2.p1->data = 2;
	}
	Board(last);
	cout << dice;

	return 0;
}
