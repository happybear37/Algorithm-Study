#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct NODE {
	int num;
	int dist;

	// �Ÿ� ��������
	bool operator < (NODE nxt) const {
		if (dist > nxt.dist) return true;
		if (dist < nxt.dist) return false;
		return false;
	}
};

vector<NODE> al[1001]; // ���� ����Ʈ
vector<NODE> copied[1001]; // �ܹ��� ������ ������ ������ dijkstra�� �� �� �� �����ϱ� ���� ���� ���� �����
int visited[2][1001]; // 0: �־��� ���� ���� ����, 1: �ݴ�� ���� ���� ����
int N, M, X; // N: ����� ����, M: ������ ����, X: ���� ����� ��� ��ȣ

// 1. X�� ��忡������ �ٸ� ��������� �ִ� �Ÿ��� ���Ѵ�.
// 2. ��� �ܹ��� ������ �ݴ�������� ������.
// 3. �� ���¿��� 1���� �� �� �� �����Ѵ�.
// 4. 1���� 3���� ��� visited�� ������ �պ� �Ÿ��� ���Ѵ�.
void dijkstra(int st, int flag) {
	priority_queue<NODE> q;
	q.push({ st, 0 });

	while (!q.empty()) {
		NODE now = q.top();
		q.pop();

		// now�� �������� ���� �Ÿ��� �̹� �ּҶ�� ����� Ž���� X
		if (visited[flag][now.num] <= now.dist) continue;
		visited[flag][now.num] = now.dist;

		for (int i = 0; i < al[now.num].size(); i++) {
			NODE nxt = al[now.num][i];
			int ndist = now.dist + nxt.dist; // ���� now������ �Ÿ� + (now~nxt)������ �Ÿ�

			if (ndist >= visited[flag][nxt.num]) continue; // �̹� �� ���� ���� ����Ǿ� �ִٸ� Ž�� X
			q.push({ nxt.num, ndist });
		}
	}
}

int main() {
	cin >> N >> M >> X;

	// init
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {
			visited[j][i] = 21e8;
		}
	}

	// input
	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		al[a].push_back({ b, c });
		copied[a].push_back({ b,c });
	}

	// 1. �־��� ���� ���� - X�� ���κ��� �� �������� �ִ� �Ÿ� ���ϱ�
	dijkstra(X, 0);

	// 2. ������ ���� �ٲٱ�
	for (int i = 1; i <= N; i++) {
		al[i].clear();
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < copied[i].size(); j++) {
			NODE tmp = copied[i][j];
			al[tmp.num].push_back({ i, tmp.dist });
		}
	}

	// 3. �ݴ�� ������ ���� ���� - X�� ���κ��� �� �������� �ִ� �Ÿ� ���ϱ�
	dijkstra(X, 1);

	// 4. 1���� 3���� ����� �պ� �ִ� �Ÿ� �� �ִ밪 ���ϱ�
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (visited[0][i] + visited[1][i] > ans) ans = visited[0][i] + visited[1][i];
	}

	// output
	cout << ans << "\n";

	return 0;
}