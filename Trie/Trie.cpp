#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 1;

long long aint[MAXN * 4], n;

void build(int node, int st, int dr) {
	if (st == dr) {
		cin >> aint[node];  // Citim valorile direct în timpul construirii arborelui
		return;
	}

	int mid = (st + dr) / 2;
	build(node * 2, st, mid);
	build(node * 2 + 1, mid + 1, dr);
	aint[node] =
		aint[node * 2] + aint[node * 2 + 1];  // Calculăm suma pentru nodul curent
}

void update(int pos, int val, int node, int st, int dr) {
	if (st == dr) {
		aint[node] = val;
		return;
	}

	int mid = (st + dr) / 2;
	if (pos <= mid)
		update(pos, val, node * 2, st, mid);
	else
		update(pos, val, node * 2 + 1, mid + 1, dr);
	aint[node] = aint[node * 2] + aint[node * 2 + 1];
}

long long query(int x, int y, int node, int st, int dr) {
	if (x <= st && dr <= y) return aint[node];
	if (dr < x || y < st) return 0;

	int mid = (st + dr) / 2;
	long long s1 = query(x, y, node * 2, st, mid);
	long long s2 = query(x, y, node * 2 + 1, mid + 1, dr);
	return s1 + s2;
}

int main() {
	int m, op;
	cin >> n >> m;

	// Construim arborele folosind funcția build
	build(1, 1, n);

	while (m--) {
		cin >> op;
		if (op == 1) {
			int pos, val;
			cin >> pos >> val;
			update(pos, val, 1, 1, n);
		} else {
			int st, dr;
			cin >> st >> dr;
			cout << query(st, dr, 1, 1, n) << '\n';
		}
	}

	return 0;
}
