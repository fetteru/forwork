/*
 * 迷宫寻路 - DFS & BFS 对比演示
 *
 * 迷宫约定：
 *   0 = 通路  1 = 墙壁
 *   S = 起点  E = 终点
 *   * = 路径  . = 搜索过的点
 *
 * 编译：g++ maze_solver.cpp -o maze_solver
 * 运行：maze_solver
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// 设置终端编码为 UTF-8（Windows 专用）
void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
}

// ---------- 1. 迷宫类 ----------
class Maze {
public:
    int rows, cols;
    vector<vector<int>> grid;   // 0=通路, 1=墙
    int startX, startY;         // 起点
    int endX, endY;             // 终点

    // 构造一个预设迷宫（0通路, 1墙壁）
    Maze(int r, int c) : rows(r), cols(c), grid(r, vector<int>(c, 0)) {
        startX = 0; startY = 0;
        endX = r - 1; endY = c - 1;
    }

    // 用预设地图（方便测试）
    void setPreset() {
        // 一个 8x8 的迷宫（保证起点到终点连通）
        int map[8][8] = {
            {0, 1, 0, 0, 0, 1, 0, 0},
            {0, 1, 0, 1, 0, 0, 0, 1},
            {0, 0, 0, 1, 0, 1, 0, 0},
            {0, 1, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 1, 1, 1, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 1, 1, 0, 1, 0, 0}
        };
        rows = 8; cols = 8;
        grid.assign(8, vector<int>(8, 0));
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                grid[i][j] = map[i][j];
        startX = 0; startY = 0;
        endX = 7; endY = 7;
    }

    // 打印迷宫（带路径和访问标记）
    // path: 路径上的点  visited: 搜索过的点
    void print(const vector<vector<bool>> &path,
               const vector<vector<bool>> &visited) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == startX && j == startY) {
                    cout << "S ";
                } else if (i == endX && j == endY) {
                    cout << "E ";
                } else if (grid[i][j] == 1) {
                    cout << "# ";     // 墙
                } else if (path[i][j]) {
                    cout << "* ";     // 路径
                } else if (visited[i][j]) {
                    cout << ". ";     // 访问过但不在路径上
                } else {
                    cout << "  ";     // 未访问的通路
                }
            }
            cout << endl;
        }
    }

    // 判断坐标是否可走
    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
    }
};

// ---------- 2. DFS 深度优先搜索 ----------
// 用栈（或递归），一条路走到黑，撞墙就回溯
class DFS_Solver {
public:
    Maze &maze;
    vector<vector<bool>> visited;
    vector<vector<bool>> path;
    bool found;
    int steps;  // 搜索步数（不是路径长度）

    // 四个方向：上右下左
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    DFS_Solver(Maze &m) : maze(m),
        visited(m.rows, vector<bool>(m.cols, false)),
        path(m.rows, vector<bool>(m.cols, false)),
        found(false), steps(0) {}

    // 递归 DFS
    bool dfs(int x, int y) {
        steps++;
        visited[x][y] = true;

        // 到达终点
        if (x == maze.endX && y == maze.endY) {
            path[x][y] = true;
            return true;
        }

        // 四个方向依次尝试
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (maze.isValid(nx, ny) && !visited[nx][ny]) {
                if (dfs(nx, ny)) {
                    path[x][y] = true;  // 回溯时标记路径
                    return true;
                }
            }
        }
        return false;
    }

    void solve() {
        dfs(maze.startX, maze.startY);
    }

    // 统计路径长度
    int pathLength() {
        int len = 0;
        for (int i = 0; i < maze.rows; i++)
            for (int j = 0; j < maze.cols; j++)
                if (path[i][j]) len++;
        return len;
    }
};

// ---------- 3. BFS 广度优先搜索 ----------
// 用队列，一圈一圈向外扩散，找到终点时一定是最短路径
class BFS_Solver {
public:
    Maze &maze;
    vector<vector<bool>> visited;
    vector<vector<bool>> path;
    vector<vector<pair<int,int>>> prev;  // 记录前驱，用来回溯路径
    bool found;
    int steps;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    BFS_Solver(Maze &m) : maze(m),
        visited(m.rows, vector<bool>(m.cols, false)),
        path(m.rows, vector<bool>(m.cols, false)),
        prev(m.rows, vector<pair<int,int>>(m.cols, {-1, -1})),
        found(false), steps(0) {}

    void solve() {
        queue<pair<int,int>> q;
        q.push({maze.startX, maze.startY});
        visited[maze.startX][maze.startY] = true;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int x = curr.first;
            int y = curr.second;
            steps++;

            // 到达终点
            if (x == maze.endX && y == maze.endY) {
                found = true;
                break;
            }

            // 四个方向扩散
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (maze.isValid(nx, ny) && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    prev[nx][ny] = {x, y};  // 记录从哪来的
                    q.push({nx, ny});
                }
            }
        }

        // 回溯找路径
        if (found) {
            int x = maze.endX, y = maze.endY;
            while (x != -1 && y != -1) {
                path[x][y] = true;
                auto p = prev[x][y];
                x = p.first;
                y = p.second;
            }
        }
    }

    int pathLength() {
        int len = 0;
        for (int i = 0; i < maze.rows; i++)
            for (int j = 0; j < maze.cols; j++)
                if (path[i][j]) len++;
        return len;
    }
};

// ---------- 4. 主函数 ----------
int main() {
    setupConsole();

    Maze maze(8, 8);
    maze.setPreset();

    cout << "========== 迷宫原始地图 ==========\n";
    vector<vector<bool>> empty(maze.rows, vector<bool>(maze.cols, false));
    maze.print(empty, empty);
    cout << "S = 起点, E = 终点, # = 墙\n\n";

    // ---- DFS ----
    cout << "========== DFS 深度优先搜索 ==========\n";
    DFS_Solver dfs(maze);
    dfs.solve();
    maze.print(dfs.path, dfs.visited);
    cout << "搜索格数: " << dfs.steps << "   路径长度: " << dfs.pathLength() << "\n";
    cout << "* = 路径   . = 搜索过但不在路径上\n\n";

    // ---- BFS ----
    cout << "========== BFS 广度优先搜索 ==========\n";
    BFS_Solver bfs(maze);
    bfs.solve();
    maze.print(bfs.path, bfs.visited);
    cout << "搜索格数: " << bfs.steps << "   路径长度: " << bfs.pathLength() << "\n";
    cout << "* = 路径(最短)   . = 搜索过但不在路径上\n\n";

    // 对比
    cout << "========== 对比总结 ==========\n";
    cout << "DFS 路径长度: " << dfs.pathLength() << "  (不一定最短)\n";
    cout << "BFS 路径长度: " << bfs.pathLength() << "  (一定最短)\n";
    cout << "DFS 搜索格数: " << dfs.steps << "\n";
    cout << "BFS 搜索格数: " << bfs.steps << "\n";

    return 0;
}
