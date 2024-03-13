#include <iostream>

class Complex
{
    double real, imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator + (const Complex& obj)
    {
        return Complex(real + obj.real, imag + obj.imag);
    }

    Complex operator - (const Complex& obj)
    {
        return Complex(real - obj.real, imag - obj.imag);
    }

    Complex operator * (const Complex& obj)
    {
        return Complex((real * obj.real) - (imag * obj.imag), (real * obj.imag) + (imag * obj.real));
    }

    Complex operator = (const int cheto)
    {
        return Complex(real = cheto, imag = cheto);
    }

    bool operator > (const Complex& obj)
    {
        if (real > obj.real && imag > obj.imag)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend std::ostream& operator << (std::ostream& loli, const Complex& obj)
    {
        loli << obj.real << " + " << obj.imag << "i";
        return loli;
    }

    friend std::istream& operator >> (std::istream& loli, Complex& obj)
    {
        loli >> obj.real >> obj.imag;
        return loli;
    }
};

template<typename T>
T** createMatrix(int n, int m)
{
    T** matr = new T * [n];

    for (int i = 0; i < n; i++)
    {
        matr[i] = new T[m];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cin >> matr[i][j];
        }
    }

    return matr;
}

template<typename T>
void outMatr(int n, int m, T** matr)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << matr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

template<typename T>
T FindY(int n, int m, T** matr)
{

    T Y = 0;

    for (int i = 0; i < n; i++)
    {
        T max1 = 0;
        T max2 = 0;

        for (int j = 0; j < m; j++)
        {
            if (matr[i][j] > max1)
            {
                max1 = matr[i][j];
                std::cout << max1 << std::endl;
            }

            if (matr[i][m - 1 - j] > max2)
            {
                max2 = matr[i][m - 1 - j];
                std::cout << max2 << std::endl;
            }
        }

        Y += max1 * max2;
        std::cout << "Thats a Y:  " << Y << std::endl;
    }

    return Y;
}

int main()
{
    std::cout << "Greetings. Enter matrix rows and cols: " << std::endl;

    int n, m;
    std::cin >> n >> m;

    std::cout << "What data type do u prefer (1 for int, 2 for double, 3 for complex)?" << std::endl;

    int choise;
    std::cin >> choise;

    switch (choise)
    {
    case 1:
    {
        std::cout << "Ok. Now add some elements in your int matrix" << std::endl;

        int** matr = createMatrix<int>(n, m);

        std::cout << "Your matrix: " << std::endl;
        outMatr(n, m, matr);

        std::cout << "Finded Y: " << FindY(n, m, matr) << std::endl;

        break;
    }

    case 2:
    {
        std::cout << "Ok. Now add some elements in your double matrix" << std::endl;

        double** matr = createMatrix<double>(n, m);

        std::cout << "Your matrix: " << std::endl;
        outMatr(n, m, matr);

        break;
    }

    case 3:
    {
        std::cout << "Ok. Now add some elements in your Complex matrix" << std::endl;

        Complex** matr = createMatrix<Complex>(n, m);

        std::cout << "Your matrix: " << std::endl;
        outMatr(n, m, matr);

        break;
    }

    default:
    {
        std::cout << "There's not a nubmer u wrote.";
        break;
    }
    }
}