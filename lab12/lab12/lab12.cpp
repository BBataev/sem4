#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> readMatrixFromFile(const string& filename) {
    vector<vector<int>> matrix;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return matrix;
    }

    int rows, cols;
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

void splitMatrix(const vector<vector<int>> matrix, int column1, int column2,
    vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, vector<vector<int>>& matrix3) 
{
    for (const auto& row : matrix) {
        matrix1.push_back(vector<int>(row.begin(), row.begin() + column1));
    }

    for (const auto& row : matrix) {
        matrix2.push_back(vector<int>(row.begin() + column1, row.begin() + column2));
    }

    for (const auto& row : matrix) {
        matrix3.push_back(vector<int>(row.begin() + column2, row.end()));
    }
}

void count—hainsInSections(const vector<vector<int>> matrix, int& count)
{
    int sum;
    for (const auto& row : matrix) {
        sum = 0;
        
        for (int val : row) {
            sum += val;
        }
        
        if (sum != 0)
        {
            count += 1;
        }
    }
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

int main() 
{
    setlocale(LC_ALL, "ru");

    string filename = "schemeMatr.txt";
    vector<vector<int>> matrix = readMatrixFromFile(filename);


    cout << "÷ÂÔË Ë ˝ÎÂÏÂÌÚ˚: " << endl;
    outMatr(matrix);

    cout << endl;

    int column1, column2;
    cout << "¬‚Â‰ËÚÂ ÌÓÏÂ‡ ÒÚÓÎ·ˆÓ‚, ÔÂÂ‰ ÍÓÚÓ˚ÏË ÌÛÊÌÓ Ò‰ÂÎ‡Ú¸ ‡ÁÂÁ (‰‚‡ ˜ËÒÎ‡ ˜ÂÂÁ ÔÓ·ÂÎ): ";
    cin >> column1 >> column2;

    cout << endl;

    vector<vector<int>> matrix1, matrix2, matrix3;

    splitMatrix(matrix, column1, column2, matrix1, matrix2, matrix3);
    
    cout << "œÂ‚‡ˇ ˜‡ÒÚ¸:" << endl;
    outMatr(matrix1);


    cout << endl;

    cout << "¬ÚÓ‡ˇ ˜‡ÒÚ¸:" << endl;
    outMatr(matrix2);


    cout << endl;

    cout << "“ÂÚ¸ˇ ˜‡ÒÚ¸:" << endl;
    outMatr(matrix3);


    cout << endl;

    int count1 = 0, count2 = 0, count3 = 0;
    
    count—hainsInSections(matrix1, count1);
    count—hainsInSections(matrix2, count2);
    count—hainsInSections(matrix3, count3);

    cout << "÷ÂÔË ‚ÓÒ¯Â‰¯ËÂ ‚ 1 ‡ÁÂÁ: " << count1 << endl;
    cout << "÷ÂÔË ‚ÓÒ¯Â‰¯ËÂ ‚ 2 ‡ÁÂÁ: " << count2 << endl;
    cout << "÷ÂÔË ‚ÓÒ¯Â‰¯ËÂ ‚ 3 ‡ÁÂÁ: " << count3 << endl;

    return 0;
}
