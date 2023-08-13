#include <iostream>
#include <queue>

using namespace std;

int Dr[2][4] = {
    -1,1,0,0,
    0,0,-1,1,
};

int N;
string MAP[100];
string MAP2[100];

int visited_a[100][100];
int visited_b[100][100]; // 적록색약 R==G

void BFS(string map[100],int ver,int starty, int startx)
{
    queue<int> qy;
    queue<int> qx;

    qy.push(starty);
    qx.push(startx);

    if (ver) visited_a[starty][startx] = 1;
    else visited_b[starty][startx] = 1;

    char now = map[starty][startx];

    while (!qy.empty())
    {
        int nowy = qy.front(); qy.pop();
        int nowx = qx.front(); qx.pop();

        int flag = 0;
        if (map[nowy][nowx] != now) flag = 1;

        for (int i = 0;i < 4;i++)
        {
            int nexty = nowy + Dr[0][i];
            int nextx = nowx + Dr[1][i];

            if (nexty < 0 || nextx < 0 || nexty >= N || nextx >= N) continue;

            if (map[starty][startx] != map[nexty][nextx]) continue;

            if (ver && visited_a[nexty][nextx] == 0)
            {
                visited_a[nexty][nextx] = 1;
            }
            else if (!ver && visited_b[nexty][nextx] == 0)
            {
                visited_b[nexty][nextx] = 1;
            }
            else continue;


            qy.push(nexty); qx.push(nextx);
        }
    }
}

int main()
{
    cin >> N;

    for (int i = 0;i < N;i++)
    {
        cin >> MAP[i];
        string s; s = MAP[i];
        for (int j = 0;j < N;j++)
        {
            if (s[j] == 'R') s[j] = 'G';
        }
        MAP2[i] = s;
    }
    int a = 0, b = 0;

    // 비장애인
    for (int i = 0;i < N;i++)
    {
        for (int j = 0;j < N;j++)
        {
            if (visited_a[i][j] == 0)
            {
                a++;
                BFS(MAP,1,i, j);
            }
        }
    }

    // 장애인
    for (int i = 0;i < N;i++)
    {
        for (int j = 0;j < N;j++)
        {
            if (visited_b[i][j] == 0)
            {
                b++;
                BFS(MAP2,0, i, j);
            }
        }
    }


    cout << a << " " << b;

    return 0;
}