#include <ostream>
#include <iostream>
#include <conio.h>


template <typename T>
class Set
{
    T* elements;
    int size;
    int capacity;

    friend class Car;
    friend void addNewDepot(const Set<T>& obj, int count);
    friend void deleteDepot(const Set<Car>& obj, int depotNum);
public:
    Set(int initialCapacity = 10)
    {
        size = 0;
        capacity = initialCapacity;
        elements = new T[capacity];
    }

    ~Set() {
        delete[] elements;
    }

    // Добавление элемента в множество
    void addElement(const T& element) {
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

    int getSize()
    {
        return size;
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
        for (int i = 0; i < size; i++) {
            std::cout << elements[i];
            if (i < size - 1) {
                std::cout << ";" << std::endl;
            }
        }
    }

    T& operator[](int index) {
        if (index >= 0 && index < size) {
            return elements[index];
        }
        else {
            std::cout << "No that type of element! First element returned" << std::endl;
            return elements[0];
        }
    }

    int findDepotIntersection() {
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (elements[i].getDepotNum() != elements[j].getDepotNum()) {
                    Set<std::string> brandsSet1, brandsSet2;

                    for (int k = 0; k < size; ++k) {
                        if (elements[k].getDepotNum() == elements[i].getDepotNum()) {
                            brandsSet1.addElement(elements[k].getBrand());
                        }
                        if (elements[k].getDepotNum() == elements[j].getDepotNum()) {
                            brandsSet2.addElement(elements[k].getBrand());
                        }
                    }

                    if (brandsSet1 == brandsSet2) {
                        std::cout << "Intersection of brands in depots " << elements[i].getDepotNum() << " and " << elements[j].getDepotNum() << ": " << std::endl;
                        brandsSet1.printSet();
                        return 1;
                    }
                }
            }
            std::cout << "There's no couples in brands";
            return 0;
        }
    }

    bool operator==(const Set<T>& obj)
    {
        if (size != obj.size)
        {
            return false;
        }

        for (int i = 0; i < size; i++)
        {
            if (!this->contains(obj.elements[i]))
            {
                return false;
            }
        }

        return true;
    }
};

class Car
{
    int depotNum;
    std::string number;
    std::string brand;
    double cost;

public:
    Car() : number(""), brand(""), cost(0) {}

    Car(int dN, std::string num, const std::string br, double cst) : depotNum(dN), number(num), brand(br), cost(cst) {}

    friend std::ostream& operator << (std::ostream& os, const Car& car) {
        os << "Depot: " << car.depotNum << ", Number: " << car.number << ", Brand: " << car.brand << ", Cost: " << car.cost << "$";
        return os;
    }

    int getDepotNum()
    {
        return depotNum;
    }

    std::string getBrand()
    {
        return brand;
    }

    double getCost()
    {
        return cost;
    }

    bool operator == (const Car& other) const {
        return (number == other.number) && (brand == other.brand) && (cost == other.cost);
    }
};

template <typename T>
void addNewDepot(Set<T>& obj, int count)
{
    std::cout << "Enter depot number (enter existing num if you want to add cars to existing depot): ";
    int depotNum;
    std::cin >> depotNum;

    for (int j = 0; j < count; j++)
    {
        std::string number, brand;
        double cost;


        std::cout << "Enter car details for car " << (j + 1) << ":" << std::endl;
        std::cout << "Number: ";
        std::cin >> number;
        std::cout << "Brand: ";
        std::cin >> brand;
        std::cout << "Cost: ";
        std::cin >> cost;

        Car car(depotNum, number, brand, cost);
        obj.addElement(car);
    }
}

void deleteDepot(Set<Car>& obj, int depotNum)
{
    for (int i = 0; i <= obj.getSize(); i++)
    {
        if (obj[i].getDepotNum() == depotNum)
        {
            obj.removeElement(obj[i]);
        }
    }
}


int choiceMenu();

void switchMoves(Set<Car>& obj)
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
            std::cout << "Enter how many cars in this depot: ";
            int carsCount;
            std::cin >> carsCount;
            
            addNewDepot(obj, carsCount);

            break;
        }
        case 3:
        {
            std::cout << "Enter a depot index you want to delete: ";
            int choise;
            std::cin >> choise;

            deleteDepot(obj, choise);

            break;
        }
        case 4:
        {
            obj.findDepotIntersection();
            _getch();
            break;
        }
        case 5:
            stopProgram = true;
            break;
        }
    } while (!stopProgram);
}

int main()
{
    std::cout << "Enter the number of motor depots: ";
    int mCount;
    std::cin >> mCount;

    Set<Car> motorDepots(mCount);

    for (int i = 0; i < mCount; ++i)
    {
        std::cout << "Enter the number of cars for motor depot " << (i + 1) << ": ";
        int carCount;
        std::cin >> carCount;

        for (int j = 0; j < carCount; ++j)
        {
            std::string number, brand;
            double cost;

            std::cout << "Enter car details for car " << (j + 1) << " at motor depot " << (i + 1) << ":\n";
            std::cout << "Number: ";
            std::cin >> number;
            std::cout << "Brand: ";
            std::cin >> brand;
            std::cout << "Cost: ";
            std::cin >> cost;

            Car car(i, number, brand, cost);
            motorDepots.addElement(car);
        }
    }

    switchMoves(motorDepots);

    return 0;
}

int choiceMenu()
{
    system("cls");
    std::cout
        << "1. Print cars set" << std::endl
        << "2. Add new car depot" << std::endl
        << "3. Delete car depot" << std::endl
        << "4. Check for brands intersection" << std::endl
        << "5. Close" << std::endl;
    char choice = char(0);
    do
    {
        choice = _getch();
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5');
     system("cls");

    return choice - '0';
}

