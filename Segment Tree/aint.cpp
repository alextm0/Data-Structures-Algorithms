#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100005

struct SegmentTree {
	int size;
	int tree[MAXN * 4];

	// Elementul neutru pentru operația dorită (de exemplu, 0 pentru suma, -INF pentru maxim)
	int NEUTRAL_ELEMENT;

	// Funcția de combinare pentru operația dorită (de exemplu, suma sau maxim)
	int (*merge)(int, int);

	// Funcția pentru setarea unui element singur
	int SINGLE_ELEMENT(int value) {
		return value;
	}

	// Inițializare
	void init(int n, int neutral, int (*mergeFunc)(int, int)) {
		size = n;
		NEUTRAL_ELEMENT = neutral;
		merge = mergeFunc;
		fill(tree, tree + 4 * size, NEUTRAL_ELEMENT);
	}

	// Construcția arborelui de intervale
	void build(int a[], int node, int st, int dr) {
		if (st == dr) {
			tree[node] = SINGLE_ELEMENT(a[st]);
			return;
		}
		int mid = (st + dr) / 2;
		build(a, node * 2, st, mid);
		build(a, node * 2 + 1, mid + 1, dr);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	void build(int a[]) {
		build(a, 1, 1, size);
	}

	// Actualizare element la poziția specificată
	void update(int pos, int val, int node, int st, int dr) {
		if (st == dr) {
			tree[node] = SINGLE_ELEMENT(val);
			return;
		}
		int mid = (st + dr) / 2;
		if (pos <= mid)
			update(pos, val, node * 2, st, mid);
		else
			update(pos, val, node * 2 + 1, mid + 1, dr);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int pos, int val) {
		update(pos, val, 1, 1, size);
	}

	// Interogare pe interval
	int query(int l, int r, int node, int st, int dr) {
		if (l > dr || r < st)
			return NEUTRAL_ELEMENT;
		if (l <= st && dr <= r)
			return tree[node];

		int mid = (st + dr) / 2;
		int ans1 = query(l, r, node * 2, st, mid);
		int ans2 = query(l, r, node * 2 + 1, mid + 1, dr);
		return merge(ans1, ans2);
	}

	int query(int l, int r) {
		return query(l, r, 1, 1, size);
	}
};

// Funcții de combinare pentru suma
int sumMerge(int a, int b) {
	return a + b;
}

// Funcții de combinare pentru maxim
int maxMerge(int a, int b) {
	return max(a, b);
}

int main() {
	int n, m;
	cin >> n >> m;
	int a[MAXN];
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	// Exemplu pentru sumă
	SegmentTree st;
	st.init(n, 0, sumMerge);  // Neutral pentru sumă este 0
	st.build(a);

	while (m--) {
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1) {
			st.update(x + 1, y);
		} else {
			cout << st.query(x + 1, y) << '\n';
		}
	}

	return 0;
}
