#include <iostream>
#include <string>
#define MAX_NUM 200000

using namespace std;

int C, N, M;
int member[MAX_NUM];
int fan[MAX_NUM];

void getInput() {
	string s_member, s_fan;
	cin >> s_member;
	cin >> s_fan;

	M = N = 0;

	for (int i = 0; i < s_member.length(); i++)
		s_member.at(i) == 'F' ? member[N++] = 0 : member[N++] = 1;
	for (int i = 0; i < s_fan.length(); i++)
		s_fan.at(i) == 'F' ? fan[M++] = 0 : fan[M++] = 1;
}

int getCount() {
	int count = 0;
	for (int i = 0; i < M - N + 1; i++) {
		int crnt = 0;
		for (int j = i; j < i + N; j++) {
			crnt += member[j - i] * fan[j];
			if (crnt > 0) break;
		}
		if (crnt == 0) count++;
	}
	return count;
}


int main()
{
	cin >> C;
	for (int i = 0; i < C; i++) {
		getInput();
		cout << getCount() << endl;
	}
}