// 1865 ��Ȧ
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 213456789;

int MAP[501][501]; // �� ���� ���̿� �Ÿ� (�ּҰ�)
int visited[501]; // ������ �湮 ����
int N; // ������ ��

// �������� �˰���
// ���� ��θ� ������ �׷������� ��� Ž���ϴ� �˰���
bool BellmanFord(int st) {
	// st ���������������� ����!
	queue<pair<int, int>> q;
	q.push({ 0, st });
	visited[st] = 0;

	// N-1 �� ���� ��� ������ �湮�� �ϴ� ���̴�
	// N �� ���� (N-1)��°�� ���Ͽ� ���� ����Ŭ�� �����ϴ����� �Ǵ��Ѵ�
	for (int i = 1; i <= N; i++) {
		int sz = q.size(); // �̹����� queue�� ����ִ� �����鸸 ����Ѵ�
		for (int j = 0; j < sz; j++) {
			pair<int, int> curr = q.front();
			q.pop();

			for (int k = 1; k <= N; k++) {
				int amt = curr.first + MAP[curr.second][k]; // curr������ k������ �����ϴµ� �ɸ��� �� �ҿ�ð�

				if (MAP[curr.second][k] == 0) continue; // ���� ���� X��� ����
				if (visited[k] <= amt) continue; // �̹� �� ���� ��θ� ã�� k�����̶�� ����
				if (i == N) return true; // N��° �Ͽ� �� ���� ��θ� ã�Ҵٸ� ���� ����Ŭ�� �����Ѵٰ� �Ǵ�

				// k ������ �湮 ����
				q.push({ amt, k });
				visited[k] = amt;
			}
		}
	}
	
	return false; // ������� �Դٴ� ���� ���� ����Ŭ�� ��ã�Ҵٴ� ��
}

int main() {
	int tc;
	cin >> tc;
	
	for (int t = 1; t <= tc; t++) {
		// init
		memset(MAP, 0, sizeof(MAP));

		// input
		int M, W;
		int S, E, T;
		cin >> N >> M >> W;

		// �������� ������ �ߺ��� �����ϴٰ� ���´�
		// ������ Ǯ�̸� ���ؼ��� �ᱹ �� ��ο��� �ּ��� ���̸� �ʿ��ϴ�
		// ���� �� ��δ� ���� ���� ���� �Ÿ����� �����Ѵ�

		// �⺻ ���� - �����
		for (int i = 0; i < M; i++) {
			cin >> S >> E >> T;
			if (MAP[S][E] == 0 || MAP[S][E] > T) MAP[S][E] = T;
			if (MAP[E][S] == 0 || MAP[E][S] > T) MAP[E][S] = T;
		}

		// ��Ȧ - �ܹ���, ����
		for (int i = 0; i < W; i++) {
			cin >> S >> E >> T;
			if (MAP[S][E] == 0 || MAP[S][E] > -T) MAP[S][E] = -T;
		}

		// �� ������ �����ϴµ� �ɸ��� �Ÿ��� INF�� �ʱ�ȭ
		for (int i = 1; i <= N; i++) {
			visited[i] = INF;
		}

		// ��� �� �������� �����Ͽ� �� �������� ���ƿ��µ� ������ �ð��� �ɸ���
		// ��, ���� ����Ŭ�� �����ϴ°��� ã�� �����̴�
		// ��� ������������ �����ϴ� Ž���� �ϸ� �ð��ʰ��� �߻��Ѵ�
		// ���� 1�� �������� �������带 ������, ���Ŀ��� �̹湮�� �����鸸�� ���������� �Ͽ� �������� ������
		// �� �ѹ��̶� ���� ����Ŭ�� ã�Ҵٸ� YES�� ����Ѵ�
		bool isPossible = false;
		for (int i = 1; i <= N; i++) {
			if (visited[i] == INF) {
				if (BellmanFord(i)) {
					isPossible = true; // ���� ����Ŭ ã�Ҵ�
					break;
				}
			}
		}
		
		// output
		if(isPossible) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}