#include <iostream>
#include <vector>

int main()
{
	std::vector<int> V;


    std::cout << "Enter a V quantity of elems: ";
    int quantity;
    std::cin >> quantity;

    std::cout << "Enter V elems: ";
    for (int i = 0; i < quantity; i++)
    {
        int newE;
        std::cin >> newE;
        V.push_back(newE);
    }

    auto it1 = std::find(V.begin(), V.end(), 0);

    if (it1 != V.end()) 
    {

        auto it2 = std::find(it1 + 1, V.end(), 0);

        if (it2 != V.end()) 
        {
            V.erase(it2);
        }
        else
        {
            std::cout << "There's no seconde zero to delete.";
        }
    }
    else
    {
        std::cout << "There's no any zero in V";
        return 1;
    }

    std::cout << "Result: ";
    for (int num : V) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}