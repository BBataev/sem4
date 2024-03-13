#include <iostream>
#include <string>
#include <vector>

class Car
{
    std::string number;
    std::string brand;
    double cost;

public:
    Car() : number(""), brand(""), cost(0) {}

    Car(const std::string& num, const std::string& br, double cst)
        : number(num), brand(br), cost(cst) {}

    friend std::ostream& operator<<(std::ostream& os, const Car& car)
    {
        os << "Numbers: " << car.number << ", Brand: " << car.brand << ", Cost: " << car.cost << "$";
        return os;
    }

    bool operator==(const Car& other) const
    {
        return (number == other.number) && (brand == other.brand) && (cost == other.cost);
    }
};

class CarsDepot
{
    std::vector<Car> cars; 

public:
    void addCar(const Car& car)
    {
        cars.push_back(car);
    }

    void printCars() const
    {
        for (const auto& car : cars)
        {
            std::cout << car << std::endl;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "ru");

    std::cout << "Enter a depots count: ";
    int mCount;
    std::cin >> mCount;

    std::vector<CarsDepot> motorDepots(mCount);

    for (int i = 0; i < mCount; ++i)
    {
        CarsDepot& currentDepot = motorDepots[i];
        int carCount;

        std::cout << "Enter cars of depots " << (i + 1) << ": ";
        std::cin >> carCount;

        for (int j = 0; j < carCount; ++j)
        {
            std::string number, brand;
            double cost;

            std::cout << "Enter car's info " << (j + 1) << ":" << std::endl;
            std::cout << "Numbers: ";
            std::cin >> number;

            std::cout << "Brand: ";
            std::cin >> brand;

            std::cout << "Cost: ";
            std::cin >> cost;

            currentDepot.addCar(Car(number, brand, cost));
        }
    }

    for (int i = 0; i < mCount; ++i)
    {
        std::cout << "Cars in depot " << (i + 1) << ":" << std::endl;
        motorDepots[i].printCars();
        std::cout << std::endl;
    }

    return 0;
}
