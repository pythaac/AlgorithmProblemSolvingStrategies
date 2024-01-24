#include <iostream>

using namespace std;

int C, H, W, white;
char map[20][20];
int direction[][4] = { {-1, 0}, {0, 1}, {1,0}, {0, -1} };
int curve[][2][2] = {
	{{direction[0][0], direction[0][1]}, {direction[3][0], direction[3][1]}},
	{{direction[0][0], direction[0][1]}, {direction[1][0], direction[1][1]}},
	{{direction[1][0], direction[1][1]}, {direction[0][0], direction[0][1]}},
	{{direction[1][0], direction[1][1]}, {direction[2][0], direction[2][1]}},
	{{direction[2][0], direction[2][1]}, {direction[1][0], direction[1][1]}},
	{{direction[2][0], direction[2][1]}, {direction[3][0], direction[3][1]}},
	{{direction[3][0], direction[3][1]}, {direction[2][0], direction[2][1]}},
	{{direction[3][0], direction[3][1]}, {direction[0][0], direction[0][1]}},

	{{direction[0][0], direction[0][1]}, {direction[1][0]- direction[0][0], direction[1][1]- direction[0][1]}},
	{{direction[1][0], direction[1][1]}, {direction[2][0]- direction[1][0], direction[2][1]- direction[1][1]}},
	{{direction[2][0], direction[2][1]}, {direction[3][0]- direction[2][0], direction[3][1]- direction[2][1]}},
	{{direction[3][0], direction[3][1]}, {direction[0][0]- direction[3][0], direction[0][1]- direction[3][1]}}
};

bool in_range(int x1, int y1) {
	return 0 <= x1 && x1 < H &&  0 <= y1 && y1 < W;
}

bool is_white(int x1, int y1) {
	return map[x1][y1] == '.';
}

void get_input() {
	white = 0;
	cin >> H >> W;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> map[i][j];
			if (map[i][j] == '.') white++;
		}
	}
}

int get_count(int x, int y) {
	int count = 0;
	int i = x;
	int j = y;

	while (i < H) {
		while (j < W) {
			if (is_white(i, j)) {
				for (int d = 0; d < 12; d++) {
					int nw_i1 = i + curve[d][0][0];
					int nw_j1 = j + curve[d][0][1];
					int nw_i2 = nw_i1 + curve[d][1][0];
					int nw_j2 = nw_j1 + curve[d][1][1];

					if (in_range(nw_i1, nw_j1) && in_range(nw_i2, nw_j2) && is_white(nw_i1, nw_j1) && is_white(nw_i2, nw_j2)) {
						map[i][j] = '#';
						map[nw_i1][nw_j1] = '#';
						map[nw_i2][nw_j2] = '#';
						white -= 3;

						count += get_count(i, j + 1);

						map[i][j] = '.';
						map[nw_i1][nw_j1] = '.';
						map[nw_i2][nw_j2] = '.';
						white += 3;
					}
				}
				return count;
			}
			j++;
		}
		i++;
		j = 0;
	}
	
	if (white == 0) {
		return 1;
	}
	else {
		return 0;
	}
}


int main()
{
	cin >> C;
	for (int i = 0; i < C; i++) {
		get_input();
		cout << get_count(0, 0) << endl;
	}
}