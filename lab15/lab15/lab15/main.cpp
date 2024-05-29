#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> readMatrixFromFile(const string& filename, int& rows, int& cols) {
    vector<vector<int>> graph;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return graph;
    }

    file >> rows >> cols;

    graph.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> graph[i][j];
        }
    }

    file.close();
    return graph;
}

void outMatr(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> fillMatr(int a, int b) {
    vector<vector<int>> ans(3, vector<int>(3, 0));
    ans[0][0] = a;
    ans[1][1] = b;

    int c = (a % 8) + 1; // Используем следующую вершину по порядку

    while (c == a || c == b) {
        c = (c % 8) + 1;
    }

    ans[0][1] = c;

    return ans;
}

vector<vector<int>> findIntersections(const vector<vector<int>>& graph) {
    int vertices = graph[0].size();
    vector<vector<int>> intersections(vertices);

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (i != j) {
                for (const auto& row : graph) {
                    if (row[i] == 1 && row[j] == 1) {
                        intersections[i].push_back(j + 1);
                        break;
                    }
                }
            }
        }
    }

    return intersections;
}

void findIntersectingVertices(vector<vector<int>>& ans, const vector<vector<int>>& intersections, set<int>& usedVertices) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ans[i][j] == 0) {
                set<int> intersectingVertices;
                if (i > 0 && ans[i - 1][j] != 0) {
                    int v = ans[i - 1][j] - 1;
                    intersectingVertices.insert(intersections[v].begin(), intersections[v].end());
                }
                if (j > 0 && ans[i][j - 1] != 0) {
                    int v = ans[i][j - 1] - 1;
                    intersectingVertices.insert(intersections[v].begin(), intersections[v].end());
                }
                if (i < 2 && ans[i + 1][j] != 0) {
                    int v = ans[i + 1][j] - 1;
                    intersectingVertices.insert(intersections[v].begin(), intersections[v].end());
                }
                if (j < 2 && ans[i][j + 1] != 0) {
                    int v = ans[i][j + 1] - 1;
                    intersectingVertices.insert(intersections[v].begin(), intersections[v].end());
                }

                // Найти вершину, которая еще не использовалась
                int selectedVertex = 0;
                for (int vertex : intersectingVertices) {
                    if (usedVertices.find(vertex) == usedVertices.end()) {
                        selectedVertex = vertex;
                        break;
                    }
                }

                // Если не нашлось новой вершины, заполняем 0
                if (selectedVertex == 0) {
                    ans[i][j] = 0;
                }
                else {
                    ans[i][j] = selectedVertex;
                    usedVertices.insert(selectedVertex);
                }
            }
        }
    }
}

int calculatePathLength(const vector<vector<int>>& matrix, const vector<vector<int>>& intersections) {
    int length = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int vertex = matrix[i][j];
            if (vertex != 0) {
                vertex -= 1;
                for (int ii = 0; ii < 3; ++ii) {
                    for (int jj = 0; jj < 3; ++jj) {
                        if (i != ii || j != jj) {
                            int neighbor = matrix[ii][jj];
                            if (neighbor != 0 && find(intersections[vertex].begin(), intersections[vertex].end(), neighbor) != intersections[vertex].end()) {
                                length += abs(i - ii) + abs(j - jj);
                            }
                        }
                    }
                }
            }
        }
    }
    return length;
}

void optimizeMatrixRand(vector<vector<int>>& matrix, const vector<vector<int>>& intersections) {
    int bestLength = calculatePathLength(matrix, intersections);

    for (int i = 0; i < 300; ++i) {
        int x1 = rand() % 3, y1 = rand() % 3;
        int x2 = rand() % 3, y2 = rand() % 3;

        swap(matrix[x1][y1], matrix[x2][y2]);

        int newLength = calculatePathLength(matrix, intersections);

        if (newLength < bestLength) {
            bestLength = newLength;
        }
        else {
            swap(matrix[x1][y1], matrix[x2][y2]);
        }
    }
}

void optimizeMatrix1by1(vector<vector<int>>& matrix, const vector<vector<int>>& intersections) {
    int bestLength = calculatePathLength(matrix, intersections);

    for (int x = 0; x < 2; ++x) {
        int i = 0;
        for (int x1 = 0; x1 < 3; ++x1) {
            for (int y1 = 0; y1 < 3; ++y1) {
                for (int x2 = 0; x2 < 3; ++x2) {
                    for (int y2 = 0; y2 < 3; ++y2) {
                        i++;
                        if (x1 == x2 && y1 == y2) continue;

                        cout << bestLength << " " << matrix[x1][y1] << " " << matrix[x2][y2] << endl;

                        swap(matrix[x1][y1], matrix[x2][y2]);

                        int newLength = calculatePathLength(matrix, intersections);

                        cout << newLength << " " << matrix[x1][y1] << " " << matrix[x2][y2] << endl;

                        if (newLength < bestLength) {
                            bestLength = newLength;
                        }
                        else {
                            swap(matrix[x1][y1], matrix[x2][y2]);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    int N = 0;
    int L = 0;

    string filename = "schemeMatr.txt";
    vector<vector<int>> graph = readMatrixFromFile(filename, N, L);

    cout << "Цепи и элементы: " << endl;
    outMatr(graph);
    cout << endl;

    cout << "Введите элементы, которые будут располагаться в верхней левой части матрицы и в центре: " << endl;

    int a, b;
    cin >> a >> b;

    vector<vector<int>> ans = fillMatr(a, b);

    set<int> usedVertices = { ans[0][0], ans[0][1], ans[1][1] };

    //lab15
    cout << "Начальная матрица:" << endl;
    outMatr(ans);
    cout << endl;

    vector<vector<int>> intersections = findIntersections(graph);

    findIntersectingVertices(ans, intersections, usedVertices);

    cout << "Матрица после заполнения:" << endl;
    outMatr(ans);
    cout << endl;


    cout << "Выберите метод оптимизации матрицы: " << endl << "1) Метод случайных изменений (300 итераций)" << endl << "2) Метод последовательных изменений (162 итерации)" << endl;
    int choise;

    cin >> choise;

    if (choise == 1) optimizeMatrixRand(ans, intersections);
    if (choise == 2) optimizeMatrix1by1(ans, intersections);
    if (choise != 1 && choise != 2) { 
        cout << "Выбран неверный номер" << endl;
        return 1;
    };
    
    
    //lab16
    cout << "Оптимизированная матрица:" << endl;
    outMatr(ans);

    return 0;
}
