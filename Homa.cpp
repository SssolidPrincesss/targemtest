#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <fstream>
#include <optional>

// Константы для специальных значений в матрице prev
const std::pair<int, int> UNVISITED = { -1, -1 };  // Ячейка ещё не посещена
const std::pair<int, int> START_MARKER = { -2, -2 }; // Маркер стартовой точки

// Метод для чтения лабиринта из файла
std::optional<std::vector<std::string>> readMazeFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: couldn't open file " << filename << std::endl;
        return std::nullopt;
    }

    std::vector<std::string> maze;
    std::string line;
    size_t expected_length = 0;

    while (std::getline(inputFile, line)) {
        if (maze.empty()) {
            expected_length = line.size();
        }
        else if (line.size() != expected_length) {
            std::cerr << "Error: all maze rows must have equal length" << std::endl;
            inputFile.close();
            return std::nullopt;
        }
        maze.push_back(line);
    }
    inputFile.close();

    if (maze.empty()) {
        std::cerr << "Error: empty maze in file " << filename << std::endl;
        return std::nullopt;
    }

    return maze;
}

std::pair<int, int> findPoint(const std::vector<std::string>& maze, char target) {
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == target) {
                return { i, j };
            }
        }
    }
    return { -1, -1 };
}

void reconstructPath(std::vector<std::string>& maze,
    const std::vector<std::vector<std::pair<int, int>>>& prev,
    const std::pair<int, int>& start,
    const std::pair<int, int>& end) {
    std::pair<int, int> curr = end;
    while (curr != start) {
        if (maze[curr.first][curr.second] != 'F' &&
            maze[curr.first][curr.second] != 'S') {
            maze[curr.first][curr.second] = '*';
        }
        curr = prev[curr.first][curr.second];
    }
}

std::optional<std::vector<std::string>> findAndMarkShortestPath(std::vector<std::string> maze) {
    if (maze.empty()) {
        std::cerr << "Error: maze is empty" << std::endl;
        return std::nullopt;
    }

    const int rows = maze.size();
    const int cols = maze[0].size();

    const auto start = findPoint(maze, 'S');
    const auto end = findPoint(maze, 'F');

    if (start.first == -1) {
        std::cerr << "Error: starting point 'S' not found" << std::endl;
        return std::nullopt;
    }

    if (end.first == -1) {
        std::cerr << "Error: finishing point 'F' not found" << std::endl;
        return std::nullopt;
    }

    constexpr int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<std::pair<int, int>>> prev(
        rows, std::vector<std::pair<int, int>>(cols, UNVISITED)
    );

    q.push(start);
    prev[start.first][start.second] = START_MARKER;

    bool pathFound = false;

    while (!q.empty() && !pathFound) {
        const auto current = q.front();
        q.pop();

        if (current == end) {
            pathFound = true;
            break;
        }

        for (const auto& dir : directions) {
            const int x = current.first + dir[0];
            const int y = current.second + dir[1];

            if (x >= 0 && x < rows && y >= 0 && y < cols &&
                prev[x][y] == UNVISITED && maze[x][y] != 'x') {
                prev[x][y] = current;
                q.push({ x, y });
            }
        }
    }

    if (!pathFound) {
        std::cerr << "Error: path from 'S' to 'F' not found" << std::endl;
        return std::nullopt;
    }

    reconstructPath(maze, prev, start, end);
    return maze;
}

int main() {
    // Чтение лабиринта из файла
    auto maze = readMazeFromFile("input.txt");
    if (!maze) {
        return 1;
    }

    // Поиск и отметка кратчайшего пути
    auto result = findAndMarkShortestPath(*maze);
    if (!result) {
        return 1;
    }

    // Вывод результата
    std::cout << "Solution:\n";
    for (const auto& row : *result) {
        std::cout << row << '\n';
    }

    return 0;
}