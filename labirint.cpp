{\rtf1\ansi\ansicpg1251\cocoartf2821
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\froman\fcharset0 TimesNewRomanPSMT;\f1\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;\red33\green37\blue41;\red232\green62\blue140;}
{\*\expandedcolortbl;;\csgenericrgb\c12941\c14510\c16078;\csgenericrgb\c90980\c24314\c54902;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\deftab709
\pard\pardeftab709\partightenfactor0

\f0\fs24 \cf0 //\uc0\u1073 \u1080 \u1073 \u1083 \u1080 \u1086 \u1090 \u1077 \u1082 \u1080  \u1080  \u1087 \u1088 \u1086 \u1089 \u1090 \u1088 \u1072 \u1085 \u1089 \u1090 \u1074 \u1086  \u1080 \u1084 \u1077 \u1085 \
#include <iostream>\
#include <vector>\
#include <queue>\
#include <utility>\
#include <string>\
#include <fstream>\
using namespace std;\
\
\
//
\f1 \cf2 \uc0\u1060 \u1091 \u1085 \u1082 \u1094 \u1080 \u1103 , \u1082 \u1086 \u1090 \u1086 \u1088 \u1072 \u1103  \u1080 \u1097 \u1077 \u1090  \u1082 \u1086 \u1086 \u1088 \u1076 \u1080 \u1085 \u1072 \u1090 \u1099  \u1089 \u1080 \u1084 \u1074 \u1086 \u1083 \u1072 \'a0
\fs19 \cf3 target
\f0\fs24 \cf2 \'a0
\f1 \uc0\u1074  \u1083 \u1072 \u1073 \u1080 \u1088 \u1080 \u1085 \u1090 \u1077 \'a0
\fs19 \cf3 maze
\f0\fs24 \cf0 \
\pard\pardeftab709\partightenfactor0

\f1\fs19 \cf3 //
\fs24 \cf2 \uc0\u1087 \u1088 \u1080 \u1085 \u1080 \u1084 \u1072 \u1077 \u1090  \u1083 \u1072 \u1073 \u1080 \u1088 \u1080 \u1085 \u1090  \u1074  \u1074 \u1080 \u1076 \u1077  \u1082 \u1086 \u1085 \u1089 \u1090 \u1072 \u1085 \u1090 \u1085 \u1086 \u1081  \u1089 \u1089 \u1099 \u1083 \u1082 \u1080  \u1085 \u1072  \u1074 \u1077 \u1082 \u1090 \u1086 \u1088  \u1089 \u1090 \u1088 \u1086 \u1082  \u1080  \u1089 \u1080 \u1084 \u1074 \u1086 \u1083 , \u1082 \u1086 \u1090 \u1086 \u1088 \u1099 \u1081  \u1085 \u1091 \u1078 \u1085 \u1086  \u1085 \u1072 \u1081 \u1090 \u1080 
\f0 \cf0 \
pair<int, int> findPoint(const vector<string>& maze, char target) \{\
\
    for (int i = 0; i < maze.size(); ++i) \{\
        for (int j = 0; j < maze[i].size(); ++j) \{\
            if (maze[i][j] == target) \{\
                return \{ i, j \};\
            \}\
        \}\
    \}\
    return \{ -1, -1 \};\
\}\
\
vector<string> findAndMarkShortestPath(vector<string> maze) \{\
    int rows = maze.size();\
    if (rows == 0) return maze;\
    int cols = maze[0].size();\
\
    pair<int, int> start = findPoint(maze, 'S');\
    pair<int, int> end = findPoint(maze, 'F');\
    if (start.first == -1 || end.first == -1) return maze;\
\
    const int steps[4][2] = \{ \{-1, 0\}, \{1, 0\}, \{0, -1\}, \{0, 1\} \};\
    queue<pair<int, int>> q;\
    vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols, \{ -1, -1 \}));\
\
    q.push(start);\
    prev[start.first][start.second] = \{ -2, -2 \};\
\
    bool found = false;\
\
    while (!q.empty()) \{\
        auto curr = q.front();\
        q.pop();\
\
        if (curr == end) \{\
            found = true;\
            break;\
        \}\
\
        for (const auto& step : steps) \{\
            int x = curr.first + step[0];\
            int y = curr.second + step[1];\
\
            if (x >= 0 && x < rows && y >= 0 && y < cols &&\
                prev[x][y].first == -1 && maze[x][y] != 'x') \{\
\
                prev[x][y] = curr;\
                q.push(\{ x, y \});\
            \}\
        \}\
    \}\
\
    if (found) \{\
        pair<int, int> curr = end;\
\
        while (prev[curr.first][curr.second].first != -2) \{\
            if (maze[curr.first][curr.second] != 'F' && maze[curr.first][curr.second] != 'S') \{\
                maze[curr.first][curr.second] = '*';\
            \}\
            curr = prev[curr.first][curr.second];\
        \}\
    \}\
\
    return maze;\
\}\
\
\
int main() \{\
    ifstream inputFile("input.txt");\
    if (!inputFile.is_open()) \{\
        cerr << "\uc0\u1054 \u1096 \u1080 \u1073 \u1082 \u1072 : \u1085 \u1077  \u1091 \u1076 \u1072 \u1083 \u1086 \u1089 \u1100  \u1086 \u1090 \u1082 \u1088 \u1099 \u1090 \u1100  \u1092 \u1072 \u1081 \u1083  input.txt" << endl;\
        return 1;\
    \}\
\
    vector<string> maze;\
    string line;\
    size_t expected_length = 0;\
\
    while (getline(inputFile, line)) \{\
        if (maze.empty()) \{\
            expected_length = line.size();\
        \} else if (line.size() != expected_length) \{\
            cerr << "\uc0\u1054 \u1096 \u1080 \u1073 \u1082 \u1072 : \u1074 \u1089 \u1077  \u1089 \u1090 \u1088 \u1086 \u1082 \u1080  \u1083 \u1072 \u1073 \u1080 \u1088 \u1080 \u1085 \u1090 \u1072  \u1076 \u1086 \u1083 \u1078 \u1085 \u1099  \u1073 \u1099 \u1090 \u1100  \u1086 \u1076 \u1080 \u1085 \u1072 \u1082 \u1086 \u1074 \u1086 \u1081  \u1076 \u1083 \u1080 \u1085 \u1099 " << endl;\
            inputFile.close();\
            return 1;\
        \}\
        maze.push_back(line);\
    \}\
    inputFile.close();\
\
    if (maze.empty()) \{\
        cerr << "\uc0\u1054 \u1096 \u1080 \u1073 \u1082 \u1072 : \u1092 \u1072 \u1081 \u1083  input.txt \u1087 \u1091 \u1089 \u1090 " << endl;\
        return 1;\
    \}\
\
    vector<string> result = findAndMarkShortestPath(maze);\
\
    cout << "\uc0\u1056 \u1077 \u1079 \u1091 \u1083 \u1100 \u1090 \u1072 \u1090 :" << endl;\
    for (const auto& row : result) \{\
        cout << row << endl;\
    \}\
\
    return 0;\
\}}