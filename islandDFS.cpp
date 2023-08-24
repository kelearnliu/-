#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <stack>
#include <iterator>
#include <complex>
#include <algorithm>
#include <queue>
using namespace std;


size_t countN = 0;
vector<vector<int>> dirction = { {-1,0},{1,0},{0,-1},{0,1} };

void bfs(vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j)
{
    queue<pair<int, int>> que;
    que.push({ i,j });
    visited[i][j] = true;
    size_t sum = 1;
    while (!que.empty())
    {
        pair<int, int> p = que.front();
        que.pop();
        int curX = p.first;
        int curY = p.second;
        cout << "curX: " << curX << "curY: " << curY << endl;
        for (int k = 0; k < 4; k++)
        {
            int nextX = curX + dirction[k][0];
            int nextY = curY + dirction[k][1];
            // 判断
            if (nextX < 0 || nextX >= grid.size() || nextY < 0 || nextY >= grid[0].size()||grid[nextX][nextY]==0)
                continue;
            if (!visited[nextX][nextY])
            {
                cout << "插入nextX和nextY：" << nextX << " " << nextY << endl;
                que.push({ nextX,nextY });
                visited[nextX][nextY] = true;
                sum++;
            }
        }
    }
    countN = max(countN, sum);
    return;
}
void island()
{
    vector<vector<int>> grid = {
            {0,0,1,0,0,0,0,1,0,0,0,0,0 },
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0}	};
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, false));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (!visited[i][j] && grid[i][j] == 1)
            {
                bfs(grid, visited, i, j);
                cout << "本次遍历的i：" << i <<" j:"<<j<< endl;
                cout << "本次遍历的计数值countN:" << countN << endl;
            }
        }
    cout << "最大的面积countN:" << countN << endl;
    return;
}


size_t sum = 0;
void dfs(vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j)
{
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != 1
        || visited[i][j])
    {
        // 共用上面的countN
        countN = max(countN, sum);
        cout << "本次遍历的终止：" << i << " j:" << j << endl;
        cout << "本次遍历的计数值sum:" << sum << endl;
        cout << "本次遍历的计数值countN:" << countN << endl;
        sum = 0;
        return;
    }
    sum++;
    cout << "本次遍历的开始" << endl;
    cout << "i:" << i << " j:" << j << " sum:" << sum << endl;
    visited[i][j] = true;
    dfs(grid, visited, i - 1, j);
    dfs(grid, visited, i + 1, j);
    dfs(grid, visited, i, j - 1);
    dfs(grid, visited, i, j + 1);
}
void islandDfs()
{
    vector<vector<int>> grid = {
            {0,0,1,0,0,0,0,1,0,0,0,0,0 },
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0} };
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, false));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (!visited[i][j] && grid[i][j] == 1)
            {
                dfs(grid, visited, i, j);
            }
        }
    cout << "最大的面积countN:" << countN << endl;
    return;
}
int main()
{
    // 一个是求解面积  一个是求解最大的连通块
    islandDfs();
//    island();
}
