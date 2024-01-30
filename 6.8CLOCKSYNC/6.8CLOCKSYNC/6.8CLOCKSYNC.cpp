#include <iostream>
#define INF 0x7fffffff

using namespace std;

int C;
int clocks[16];
int switcher[10][5] = {
	{0, 1, 2, -1, -1},
	{3, 7, 9, 11, -1},
	{4, 10, 14, 15, -1},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15, -1},
	{3, 14, 15, -1, -1},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13},
};
int min_count;

void get_input(){
	for (int i = 0; i < 16; i++) {
		cin >> clocks[i];
	}
	min_count = INF;
}

int get_score() {
	int score = 0;
	for (int i = 0; i < 16; i++) {
		if (clocks[i] == 12) score++;
	}
	return score;
}

void go_switcher(int i) {
	if (clocks[i] == 12) clocks[i] = 3;
	else clocks[i]+=3;
}

void go_button(int button) {
	for (int i = 0; i < 5; i++) {
		int num_clocks = switcher[button][i];
		if (num_clocks == -1) break;

		go_switcher(num_clocks);
	}
}

void get_count(int crnt_score, int i, int count) {
	if (crnt_score == 16) min_count = count < min_count ? count : min_count;
	if (count >= min_count) return;
	if (i >= 10) return;

	for (int idx = 0; idx < 4; idx++) {
		int nw_score = get_score();
		get_count(nw_score, i+1, count + idx);
		go_button(i);
	}
}

int main()
{
	cin >> C;
	for (int i = 0; i < C; i++) {
		get_input();
		int crnt_score = get_score();
		get_count(crnt_score, 0, 0);
		cout << (min_count == INF ? -1 : min_count) << endl;
	}
}