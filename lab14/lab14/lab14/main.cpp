#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

//Считывает матрицу
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

//Выводит матрицу
void outMatr(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

//Выводит вершины
void outVertex(set<int>& subset1, set<int>& subset2) {
    cout << "Массив вершин номер 1: ";
    for (int elem : subset1) {
        cout << elem + 1 << " ";
    }
    cout << endl;

    cout << "Массив вершин номер 2: ";
    for (int elem : subset2) {
        cout << elem + 1 << " " ;
    }
    cout << endl;
    cout << endl;
}

//Считает внутренние связи
int countInternalEdges(const std::set<int>& vertices, const vector<vector<int>>& matr) {
    int internalEdges = 0;

    for (const auto& row : matr) {
        bool isInternalEdge = true;
        for (int i = 0; i < row.size(); ++i) {
            if (row[i] == 1 && vertices.find(i) == vertices.end()) {
                isInternalEdge = false;
                break;
            }
        }
        if (isInternalEdge) {
            internalEdges++;
        }
    }

    return internalEdges;
}

//Находит число улучшения
void swap(set<int> subset1, set<int> subset2, int i, int j, vector<vector<int>> matrix, bool& improved) {
    int currentInternalEdges1 = countInternalEdges(subset1, matrix);
    int currentInternalEdges2 = countInternalEdges(subset2, matrix);

    subset1.erase(i);
    subset2.erase(j);

    subset1.insert(j);
    subset2.insert(i);

    int newInternalEdges1 = countInternalEdges(subset1, matrix);
    int newInternalEdges2 = countInternalEdges(subset2, matrix);

    if (newInternalEdges1 + newInternalEdges2 > currentInternalEdges1 + currentInternalEdges2) {
        improved = true;
    }
}

void optimize(set<int>& subset1, set<int>& subset2, vector<vector<int>>& matrix) {
    bool improvement = true;

    while (improvement) {
        improvement = false;

        set<int> subset1_copy = subset1;
        set<int> subset2_copy = subset2;

        int a = 0;

        for (int i : subset1_copy) {
            for (int j : subset2_copy) {
                swap(subset1, subset2, i, j, matrix, improvement);

                if (improvement && (subset1.find(i) != subset1.end()) && (subset2.find(j) != subset2.end())) {
                    subset1.erase(i);
                    subset2.erase(j);

                    subset1.insert(j);
                    subset2.insert(i);

                    int newInternalEdges1 = countInternalEdges(subset1, matrix);
                    int newInternalEdges2 = countInternalEdges(subset2, matrix);

                    cout << "Внутренние пересечения среди 1 массива вершин: " << newInternalEdges1 << endl;
                    cout << "Внутренние пересечения среди 2 массива вершин: " << newInternalEdges2 << endl << endl;

                    outVertex(subset1, subset2);

                    improvement = false;
                }
            }
        }
    }
}

//Выводит внутренние связи
void findInternalEdgesInSubsets(set<int>& subset1, set<int>& subset2, const vector<vector<int>>& matrix) {
    int internalEdges1 = countInternalEdges(subset1, matrix);
    int internalEdges2 = countInternalEdges(subset2, matrix);

    cout << "Внутренние пересечения среди 1 массива вершин: " << internalEdges1 << endl;
    cout << "Внутренние пересечения среди 2 массива вершин: " << internalEdges2 << endl << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    // Подмножество 1: v1, v2, v3, v4
    set<int> subset1 = { 0, 1, 2, 3 };
    // Подмножество 2: v5, v6, v7, v8
    set<int> subset2 = { 4, 5, 6, 7 };

    int N = 0;
    int L = 0;


    string filename = "schemeMatr.txt";
    vector<vector<int>> matrix = readMatrixFromFile(filename, N, L);

    cout << "Цепи и элементы: " << endl;
    outMatr(matrix);
    cout << endl;


    findInternalEdgesInSubsets(subset1, subset2, matrix);
    outVertex(subset1, subset2);

    optimize(subset1, subset2, matrix);

    cout << "На выводе получам такие разделения на платe, которые имеют наибольшее число внутренних пересечений: " << endl;

    outVertex(subset1, subset2);

    cout << "С числом внутренних пересечений: " << endl << "Для первого массива: " << countInternalEdges(subset1, matrix) << endl << "И для второго: " << countInternalEdges(subset2, matrix) << endl;
    
    return 0;
}
