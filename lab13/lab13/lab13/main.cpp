#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> readMatrixFromFile(const string& filename, int& rows, int& cols) {
    vector<vector<int>> matrix;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return matrix;
    }

    file >> rows >> cols;

    matrix.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();
    return matrix;
}

void outMatr(const vector<vector<int>> matrix)
{
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int countExternalEdges(const std::set<int>&vertices, vector<vector<int>> matr, int N, int L) {
    int externalEdges = 0;

    for (int i = 0; i < N; ++i) {
        bool isExternalEdge = false;
        bool hasInternalVertex = false;
        for (int j = 0; j < L; ++j) {
            if (matr[i][j] == 1) {
                if (vertices.find(j) != vertices.end()) {
                    hasInternalVertex = true;
                }
                else {
                    isExternalEdge = true;
                }
            }
        }
        if (isExternalEdge && hasInternalVertex) {
            externalEdges++;
        }
    }

    return externalEdges;
}

int findMinBoards(int n, int l, int N, int L, vector<vector<int>> matr) {
    int minBoards = 0;
    std::vector<bool> used(L, false);

    while (true) {
        std::set<int> currentBoard;
        for (int i = 0; i < L && currentBoard.size() < n; ++i) {
            if (!used[i]) {
                currentBoard.insert(i);
                if (countExternalEdges(currentBoard, matr, N, L) > l) {
                    currentBoard.erase(i);
                }
            }
        }

        if (currentBoard.empty()) {
            break;
        }

        for (int vertex : currentBoard) {
            used[vertex] = true;
        }

        minBoards++;
    }

    for (bool vertexUsed : used) {
        if (!vertexUsed) {
            return -1;
        }
    }

    return minBoards;
}

int main()
{
    setlocale(LC_ALL, "ru");

    // Рабочие значения
    int N = 0;
    int L = 0;
    int n = 0;
    int l = 0;


    string filename = "schemeMatr.txt";
    vector<vector<int>> matrix = readMatrixFromFile(filename, N, L);


    cout << "Цепи и элементы: " << endl;
    outMatr(matrix);

    cout << endl;


    cout << "Введите число элементов для платы: " << endl;
    cin >> n;
    cout << "Введите число контактов разъема для платы: " << endl;
    cin >> l;
    cout << endl;
    cout << "Схема гиперграф и введенные элементы: " << endl;
    outMatr(matrix);

    cout << endl;

    cout << "Гиперграф размера: " << N << "x" << L << endl << "Число элементов: " << n << endl << "Число контактов разъема: " << l << endl;

    int minBoards = findMinBoards(n, l, N, L, matrix);
    if (minBoards == -1) {
        std::cout << "Невозможно распределить все вершины по платам с заданными контактами разъемов." << std::endl;
    }
    else {
        std::cout << "Минимальное количество плат: " << minBoards << std::endl;
    }

    return 0;
}
