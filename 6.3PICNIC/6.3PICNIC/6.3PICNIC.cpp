#include <iostream>

using namespace std;

/*
	<놓쳤던 부분들>
	1. recursive 도중 visited == 0 일 때 depth를 내려가지 않은 것
	2. m == 0  인 case를 생각하지 못함
	3. 짝궁이 없는 case를 생각하지 못함
*/

int C, n, m;
int N = 10;

void init_jjak(int jjak[][10], int visited[10]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			jjak[i][j] = 0;
		}
		visited[i] = 0;
	}
}

void get_input(int jjak[][10], int visited[10]) {
	cin >> n >> m;
	int a = 0;
	int b = 0;

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		if (a != b) {
			jjak[a][b] = 1;
			jjak[b][a] = 1;
			visited[a] = 1;
			visited[b] = 1;
		}
	}
}

// 3.remaining
int count(int jjak[][10], int visited[10], int student, int remaining) {
	int cnt = 0;

	if (student == N) {
		if (remaining == 0)
			return 1;
		return 0;
	}

	if (visited[student] == 1) {
		for (int i = 0; i < N; i++) {
			if (jjak[student][i] == 1 && visited[i] == 1) {
				visited[student] = 0;
				visited[i] = 0;

				cnt += count(jjak, visited, student + 1, remaining -2);

				visited[student] = 1;
				visited[i] = 1;
			}
		}
	}
	// 1.
	else {
		cnt += count(jjak, visited, student + 1, remaining);
	}

	return cnt;
}

int main()
{
	int jjak[10][10];
	int visited[10];
	cin >> C;

	for (int i = 0; i < C; i++) {
		init_jjak(jjak, visited);
		get_input(jjak, visited);
		// 2.
		if (m == 0)
			cout << 0 << endl;
		else
			cout << count(jjak, visited, 0, n) << endl;
	}
}