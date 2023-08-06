#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int v1, v2;

struct g_no {
    int to;
    int ct;
};

vector<g_no> s_gp[802];

struct d_no {
    int to;
    int ct;

    bool operator < (d_no now) const
    {
        if (ct > now.ct)
        {
            return true;
        }
        if (ct < now.ct)
        {
            return false;
        }
        return false;
    }
};

int dists[802];

void d_search(int sv)
{
    priority_queue<d_no> pq = {};
    pq.push({ sv,0 });

    dists[sv] = 0;

    while (!pq.empty())
    {
        d_no n_no = pq.top();
        pq.pop();

        int to_v, to_ct;
        if (dists[n_no.to] < n_no.ct) { continue; }

        for (int s = 0; s < s_gp[n_no.to].size(); s++)
        {
            to_v = s_gp[n_no.to][s].to;
            to_ct = s_gp[n_no.to][s].ct;

            if (dists[to_v] <= dists[n_no.to] + to_ct) { continue; }
            dists[to_v] = dists[n_no.to] + to_ct;
            pq.push({ to_v, dists[n_no.to] + to_ct });
        }
    }
    return;
}

int main() {
    cin >> n >> m;

    // �׷��� ���� �Է�
    int a, b, in_ct;
    for (int i=0; i<m; i++)
    {
        cin >> a >> b >> in_ct;
        s_gp[a].push_back({ b,in_ct });
        s_gp[b].push_back({ a, in_ct });
    }

    cin >> v1 >> v2;

    long long p1_dist = 0;
    long long p2_dist = 0;


    // ���ۺ��� �������� �̵��ϸ鼭 v1�� v2�� �ݵ�� �湮�ؾ� �Ѵ�.
    // ���1: 1-v1-v2-n
    // ���2: 1-v2-v1-n
    // ���� ��θ� ����ϰ� ����Ѵ�.
    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 21e8;
    }
    d_search(1);

    p1_dist += dists[v1];
    p2_dist += dists[v2];

    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 21e8;
    }
    d_search(n);

    p1_dist += dists[v2];
    p2_dist += dists[v1];

    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 21e8;
    }
    d_search(v1);

    p1_dist += dists[v2];
    p2_dist += dists[v2];

    // ��� ����� ���� �ּҰ� �Ǵ� ��츦 ���Ѵ�.
    long long s_dist = min(p1_dist, p2_dist);

    // ����� ���� ���ٸ� -1 ���, �ƴϸ� �ּ� ����� ����Ѵ�.
    if (s_dist >= 21e8)
    {
        cout << -1 << endl;
    }
    else {
        cout << s_dist << endl;
    }
    return 0;
};