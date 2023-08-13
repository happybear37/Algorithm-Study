#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, k; cin >> n >> k;

	int Dist[401][401] = { 0 };

	for (int i = 0;i < k;i++)
	{
		int a, b; cin >> a >> b;
		Dist[a][b] = -1;
		Dist[b][a] = 1;
	}

	for (int t = 1;t <= n;t++)
	{
		for (int i = 1;i <= n;i++)
		{
			for (int j = 1;j <= n;j++)
			{
				if (Dist[i][j] == 0)
				{
					if (Dist[i][t] == 1 && Dist[t][j] == 1) Dist[i][j] = 1;
					else if (Dist[i][t] == -1 && Dist[t][j] == -1) Dist[i][j] = -1;
				}
			}
		}
	}

	int s; cin >> s;
	for (int i = 0;i < s;i++)
	{
		int a, b; cin >> a >> b;

		cout << Dist[a][b] << "\n";
	}

	return 0;
}