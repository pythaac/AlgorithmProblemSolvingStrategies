#include <iostream>
#define TREE_DEPTH (1 << 16)

using namespace std;

int segmentTree[TREE_DEPTH];
int fence[20000];
int C, N;

void getInput() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> fence[i];
	}
}

void segmenting(int l, int r, int idx) {
	if (l == r) {
		segmentTree[idx] = fence[l];
		return;
	}

	int mid = (r + l) / 2;
	segmenting(l, mid, idx * 2);
	segmenting(mid + 1, r, idx * 2 + 1);

	segmentTree[idx] = segmentTree[idx * 2] < segmentTree[idx * 2 + 1] ? segmentTree[idx * 2] : segmentTree[idx * 2 + 1];
}

int searching(int l, int r, int idx, int targetL, int targetR) {
	if (l == targetL && r == targetR) return segmentTree[idx];

	int mid = (r + l) / 2;
	if (mid+1 <= targetL) {
		return searching(mid + 1, r, idx * 2 + 1, targetL, targetR);
	}
	else if (targetR <= mid) {
		return searching(l, mid, idx * 2, targetL, targetR);
	}
	else {
		int left = searching(l, mid, idx * 2, targetL, mid);
		int right = searching(mid + 1, r, idx * 2 + 1, mid + 1, targetR);
		return left < right ? left : right;
	}
}

int getMaxSquare(int l, int r) {
	if (l == r) return fence[l];

	int minHeight = searching(0, N - 1, 1, l, r);
	int crntXY = (r - l + 1) * minHeight;

	int crntL = l;
	for (int i = l; i <= r; i++) {
		if (fence[i] == minHeight) {
			if ( i!=crntL){
				int partialMax = getMaxSquare(crntL, i - 1);
				crntXY = crntXY < partialMax ? partialMax : crntXY;
			}
			crntL = i + 1;
		}
	}

	if (crntL <= r) {
		int partialMax = getMaxSquare(crntL, r);
		crntXY = crntXY < partialMax ? partialMax : crntXY;
	}

	return crntXY;
}

int main()
{
	cin >> C;
	for (int i = 0; i < C; i++) {
		getInput();
		segmenting(0, N-1, 1);
		cout << getMaxSquare(0, N - 1) << endl;;
	}
}