#include <iostream>
#include <set>

using namespace std;

int main()
{
    int T;
    cin >> T;

    int n;
		for (int t=0;t<T;t++)
		{
				cin >> n;
        char order;
        int num;
        multiset<int> ms;
        while (n--)
        {
            cin >> order >> num;
            if (order == 'I')
            {
                ms.insert(num);
            }
            else
            {
                if (!ms.empty() && num == -1)
                {
                    ms.erase(ms.begin());
                }
                else if (!ms.empty() && num == 1)
                {
                    auto iter = ms.end();
                    iter--;
                    ms.erase(iter);
                }
            }
        }
        if (ms.empty())
        {
            cout << "EMPTY" << '\n';
        }
        else
        {
            auto end_iter = ms.end();
            end_iter--;
            cout << *end_iter << ' ' << *ms.begin() << '\n';
        }
		}

    return 0;
}