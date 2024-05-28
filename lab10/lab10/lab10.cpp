#include <iostream>
#include <string>
#include <set>
#include <windows.h>

struct Sportsman {
    std::string surname;
    double height;

    bool operator<(const Sportsman& other) const {
        return surname < other.surname;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "ru");

    int count;

    std::cout << "Введите коилчество студентов в списке: ";
    std::cin >> count;
    std::cin.ignore();

    std::cout << std::endl;

    std::set<Sportsman> sportsmen;

    for (int i = 0; i < count; i++)
    {
        std::string surname;
        double height;

        std::cout << "Введите данные для " << i + 1 << " студента: ";
        std::cin >> surname >> height;
        sportsmen.insert({ surname, height });
    }

    std::cout << std::endl;

    double total_height = 0.0;
    for (const Sportsman& sportsman : sportsmen) {
        total_height += sportsman.height;
    }
    double average_height = total_height / sportsmen.size();


    std::set<Sportsman> filtered_sportsmen;

    for (const Sportsman& sportsman : sportsmen) {
        if ((sportsman.surname[0] == 'а' || sportsman.surname[0] == 'А' ||
            sportsman.surname[0] == 'с' || sportsman.surname[0] == 'С') &&
            sportsman.height < average_height) 
        {
            filtered_sportsmen.insert(sportsman);
        }
    }

    if (filtered_sportsmen.empty())
    {
        std::cout << "Спортсменов с ростом ниже среднего и фамилией, начинающейся с 'a' или 'c' в списке нет" << std::endl;
        return 1;
    }

    std::cout << "Спортсмены с ростом ниже среднего и фамилией, начинающейся с 'a' или 'c':" << std::endl;
    for (const Sportsman& sportsman : filtered_sportsmen) {
        std::cout << sportsman.surname << " с ростом " << sportsman.height << std::endl;
    }

    return 0;
}