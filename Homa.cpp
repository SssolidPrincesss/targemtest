#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <fstream>
using namespace std;


//Функция, которая ищет координаты символа target в лабиринте maze
//принимает лабиринт в виде константной ссылки на вектор строк и символ, который нужно найти
pair<int, int> findPoint(const vector<string>& maze, char target) {

    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == target) {
                return { i, j };
            }
        }
    }
    return { -1, -1 };
}

vector<string> findAndMarkShortestPath(vector<string> maze) {
    int rows = maze.size();
    if (rows == 0) return maze;
    int cols = maze[0].size();

    pair<int, int> start = findPoint(maze, 'S');
    pair<int, int> end = findPoint(maze, 'F');
    if (start.first == -1 || end.first == -1) return maze;

    const int steps[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    queue<pair<int, int>> q;
    vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols, { -1, -1 }));

    q.push(start);
    prev[start.first][start.second] = { -2, -2 };

    bool found = false;

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        if (curr == end) {
            found = true;
            break;
        }

        for (const auto& step : steps) {
            int x = curr.first + step[0];
            int y = curr.second + step[1];

            if (x >= 0 && x < rows && y >= 0 && y < cols &&
                prev[x][y].first == -1 && maze[x][y] != 'x') {

                prev[x][y] = curr;
                q.push({ x, y });
            }
        }
    }

    if (found) {
        pair<int, int> curr = end;

        while (prev[curr.first][curr.second].first != -2) {
            if (maze[curr.first][curr.second] != 'F' && maze[curr.first][curr.second] != 'S') {
                maze[curr.first][curr.second] = '*';
            }
            curr = prev[curr.first][curr.second];
        }
    }

    return maze;
}


int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл input.txt" << endl;
        return 1;
    }

    vector<string> maze;
    string line;
    size_t expected_length = 0;

    while (getline(inputFile, line)) {
        if (maze.empty()) {
            expected_length = line.size();
        } else if (line.size() != expected_length) {
            cerr << "Ошибка: все строки лабиринта должны быть одинаковой длины" << endl;
            inputFile.close();
            return 1;
        }
        maze.push_back(line);
    }
    inputFile.close();

    if (maze.empty()) {
        cerr << "Ошибка: файл input.txt пуст" << endl;
        return 1;
    }

    vector<string> result = findAndMarkShortestPath(maze);

    cout << "Результат:" << endl;
    for (const auto& row : result) {
        cout << row << endl;
    }

    return 0;
}
