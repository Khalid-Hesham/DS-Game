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
	int score1 = 0, score2 = 0;
	int pieces_won = 0;
	bool win = false;
	node* piece1 = NULL;
	node* piece2 = NULL;
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

int RollDice() {
	return rand() % 6 + 1;
}

void move(node** p, int n) {
	for (int i = 0; i < n; i++)
		*p = (*p)->next;
}

void Stats() {
	int score1 = player1.score1 + player1.score2;
	int score2 = player2.score1 + player2.score2;

	if (player1.pieces_won && player1.score2 >= 50)
		player1.win = true;
	if (player2.pieces_won && player2.score2 >= 50)
		player2.win = true;

	if (player1.score1 >= 50) {
		player1.score1 = 50;
		player1.piece1->data = 0;
		if (!player1.pieces_won)
			player1.pieces_won++;
	}

	if (player2.score1 >= 50) {
		player2.score1 = 50;
		player2.piece1->data = 0;
		if (!player2.pieces_won)
			player2.pieces_won++;
	}

	cout << "==================================================================\n";
	cout << "||\tPlayer1 Score: " << score1 << "\t\tPlayer2 Score: " << score2 << "\t||\n";
	cout << "||\tActive: " << player1.Active_Piece << "\t\t\tActive: " << player2.Active_Piece << "\t\t||\n";
	cout << "||\tPieces Won: " << player1.pieces_won << "\t\t\tPieces Won: " << player2.pieces_won << "\t\t||\n";
	cout << "==================================================================\n";
}

void Board(node* last) {
	node* p;
	p = last;
	move(&p, 24);

	cout << "\n\n\t\t            ";
	for (int i = 0; i < 3; i++) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
	cout << "\t\t            ";
	move(&p, 48); cout << p->data << "   "; move(&p, 4); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 47); cout << p->data << "   "; move(&p, 6); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 45); cout << p->data << "   "; move(&p, 8); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 43); cout << p->data << "   "; move(&p, 10); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 41); cout << p->data << "   "; move(&p, 12); cout << p->data << "\n\t\t";
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
	move(&p, 26); cout << "\n\t\t" << p->data << "                           "; move(&p, 26); cout << p->data << "\n\t\t";
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
	cout << "\n\t\t            ";
	move(&p, 19); cout << p->data << "   "; move(&p, 40); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 11); cout << p->data << "   "; move(&p, 42); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 9); cout << p->data << "   "; move(&p, 44); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 7); cout << p->data << "   "; move(&p, 46); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 5); cout << p->data << "   "; move(&p, 48); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 3);
	for (int i = 0; i < 3; i++) {
		cout << p->data << " ";
		move(&p, 51);
	}
	cout << endl;
}

void Start(node** last) {
	int turns = 0;
	while (!(player1.win || player2.win)) {
	start:
		system("pause");
		system("cls");
		int dice = RollDice();
		if (turns % 2 == 0) {
			Stats();
			Board(*last);
			cout << "\n\tPlayer 1 turn!.\n\tDice: " << dice << endl;
			if (dice == 6 && player1.Static_Piece) {
				if (player1.Static_Piece == 2) {
					player1.Static_Piece--; player1.Active_Piece++;
					player1.piece1 = player1_base;
					player1.piece1->data = 1;
				}
				else {
					int choice;
					cout << "If you want to move the active piece enter 1.\n";
					cout << "If you want to activate a static piece enter 2.\n";
					cin >> choice;
					if (choice == 1) {
						player1.score1 += dice;
						for (int i = 0; i < dice; i++) {
							player1.piece1->data = 0;
							if ((player1.piece1 == player2.piece1 || player1.piece1 == player2.piece2) && i != dice)
								player1.piece1->data = 2;
							player1.piece1 = player1.piece1->next;
							player1.piece1->data = 1;
						}
						if (player1.piece1 == player2.piece1 && player2.score1 != 50) {
							if (player2.Static_Piece) {
								player2.score1 = 0;
								player2.piece1 = NULL;
								player2.Active_Piece--; player2.Static_Piece++;
							}
							else {
								player2.score1 = player1.score2;
								player2.score2 = 0;
								player2.piece1 = player2.piece2;
								player2.piece2 = NULL;
								player2.Active_Piece--; player2.Static_Piece++;
							}
						}
						if (player1.piece1 == player2.piece2) {
							player2.score2 = 0;
							player2.piece2 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
					}
					else if (choice == 2) {
						player1.Static_Piece--; player1.Active_Piece++;
						player1.piece2 = player1_base;
						player1.piece2->data = 1;
					}
				}
				goto start;
			}
			else if (player1.Active_Piece) {
				if (player1.Active_Piece == 1 && player1.score1 < 50)
					goto move1;
				if (player1.score1 >= 50 && !player1.Static_Piece)
					goto move2;
				if (player1.Active_Piece == 1 && player1.score1 >= 50)
					goto skip;
				int choice;
				cout << "If you want to move piece 1 enter 1\n";
				cout << "If you want to move piece 2 enter 2\n";
				cin >> choice;
				if (choice == 1) {
				move1:
					player1.score1 += dice;
					for (int i = 0; i < dice; i++) {
						player1.piece1->data = 0;
						if ((player1.piece1 == player2.piece1 || player1.piece1 == player2.piece2) && i != dice)
							player1.piece1->data = 2;
						player1.piece1 = player1.piece1->next;
						player1.piece1->data = 1;
					}
					if (player1.piece1 == player2.piece1 && player2.score1 != 50) {
						if (player2.Static_Piece) {
							player2.score1 = 0;
							player2.piece1 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
						else {
							player2.score1 = player2.score2;
							player2.score2 = 0;
							player2.piece1 = player2.piece2;
							player2.piece2 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
					}
					if (player1.piece1 == player2.piece2) {
						player2.score2 = 0;
						player2.piece2 = NULL;
						player2.Active_Piece--; player2.Static_Piece++;
					}
				}
				else if (choice == 2) {
				move2:
					player1.score2 += dice;
					for (int i = 0; i < dice; i++) {
						player1.piece2->data = 0;
						if ((player1.piece2 == player2.piece1 || player1.piece2 == player2.piece2) && i != dice)
							player1.piece2->data = 2;
						player1.piece2 = player1.piece2->next;
						player1.piece2->data = 1;
					}
					if (player1.piece2 == player2.piece1 && player2.score1 != 50) {
						if (player2.Static_Piece) {
							player2.score1 = 0;
							player2.piece1 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
						else {
							player2.score1 = player2.score2;
							player2.score2 = 0;
							player2.piece1 = player2.piece2;
							player2.piece2 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
					}
					if (player1.piece2 == player2.piece2) {
						player2.score2 = 0;
						player2.piece2 = NULL;
						player2.Active_Piece--; player2.Static_Piece++;
					}
				}
				if (dice == 6)
					goto start;
			}
		}
		else {
			Stats();
			Board(*last);
			cout << "\n\tPlayer 2 turn!.\n\tDice: " << dice << endl;
			if (dice == 6 && player2.Static_Piece) {
				if (player2.Static_Piece == 2) {
					player2.piece1 = player2_base;
					player2.piece1->data = 2;
				}
				else {
					player2.piece2 = player2_base;
					player2.piece2->data = 2;
				}
				player2.Static_Piece--; player2.Active_Piece++;
				goto start;
			}
			else if (player2.Active_Piece) {
				if ((player2.score1 - player2.score2 <= 6 || !player2.piece2) && player2.score1 <= 50) {
					player2.score1 += dice;
					for (int i = 0; i < dice; i++) {
						player2.piece1->data = 0;
						if ((player2.piece1 == player1.piece1 || player2.piece1 == player1.piece2) && i != dice)
							player2.piece1->data = 1;
						player2.piece1 = player2.piece1->next;
						player2.piece1->data = 2;
					}
					if (player2.piece1 == player1.piece1 && player1.score1 != 50) {
						player1.score1 = 0; player1.piece1 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
					if (player2.piece1 == player1.piece2) {
						player1.score2 = 0; player1.piece2 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
				}
				else if (!player2.Static_Piece) {
					player2.score2 += dice;
					for (int i = 0; i < dice; i++) {
						player2.piece2->data = 0;
						if ((player2.piece2 == player1.piece1 || player2.piece2 == player1.piece2) && i != dice)
							player2.piece2->data = 1;
						player2.piece2 = player2.piece2->next;
						player2.piece2->data = 2;
					}
					if (player2.piece2 == player1.piece1 && player1.score1 != 50) {
						player1.score1 = 0; player1.piece1 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
					if (player2.piece2 == player1.piece2) {
						player1.score2 = 0; player1.piece2 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
				}
				if (dice == 6)
					goto start;
			}
		}
	skip:
		turns++;
	}
}


int main() {
	int dice;
	srand(time(0));

	node* last = NULL;
	InitializeGame(&last);

	Start(&last);
	
	if (player1.win)
		cout << "\n\tPLAYER 1 WON CONGRATS!!!\n";
	else
		cout << "\n\tPLAYER 2 WON CONGRATS!!!\n";

	return 0;
}
