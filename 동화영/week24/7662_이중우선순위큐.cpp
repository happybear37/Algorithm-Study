// 7662 ���� �켱���� ť
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 1000000;
bool isPoped[MAX_N]; // 0:�������, 1:pop �߻���
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> asc; // �������� (��, �ε���)
priority_queue<pair<int, int>> desc; // �������� (�⺻)
int cnt, aliveCnt; // cnt: insert�� �� ����, aliveCnt: ���� pop���� �ʰ� �����ִ� ����

// INSERT ����
void insertPQ(int  num) {
	// �� pq�� push
	asc.push({ num, cnt });
	desc.push({ num, cnt });

	// �ű� ���ڰ� �������Ƿ� cnt ����
	aliveCnt++;
	cnt++;
}

// DELETE ����
void deletePQ(int prior, bool isAns) {
	if (aliveCnt == 0) return;

	int target = 0, targetInd = 0;
	if (prior == -1) { // �ּҰ� ã��
		while (!asc.empty()) {
			pair<int, int> mini = asc.top();
			asc.pop();
			if (isPoped[mini.second]) continue;

			target = mini.first;
			targetInd = mini.second;
			break;
		}
	}
	else if (prior == 1) { // �ִ밪 ã��
		while (!desc.empty()) {
			pair<int, int> maxi = desc.top();
			desc.pop();
			if (isPoped[maxi.second]) continue;

			target = maxi.first;
			targetInd = maxi.second;
			break;
		}
	}

	if (isAns) {
		cout << target << " ";
		return;
	}
	isPoped[targetInd] = true;
	aliveCnt--;
}

int main() {
	// input
	int T, Q, num;
	char act;

	cin >> T;
	for (int t = 1; t <= T; ++t) {
		// init
		cnt = 0, aliveCnt = 0;
		memset(isPoped, false, sizeof(isPoped));
		while (!asc.empty()) asc.pop();
		while (!desc.empty()) desc.pop();

		cin >> Q;
		for (int j = 0; j < Q; ++j) {
			cin >> act >> num;
			
			if (act == 'I') insertPQ(num); // insert ����
			else if (act == 'D') deletePQ(num, false); // delete ���� (false: �����)
		}

		// output
		if (aliveCnt == 0) cout << "EMPTY\n"; // �����ִ� ���ڰ� ������ EMPTY ���
		else {
			// ��¿� delete
			deletePQ(1, true);
			deletePQ(-1, true);
			cout << "\n";
		}
	}

	return 0;
}
