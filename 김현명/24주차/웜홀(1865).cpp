#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int tc;
int n, m;
int k;

struct r_no{
    int to;
    int ct;
};

vector<r_no> r_gp[502];
int r_vi[502][502];
int w_vi[502][502];

// ���� ����Ŭ�� �����ϴ����� ����.
// ���� ��ΰ� Ȯ���� �Ǿ������� �ѹ��� ������ �Ǹ� ���� ��찡 �����.
bool bellmfd()
{
    int up_dists[502] = {};
    for (int i = 0; i < n + 1; i++)
    {
        up_dists[i] = 21e8;
    }
    up_dists[1] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int v = 1; v < n + 1; v++)
        {
            int to_v, to_ct;
            for (int s = 0; s < r_gp[v].size(); s++)
            {
                to_v = r_gp[v][s].to;
                to_ct = r_gp[v][s].ct;

                if (up_dists[to_v] > up_dists[v] + to_ct)
                {
                    up_dists[to_v] = up_dists[v] + to_ct;
                    if (i == n - 1)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> tc;

    for (int ti = 0; ti < tc; ti++)
    {
        cin >> n >> m >> k;

        // �ڷᱸ�� �ʱ�ȭ �ϱ�
        memset(r_vi, -1, sizeof(r_vi));
        memset(w_vi, -1, sizeof(w_vi));
        for (int i = 0; i < n + 1; i++)
        {
            r_gp[i].clear();
        }

        // ���� ���� �Է� �ޱ�
        // ������̴�.
        int a, b, ct;
        int r_ct = 0;
        for (int i=0; i<m; i++)
        { 
            cin >> a >> b >> ct;

            r_gp[a].push_back({ b,ct });
            r_gp[b].push_back({ a,ct });
        }

        // ��Ȧ ���� �Է� �ޱ�
        // �ð��� �پ���.
        int w_ct = 0;
        for (int i = 0; i < k; i++)
        {
            cin >> a >> b >> ct;
            r_gp[a].push_back({ b,-ct });
            w_vi[a][b] = ct;
        }

        // ������ �������� �ð��� �پ������� ����.
        // ���, ���� ����Ŭ�� �����ϴ����� �Ǵ��Ѵ�.
        if (!bellmfd())
        {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
};