// 1504 Ư���� �ִ� ���
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 213456789;

vector<pair<int, int>> al[801]; // �� ������ ����� ���� ����Ʈ
int cRoute; // v1�� v2 ������ �Ÿ�
int N, E; // N: ������ ����, E: ������ ����
int v1, v2; // �ʼ� ��� ����

pair<int, int> minDist(int st) {
	// st �������� Ž�� ������ �غ�
	int visited[801];
	for (int i = 1; i <= N; i++) visited[i] = INF;
	queue<int> q;
	q.push(st);
	visited[st] = 0;

	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		int sz = al[curr].size(); // curr�� ����� ������ Ž��
		for (int i = 0; i < sz; i++) {
			int nxt = al[curr][i].first; // ����� ������ nxt
			int amt = visited[curr] + al[curr][i].second; // ���� curr������ �Ÿ� + curr�� nxt ���� ������ �Ÿ�

			if (visited[nxt] <= amt) continue; // �̹� ã�� ��κ��� ������ �ƴϸ� ����

			q.push(nxt); // ������ Ž���� ����
			visited[nxt] = amt;
		}
	}

	// ������ ��� ������̶� v1->v2�� v2->v1�� ����
	// ���� �� ���� �����ϸ� �ȴ�
	if (st == v1) cRoute = visited[v2]; // v1�� v2 ������ �Ÿ�

	return { visited[1], visited[N] }; // 1��, N�� ���������� �Ÿ��� ��ȯ
}

int main() {
	int a, b, c;

	// input
	cin >> N >> E;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		al[a].push_back({ b, c }); // ����� ó��
		al[b].push_back({ a, c });
	}
	cin >> v1 >> v2; // �ʼ� �ڽ��� 2���� ����

	// 1 -> v1 -> v2 -> N (1�� ���)
	// 1 -> v2 -> v1 -> N (2�� ���)
	// ���� 2���� ��θ� ���Ͽ� �� ���� ���� ����ϸ� �ȴ�
	// ������ ��� ������̹Ƿ� �� ���� ������ �Ÿ����� ���ϸ� �ȴ�
	// ��, v1�������� 1�� N ������ �Ÿ�
	//     v2�������� 1�� N ������ �Ÿ�
	//     v1�� v2�� �Ÿ�
	pair<int, int> dist1 = minDist(v1); // v1���� 1�� N ������ �Ÿ�
	pair<int, int> dist2 = minDist(v2); // v2���� 1�� N ������ �Ÿ�

	// cRoute �� v1�� v2 ������ �Ÿ�
	int route1 = dist1.first + cRoute + dist2.second; // 1�� ���
	int route2 = dist1.second + cRoute + dist2.first; // 2�� ���

	// �� ���� ���� ��� output
	if (route1 >= INF && route2 >= INF) cout << "-1\n"; // 2���� ��� �������� ���� ���
	else if (route1 < route2) cout << route1 << "\n";
	else cout << route2 << "\n";

	return 0;
}