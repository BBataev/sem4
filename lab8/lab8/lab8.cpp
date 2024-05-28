#include <iostream>
#include <set>
#include <string>
#include <conio.h>

class Car
{
    int depotNum;
    std::string number;
    std::string brand;
    double cost;

public:
    Car() : depotNum(0), number(""), brand(""), cost(0) {}

    Car(int dN, std::string num, const std::string br, double cst) : depotNum(dN), number(num), brand(br), cost(cst) {}

    friend std::ostream& operator << (std::ostream& os, const Car& car) {
        os << "Depot: " << car.depotNum << ", Number: " << car.number << ", Brand: " << car.brand << ", Cost: " << car.cost << "$";
        return os;
    }

    int getDepotNum() const
    {
        return depotNum;
    }

    std::string getBrand() const
    {
        return brand;
    }

    double getCost() const
    {
        return cost;
    }

    bool operator<(const Car& other) const {
        return number < other.number;
    }
};

template <typename T>
void addNewDepot(std::set<T>& obj, int count)
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
        obj.insert(car);
    }
}

void deleteDepot(std::set<Car>& obj, int depotNum)
{
    auto it = obj.begin();
    while (it != obj.end())
    {
        if (it->getDepotNum() == depotNum)
        {
            it = obj.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

int findDepotIntersection(const std::set<Car>& obj) {
    for (auto it1 = obj.begin(); it1 != obj.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != obj.end(); ++it2) {
            if (it1->getDepotNum() != it2->getDepotNum()) {
                std::set<std::string> brandsSet1, brandsSet2;

                for (const auto& car : obj) {
                    if (car.getDepotNum() == it1->getDepotNum()) {
                        brandsSet1.insert(car.getBrand());
                    }
                    if (car.getDepotNum() == it2->getDepotNum()) {
                        brandsSet2.insert(car.getBrand());
                    }
                }

                if (brandsSet1 == brandsSet2) {
                    std::cout << "Intersection of brands in depots " << it1->getDepotNum() << " and " << it2->getDepotNum() << ": " << std::endl;
                    for (const auto& brand : brandsSet1) {
                        std::cout << brand << std::endl;
                    }
                    return 1;
                }
            }
        }
    }
    std::cout << "There's no couples in brands" << std::endl;
    return 0;
}

void printSet(const std::set<Car>& obj)
{
    for (const auto& car : obj)
    {
        std::cout << car << std::endl;
    }
}

int choiceMenu();

void switchMoves(std::set<Car>& obj)
{
    bool stopProgram = false;

    do
    {
        switch (choiceMenu())
        {
        case 1:
            printSet(obj);
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
            std::cout << "Enter a depot number you want to delete: ";
            int choise;
            std::cin >> choise;

            deleteDepot(obj, choise);

            break;
        }
        case 4:
        {
            findDepotIntersection(obj);
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

    std::set<Car> motorDepots;

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
            motorDepots.insert(car);
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
