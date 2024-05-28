#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>

struct Sportsman {
    std::string surname;
    double height;
};

struct StartsWithAC {
    bool operator()(const Sportsman& sportsman) const {
        char first_char = std::tolower(sportsman.surname[0]);
        return (first_char == '�' || first_char == '�');
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "ru");

    int count;

    std::cout << "������� ���������� ��������� � ������: ";
    std::cin >> count;
    std::cin.ignore();

    std::cout << std::endl;

    std::vector<Sportsman> sportsmen;

    for (int i = 0; i < count; i++)
    {
        std::string surname;
        double height;

        std::cout << "������� ������ ��� " << i + 1 << " ��������: ";
        std::cin >> surname >> height;
        sportsmen.push_back({ surname, height });
    }

    std::cout << std::endl;

    double total_height = 0.0;
    for (const Sportsman& sportsman : sportsmen) {
        total_height += sportsman.height;
    }
    double average_height = total_height / sportsmen.size();
    
    
    std::vector<Sportsman> filtered_sportsmen;

    std::copy_if(sportsmen.begin(), sportsmen.end(), std::back_inserter(filtered_sportsmen),
        [&](const Sportsman& sportsman) {
            return (sportsman.height < average_height) && StartsWithAC()(sportsman);
        });
    
    if (filtered_sportsmen.empty())
    {
        std::cout << "����������� � ������ ���� �������� � ��������, ������������ � 'a' ��� 'c' � ������ ���" << std::endl;
        return 1;
    }

    std::cout << "���������� � ������ ���� �������� � ��������, ������������ � 'a' ��� 'c':" << std::endl;
    for (const Sportsman& sportsman : filtered_sportsmen) {
        std::cout << sportsman.surname << " � ������ " << sportsman.height << std::endl;
    }

    return 0;
}
