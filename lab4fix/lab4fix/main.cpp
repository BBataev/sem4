#include <ostream>
#include <iostream>
#include <conio.h>


class Complex
{
    double real, imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    bool operator == (const Complex& obj)
    {
        if (real == obj.real && imag == obj.imag)
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

template <typename T>
class Set 
{
    T* elements;
    int size;
    int capacity;

public:
    Set(int initialCapacity) {
        size = 0;
        capacity = initialCapacity;
        elements = new T[capacity];
    }

    ~Set() {
        delete[] elements;
    }

    // Добавление элемента в множество
    void addElement(T element) {
        if (!contains(element)) {
            if (size == capacity) {
                // Увеличиваем емкость массива, если необходимо
                int newCapacity = capacity * 2;
                T* newElements = new T[newCapacity];
                for (int i = 0; i < size; i++) {
                    newElements[i] = elements[i];
                }
                delete[] elements;
                elements = newElements;
                capacity = newCapacity;
            }
            elements[size] = element;
            size++;
        }
    }

    // Удаление элемента из множества
    void removeElement(T element) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                for (int j = i; j < size - 1; j++) {
                    elements[j] = elements[j + 1];
                }
                size--;
                return;
            }
        }
    }

    // Проверка вхождения элемента в множество
    bool contains(T element) const {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }

    // Объединение множеств
    Set<T> unionSets(const Set<T>& otherSet) const {
        Set<T> resultSet(size + otherSet.size);

        for (int i = 0; i < size; i++) {
            resultSet.addElement(elements[i]);
        }

        for (int i = 0; i < otherSet.size; i++) {
            resultSet.addElement(otherSet.elements[i]);
        }

        return resultSet;
    }

    // Объединение множеств без нового объекта
    void unionSetsWithout(Set<T>& mainSet, const Set<T>& otherSet) {
        for (int i = 0; i < (otherSet.size); i++) {
            mainSet.addElement(otherSet.elements[i]);
        }
    }
 
    // Пересечение множеств
    Set<T> intersection(const Set<T>& otherSet) const {
        Set<T> resultSet(size);

        for (int i = 0; i < size; i++) {
            if (otherSet.contains(elements[i])) {
                resultSet.addElement(elements[i]);
            }
        }

        return resultSet;
    }



    // Вывод множества
    void printSet() const {
        std::cout << "{ ";
        for (int i = 0; i < size; i++) {
            std::cout << elements[i];
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }" << std::endl;
    }
};

// Функция для ввода элементов множества
template <typename T>
void inputSetElements(Set<T>& set) {
    int numElements;
    std::cout << "Enter the number of elements: ";
    std::cin >> numElements;
    std::cout << "Enter the elements: ";
    for (int i = 0; i < numElements; i++) {
        T element;
        std::cin >> element;
        set.addElement(element);
    }
}

int choiceMenu();
int setChoiсe();

template <typename T>
void switchMoves(Set<T>& obj)
{
    bool stopProgram = false;

    do
    {
        switch (choiceMenu())
        {
        case 1:
            obj.printSet();
            _getch();
            break;
        case 2:
        {
            std::cout << "Enter an element that will be added to set: ";
            T elem;
            std::cin >> elem;
            obj.addElement(elem);
            break;
        }
        case 3:
        {
            std::cout << "Enter an element that will be deleted from set: ";
            T elem;
            std::cin >> elem;
            obj.removeElement(elem);
            break;
        }
        case 4:
        {
            T elem;
            std::cout << "Enter an element to check if it's in set: ";
            std::cin >> elem;
            if (obj.contains(elem))
            {
                std::cout << "Element " << elem << " is in set." << std::endl;
            }
            else
            {
                std::cout << "Element " << elem << " is not in set." << std::endl;
            }
            _getch();
            break;
        }
        case 5:
        {
            int initialCapacity = 10;
            Set<T> newObj(initialCapacity);
            inputSetElements(newObj);

            std::cout << "Intersection between sets: " <<  std::endl;
            
            Set<T> result = obj.intersection(newObj);

            result.printSet();

            _getch();
            break;
        }
        case 6:
        {
            int initialCapacity = 10;
            Set<T> newObj(initialCapacity);
            inputSetElements(newObj);

            std::cout << "Union between sets: " << std::endl;

            obj.unionSetsWithout(obj, newObj);

            obj.printSet();

            _getch();
            break;
        }
        case 7:
            stopProgram = true;
            break;
        }
    } while (!stopProgram);
}

int main() 
{

    int initialCapacity = 10;


    switch (setChoiсe())
    {
        case 1:
        {
            Set<int> newSet(initialCapacity);
            inputSetElements(newSet);
            switchMoves(newSet);
            break;
        }
        case 2:
        {
            Set<double> newSet(initialCapacity);
            inputSetElements(newSet);
            switchMoves(newSet);
            break;
        }
        case 3:
        {
            Set<Complex> newSet(initialCapacity);
            inputSetElements(newSet);
            switchMoves(newSet);
            break;
        }
        case 4:
        {
            Set<char> newSet(initialCapacity);
            inputSetElements(newSet);
            switchMoves(newSet);
            break;
        }
    }

	return 0;
}


int choiceMenu() 
{
	system("cls");
	std::cout
		<< "1. Print set" << std::endl
        << "2. Add elements to set" << std::endl
        << "3. Delete element" << std::endl
        << "4. Check if element is in set" << std::endl
        << "5. Intersection" << std::endl
        << "6. Sets union" << std::endl
        << "7. Close" << std::endl;
	char choice = char(0);
	do 
	{
		choice = _getch();
	} while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7' && choice != '8');
	system("cls");

	return choice - '0';
}

int setChoiсe()
{
    system("cls");
    std::cout
        << "1. Create set of integer" << std::endl
        << "2. Create set of double" << std::endl
        << "3. Create set of complex" << std::endl
        << "4. Create set of char" << std::endl;
    char choice = char(0);
    do
    {
        choice = _getch();
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4');
    system("cls");

    return choice - '0';
}