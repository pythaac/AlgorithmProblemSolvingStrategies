#include <iostream>

using namespace std;

typedef struct Elt {
	int s;
	int e;
}Elt;

char quard_tree[1000];
char tmp[1000];

void get_input() {
	for (int i = 0; i < 1000; i++) {
		quard_tree[i] = 0;
		tmp[i] = 0;
	}
	cin >> quard_tree;
}

Elt upside_down(int s) {
	if (quard_tree[s] != 'x') {
		return Elt{ s, s + 1 };
	}

	Elt quard[4];
	int nw_s = s + 1;
	for (int i = 0; i < 4; i++) {
		Elt crnt = upside_down(nw_s);
		quard[i] = crnt;
		nw_s = crnt.e;
	}

	int rear_s = quard[2].s;
	int rear_e = quard[3].e;
	int head_s = quard[0].s;
	int head_e = quard[1].e;

	int len_rear = rear_e - rear_s;
	int len_head = head_e - head_s;

	for (int i = rear_s; i < rear_e; i++) {
		tmp[i - rear_s] = quard_tree[i];
	}
	for (int i = head_e-1; i >= head_s; i--) {
		quard_tree[i + len_rear] = quard_tree[i];
	}
	for (int i = 0; i < len_rear; i++) {
		quard_tree[i + head_s] = tmp[i];
	}

	return Elt{ s, rear_e };
}

int main()
{
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		get_input();
		upside_down(0);
		cout << quard_tree << endl;
	}
}